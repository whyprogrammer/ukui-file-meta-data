#ifndef OFFICE2007EXTRACTOR_H
#define OFFICE2007EXTRACTOR_H

#include "extractor-plugin.h"

namespace UkuiFileMetaData {

class Office2007Extractor : public ExtractorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ukui.ukuifilemetadata.ExtractorPlugin"
                      FILE "office2007-extractor.json")
    Q_INTERFACES(UkuiFileMetaData::ExtractorPlugin)

public:
    Office2007Extractor(QObject *parent = nullptr);
    void extract(ExtractionResult *result) override;
    QStringList mimetypes() const override;

    friend class Office2007ExtractorTest;
};
}
#endif // OFFICE2007EXTRACTOR_H
