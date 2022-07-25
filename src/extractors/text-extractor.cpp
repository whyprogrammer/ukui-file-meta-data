#include "text-extractor.h"

#include <QFile>
#include <QDebug>
#include <QTextCodec>
#include <uchardet/uchardet.h>

#define MAX_CONTENT_LENGTH 20480000

using namespace UkuiFileMetaData;

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
    QString textcontent;
    QByteArray encodedString = file.read(MAX_CONTENT_LENGTH);

    uchardet_t chardet = uchardet_new();
    if (uchardet_handle_data(chardet, encodedString.constData(), encodedString.size()) != 0)
        qWarning() << "Txt file encoding format detect fail!" << result->inputUrl();

    uchardet_data_end(chardet);
    const char *codec = uchardet_get_charset(chardet);

    if (QTextCodec::codecForName(codec) == 0)
        qWarning() << "Unsupported Text encoding format" << result->inputUrl() << QString::fromLocal8Bit(codec);

    QTextStream stream(encodedString, QIODevice::ReadOnly);
    stream.setCodec(codec);
    uchardet_delete(chardet);

    int lines = 0;
    textcontent = stream.readLine();
    while (!textcontent.isNull()) {
        result->append(textcontent);
        textcontent = stream.readLine();
        lines++;
    }
    result->add(Property::LineCount, lines);
    file.close();
    encodedString.clear();
    chardet = NULL;
    stream.flush();
}

QStringList TextExtractor::mimetypes() const
{
    return supportedMimeTypes;
}
