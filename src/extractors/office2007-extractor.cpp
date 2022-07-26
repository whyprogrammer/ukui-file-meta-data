#include "office2007-extractor.h"

#include <QFileInfo>
#include <quazip5/quazip.h>
#include <quazip5/quazipfile.h>
#include <QXmlStreamReader>

using namespace UkuiFileMetaData;

const QStringList supportedMimeTypes = {
    QStringLiteral("application/vnd.openxmlformats-officedocument.wordprocessingml.document"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.wordprocessingml.template"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.presentationml.presentation"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.presentationml.slide"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.presentationml.slideshow"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.presentationml.template"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"),
    QStringLiteral("application/vnd.openxmlformats-officedocument.spreadsheetml.template"),
};

Office2007Extractor::Office2007Extractor(QObject *parent) : ExtractorPlugin(parent)
{

}

void Office2007Extractor::extract(ExtractionResult *result)
{
    QFileInfo info = QFileInfo(result->inputUrl());
    if (!info.exists() || info.isDir()) {
        return;
    }

    QuaZip file(result->inputUrl());
    if (!file.open(QuaZip::mdUnzip)) {
        return;
    }

    QuaZipFile fileR(&file);
    QXmlStreamReader reader(&fileR);

    if (result->inputFlags() & ExtractionResult::ExtractMetaData) {
        if (file.setCurrentFile("docProps/core.xml", QuaZip::csSensitive) and fileR.open(QIODevice::ReadOnly)) {
            while (!reader.atEnd()) {
               if (reader.readNextStartElement()) {
                  if (reader.name().toString() == "description") {
                      QString desc = reader.readElementText();
                      if (!desc.isEmpty()) {
                          result->add(Property::Description, desc);
                      }
                      continue;
                  } else if (reader.name().toString() == "subject") {
                      QString subject = reader.readElementText();
                      if (!subject.isEmpty()) {
                          result->add(Property::Subject, subject);
                      }
                      continue;
                  } else if (reader.name().toString() == "title") {
                      QString title = reader.readElementText();
                      if (!title.isEmpty()) {
                          result->add(Property::Title, title);
                      }
                      continue;
                  } else if (reader.name().toString() == "creator") {
                      QString creator = reader.readElementText();
                      if (!creator.isEmpty()) {
                          result->add(Property::Author, creator);
                      }
                      continue;
                  } else if (reader.name().toString() == "language") {
                      QString language = reader.readElementText();
                      if (!language.isEmpty()) {
                          result->add(Property::Language, language);
                      }
                      continue;
                  } else if (reader.name().toString() == "created") {
                      QString creationDate = reader.readElementText();
                      if (!creationDate.isEmpty()) {
                          result->add(Property::CreationDate, creationDate);
                      }
                      continue;
                  } else if (reader.name().toString() == "keywords") {
                      QString keywords = reader.readElementText();
                      if (!keywords.isEmpty()) {
                          result->add(Property::Keywords, keywords);
                      }
                      continue;
                  }
               }
            }
            fileR.close();
        }

        if (file.setCurrentFile("docProps/app.xml", QuaZip::csSensitive) and fileR.open(QIODevice::ReadOnly)) {
            reader.clear();
            reader.setDevice(&fileR);
            while (!reader.atEnd()) {
                if (reader.readNextStartElement()) {
                    if (this->getSupportedMimeType(result->inputMimetype()) ==
                            QLatin1String("application/vnd.openxmlformats-officedocument.wordprocessingml.document")) {
                        if (reader.name().toString() == "Pages") {
                            bool ok = false;
                            int pageCount = reader.readElementText().toInt(&ok);
                            if (ok) {
                                result->add(Property::PageCount, pageCount);
                            }
                        } else if (reader.name().toString() == "Words") {
                            bool ok = false;
                            int wordCount = reader.readElementText().toInt(&ok);
                            if (ok) {
                                result->add(Property::WordCount, wordCount);
                            }
                        }
                    }

                    if (reader.name().toString() == "Application") {
                        QString generator = reader.readElementText();
                        if (!generator.isEmpty()) {
                            result->add(Property::Generator, generator);
                        }
                    }
                }
            }
            fileR.close();
        }
    }

    //extract document content
    if (result->inputFlags() & ExtractionResult::ExtractPlainText) {
        //word
        if (file.setCurrentFile("word/document.xml", QuaZip::csSensitive) and fileR.open(QIODevice::ReadOnly)) {
            reader.clear();
            reader.setDevice(&fileR);
            result->addType(Type::Document);
            while (!reader.atEnd()) {
               if (reader.readNextStartElement() and reader.name().toString() == "t") {
                   result->append(reader.readElementText().replace("\n", "").replace("\r", " "));
               }
            }
            fileR.close();
        //excel
        } else if (file.setCurrentFile("xl/sharedStrings.xml", QuaZip::csSensitive) and fileR.open(QIODevice::ReadOnly)) {
            reader.clear();
            reader.setDevice(&fileR);
            result->addType(Type::Document);
            result->addType(Type::Spreadsheet);
            while (!reader.atEnd()) {
               if (reader.readNextStartElement() and reader.name().toString() == "t") {
                   result->append(reader.readElementText().replace("\n", "").replace("\r", " "));
               }
            }
            fileR.close();
        } else {
            //powerpoint
            QStringList slideXmlList;
            for (const QString &slideFile : file.getFileNameList()) {
                if (slideFile.contains(QRegExp("ppt/slides/slide*"))) {
                    slideXmlList << slideFile;
                }
            }
            if (!slideXmlList.isEmpty()) {
                result->addType(Type::Document);
                result->addType(Type::Presentation);
                for (QString slideXmlFile : slideXmlList) {
                    if (file.setCurrentFile(slideXmlFile, QuaZip::csSensitive) and fileR.open(QIODevice::ReadOnly)) {
                        reader.clear();
                        reader.setDevice(&fileR);
                        while (!reader.atEnd()) {
                            if(reader.readNextStartElement() and reader.name().toString() == "t"){
                                result->append(reader.readElementText().replace("\n", "").replace("\r", " "));
                            }
                        }
                        fileR.close();
                    }
                }
            }
        }
    }

    file.close();
}

QStringList Office2007Extractor::mimetypes() const
{
    return supportedMimeTypes;
}
