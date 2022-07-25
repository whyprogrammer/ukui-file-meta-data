#include "pdf-extractor.h"
#include <QDebug>

using namespace UkuiFileMetaData;

const QStringList supportedMimeTypes = {
    QStringLiteral("application/pdf")
};

PdfExtractor::PdfExtractor(QObject *parent) : ExtractorPlugin(parent)
{

}

void PdfExtractor::extract(ExtractionResult *result)
{
    const QString fileUrl = result->inputUrl();
    std::unique_ptr<Poppler::Document> pdfDoc(Poppler::Document::load(fileUrl));

    if (!pdfDoc || pdfDoc->isLocked()) {
        return;
    }

    result->addType(Type::Document);

    if (result->inputFlags() & ExtractionResult::ExtractMetaData) {
        const QString title = pdfDoc->title();
        if (!title.isEmpty()) {
            result->add(Property::Title, title);
        }

        const QString subject = pdfDoc->subject();
        if (!subject.isEmpty()) {
            result->add(Property::Subject, subject);
        }

        const QString author = pdfDoc->author();
        if (!author.isEmpty()) {
            result->add(Property::Author, author);
        }

        const QString generator = pdfDoc->producer();
        if (!generator.isEmpty()) {
            result->add(Property::Generator, generator);
        }

        const QDateTime creationDate = pdfDoc->creationDate();
        if (!creationDate.isNull()) {
            result->add(Property::CreationDate, creationDate);
        }

        const int numPages = pdfDoc->numPages();
        if (numPages > 0) {
            result->add(Property::PageCount, numPages);
        }
    }

    if (!(result->inputFlags() & ExtractionResult::ExtractPlainText)) {
        return;
    }

    for (int i = 0; i < pdfDoc->numPages(); i++) {
        std::unique_ptr<Poppler::Page> page(pdfDoc->page(i));
        if (!page) { // broken pdf files do not return a valid page
            qWarning() << "Could not read page content from" << fileUrl;
            break;
        }
        result->append(page->text(QRectF()).replace("/n", "").replace("/r", " "));
    }
}

QStringList PdfExtractor::mimetypes() const
{
    return supportedMimeTypes;
}
