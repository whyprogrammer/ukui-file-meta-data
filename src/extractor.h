/*
    SPDX-FileCopyrightText: 2014 Vishesh Handa <me@vhanda.in>
    SPDX-FileCopyrightText: 2022 iaom <zhangpengfei@kylinos.cn>

    SPDX-License-Identifier: LGPL-2.1-or-later
*/

#ifndef UKUIFILEMETADATA_EXTRACTOR_H
#define UKUIFILEMETADATA_EXTRACTOR_H

#include "ukui-file-metadata_global.h"
#include <memory>
#include <QStringList>
#include <QVariantMap>
#include <QPluginLoader>
#include "extractor-plugin.h"

namespace UkuiFileMetaData {

class ExtractionResult;
class ExtractorManager;
class ExtractorPlugin;
class ExtractorPrivate;

/**
 * \class Extractor extractor.h <KFileMetaData/Extractor>
 */
class UKUIFILEMETADATA_EXPORT Extractor
{
    friend class ExtractorManager;
    friend class ExtractorManagerPrivate;
    friend class ExtractorPrivate;

    enum ExtractorPluginOwnership {
        AutoDeletePlugin,
        DoNotDeletePlugin,
    };

public:
    Extractor(Extractor&&) noexcept ;
    virtual ~Extractor() noexcept;

    void extract(ExtractionResult* result);
    QStringList mimetypes() const;
    QVariantMap extractorProperties() const;

private:
    Extractor();
    Extractor(const Extractor&);

    void operator =(const Extractor&);

    void setExtractorPlugin(ExtractorPlugin *extractorPlugin);

    void setAutoDeletePlugin(ExtractorPluginOwnership autoDelete);

    void setMetaData(const QVariantMap &metaData);

    void setPluginPath(const QString &path);

    bool initPlugin();

    std::unique_ptr<ExtractorPrivate> d;
};
}

#endif // UKUIFILEMETADATA_EXTRACTOR_H
