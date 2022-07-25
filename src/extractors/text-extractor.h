#ifndef TEXTEXTRACTOR_H
#define TEXTEXTRACTOR_H

#include "extractor-plugin.h"

namespace UkuiFileMetaData {

class TextExtractor : public ExtractorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ukui.ukuifilemetadata.ExtractorPlugin"
                      FILE "text-extractor.json")
    Q_INTERFACES(UkuiFileMetaData::ExtractorPlugin)

public:
    explicit TextExtractor(QObject *parent = nullptr);
    void extract(ExtractionResult *result) override;
    QStringList mimetypes() const override;

    friend class TextExtractorTest;
};
}

#endif // TEXTEXTRACTOR_H
