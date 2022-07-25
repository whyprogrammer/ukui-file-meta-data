#ifndef PDFEXTRACTOR_H
#define PDFEXTRACTOR_H

#include "extractor-plugin.h"

#include <poppler-qt5.h>

namespace UkuiFileMetaData {

class PdfExtractor : public ExtractorPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.ukui.ukuifilemetadata.ExtractorPlugin"
                      FILE "pdf-extractor.json")
    Q_INTERFACES(UkuiFileMetaData::ExtractorPlugin)

public:
    PdfExtractor(QObject *parent = nullptr);
    void extract(ExtractionResult *result) override;
    QStringList mimetypes() const override;

    friend class PdfExtractorTest;
};
}


#endif // PDFEXTRACTOR_H
