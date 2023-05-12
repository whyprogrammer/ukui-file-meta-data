/*
 *
 * Copyright (C) 2022, KylinSoft Co., Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 * Authors: baijunjie <baijunjie@kylinos.cn>
 *
 */
#include "text-extractor.h"

#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <uchardet/uchardet.h>

#define MAX_CONTENT_LENGTH 20480000

using namespace UkuiFileMetadata;

const QStringList supportedMimeTypes = {
    QStringLiteral("text/plain")
};

TextExtractor::TextExtractor(QObject *parent) : ExtractorPlugin(parent)
{

}

void TextExtractor::extract(ExtractionResult *result)
{
    QFile file(result->inputUrl());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    if (!(result->inputFlags() & ExtractionResult::ExtractPlainText)) {
        file.close();
        return;
    }

    result->addType(Type::Text);
    QString textContent;
    QByteArray encodedString = file.read(MAX_CONTENT_LENGTH);

    uchardet_t chardet = uchardet_new();
    if (uchardet_handle_data(chardet, encodedString.constData(), encodedString.size()) != 0)
        qWarning() << "Txt file encoding format detect fail!" << result->inputUrl();

    uchardet_data_end(chardet);
    const char *codec = uchardet_get_charset(chardet);

    if (QTextCodec::codecForName(codec) == nullptr)
        qWarning() << "Unsupported Text encoding format" << result->inputUrl() << QString::fromLocal8Bit(codec);

    QTextStream stream(encodedString, QIODevice::ReadOnly);
    stream.setCodec(codec);
    uchardet_delete(chardet);

    int lines = 0;
    textContent = stream.readLine();
    while (!textContent.isNull()) {
        result->append(textContent);
        textContent = stream.readLine();
        lines++;
    }
    result->add(Property::LineCount, lines);
    file.close();
    encodedString.clear();
    chardet = nullptr;
    stream.flush();
}

QStringList TextExtractor::mimetypes() const
{
    return supportedMimeTypes;
}
