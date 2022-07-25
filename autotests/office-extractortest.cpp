#include "office-extractortest.h"
#include "indexerextractortestsconfig.h"
#include "extractors/office-extractor.h"
#include "simple-extraction-result.h"
#include "mime-utils.h"

#include <QTest>

using namespace UkuiFileMetaData;

QString testFilePath(const QString& baseName, const QString& extension)
{
    return QLatin1String(INDEXER_TESTS_OFFICE_FILES_PATH)
        + QLatin1Char('/') + baseName + QLatin1Char('.') + extension;
}

void OfficeExtractorTest::testContent_data()
{
    QTest::addColumn<QString>("fileType");

    QTest::addRow("Doc")
        << QStringLiteral("doc");

    QTest::addRow("WPS")
        << QStringLiteral("wps");

    QTest::addRow("Dot")
        << QStringLiteral("dot");

    QTest::addRow("Xls")
        << QStringLiteral("xls");

    QTest::addRow("Et")
        << QStringLiteral("et");

    QTest::addRow("Dps")
        << QStringLiteral("dps");

    QTest::addRow("PPT")
        << QStringLiteral("ppt");

    QTest::addRow("PPS")
        << QStringLiteral("pps");
}

void OfficeExtractorTest::testContent()
{
    QFETCH(QString, fileType);

    OfficeExtractor plugin{this};

    QMimeDatabase mimeDb;
    QString fileName = testFilePath(QStringLiteral("test"), fileType);
    QString mimeType = MimeUtils::strictMimeType(fileName, mimeDb).name();
    QVERIFY(plugin.mimetypes().contains(plugin.getSupportedMimeType(mimeType)));

    SimpleExtractionResult result(fileName, mimeType);
    plugin.extract(&result);

    QCOMPARE(result.text(), QStringLiteral("hwf"));
}
QTEST_GUILESS_MAIN(OfficeExtractorTest)
