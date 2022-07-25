#ifndef OFFICEEXTRACTOR_H
#define OFFICEEXTRACTOR_H

#include "extractor-plugin.h"

namespace UkuiFileMetaData {

class OfficeExtractor : public ExtractorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ukui.ukuifilemetadata.ExtractorPlugin"
                      FILE "office-extractor.json")
    Q_INTERFACES(UkuiFileMetaData::ExtractorPlugin)
public:
    explicit OfficeExtractor(QObject *parent = nullptr);

    void extract(ExtractionResult* result) override;
    QStringList mimetypes() const override;

    friend class OfficeExtractorTest;
};

}


#endif // OFFICEEXTRACTOR_H
