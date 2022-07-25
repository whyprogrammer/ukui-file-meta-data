#ifndef OFFICEEXTRACTORTEST_H
#define OFFICEEXTRACTORTEST_H

#include <QObject>

namespace UkuiFileMetaData {

class OfficeExtractorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testContent();
    void testContent_data();
};
}

#endif // OFFICEEXTRACTORTEST_H
