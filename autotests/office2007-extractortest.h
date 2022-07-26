#ifndef OFFICE2007EXTRACTORTEST_H
#define OFFICE2007EXTRACTORTEST_H

#include <QObject>

namespace UkuiFileMetaData {

class Office2007ExtractorTest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void testNoExtraction();
    void test();
//    void testContent_data();
};
}

#endif // OFFICE2007EXTRACTORTEST_H
