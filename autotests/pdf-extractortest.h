#ifndef PDFEXTRACTORTEST_H
#define PDFEXTRACTORTEST_H

#include <QObject>

namespace UkuiFileMetaData {

class PdfExtractorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testNoExtraction();
    void testAllData();
    void testMetaDataOnly();
};

}



#endif // PDFEXTRACTORTEST_H
