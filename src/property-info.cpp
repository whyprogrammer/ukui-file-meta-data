/*
    SPDX-FileCopyrightText: 2014 Vishesh Handa <me@vhanda.in>
    SPDX-FileCopyrightText: 2022 iaom <zhangpengfei@kylinos.cn>

    SPDX-License-Identifier: LGPL-2.1-only OR LGPL-3.0-only OR LicenseRef-KDE-Accepted-LGPL
*/

#include "property-info.h"

#include <QLocale>

using namespace UkuiFileMetaData;

class UkuiFileMetaData::PropertyInfoPrivate
{
public:
    Property::Property prop;
    QString name;
    QString displayName;
    QVariant::Type valueType;
    bool shouldBeIndexed;
//    QString (*formatAsString)(const QVariant& value) = nullptr;
};

PropertyInfo::PropertyInfo()
    : d(new PropertyInfoPrivate)
{
    d->prop = Property::Empty;
    d->name = QStringLiteral("empty");
    d->valueType = QVariant::Invalid;
    d->shouldBeIndexed = false;
//    d->formatAsString = &FormatStrings::toStringFunction;
}

PropertyInfo::PropertyInfo(Property::Property property)
    : d(new PropertyInfoPrivate)
{
    d->prop = property;
    d->shouldBeIndexed = true;
//    d->formatAsString = &FormatStrings::toStringFunction;

    switch (property) {
        case Property::Album:
            d->name = QStringLiteral("album");
            d->displayName = tr("Album");
            d->valueType = QVariant::String;
            break;

        case Property::AlbumArtist:
            d->name = QStringLiteral("albumArtist");
            d->displayName = tr("Album Artist");
            d->valueType = QVariant::String;
            break;

        case Property::Artist:
            d->name = QStringLiteral("artist");
            d->displayName = tr("Artist");
            d->valueType = QVariant::String;
            break;

        case Property::AspectRatio:
            d->name = QStringLiteral("aspectRatio");
            d->displayName = tr("Aspect Ratio");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAspectRatio;
            break;

        case Property::Author:
            d->name = QStringLiteral("author");
            d->displayName = tr("Author");
            d->valueType = QVariant::String;
            break;

        case Property::BitRate:
            d->name = QStringLiteral("bitRate");
            d->displayName = tr("Bitrate");
            d->valueType = QVariant::Int;
//            d->formatAsString = &FormatStrings::formatBitRate;
            break;

        case Property::Channels:
            d->name = QStringLiteral("channels");
            d->displayName = tr("Channels");
            d->valueType = QVariant::Int;
            break;

        case Property::Comment:
            d->name = QStringLiteral("comment");
            d->displayName = tr("Comment");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Description:
            d->name = QStringLiteral("description");
            d->displayName = tr("Description");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Composer:
            d->name = QStringLiteral("composer");
            d->displayName = tr("Composer");
            d->valueType = QVariant::String;
            break;

        case Property::Copyright:
            d->name = QStringLiteral("copyright");
            d->displayName = tr("Copyright");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::CreationDate:
            d->name = QStringLiteral("creationDate");
            d->displayName = tr("Creation Date");
            d->valueType = QVariant::DateTime;
//            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::Duration:
            d->name = QStringLiteral("duration");
            d->displayName = tr("Duration");
            d->valueType = QVariant::Int;
//            d->formatAsString = &FormatStrings::formatDuration;
            break;

        case Property::Empty:
            d->name = QStringLiteral("empty");
            d->valueType = QVariant::Invalid;
            break;

        case Property::FrameRate:
            d->name = QStringLiteral("frameRate");
            d->displayName = tr("Frame Rate");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsFrameRate;
            break;

        case Property::Generator:
            d->name = QStringLiteral("generator");
            d->displayName = tr("Document Generated By");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Genre:
            d->name = QStringLiteral("genre");
            d->displayName = tr("Genre");
            d->valueType = QVariant::String;
            break;

        case Property::Height:
            d->name = QStringLiteral("height");
            d->displayName = tr("Height");
            d->valueType = QVariant::Int;
            break;

        case Property::ImageDateTime:
            d->name = QStringLiteral("imageDateTime");
            d->displayName = tr("Image Date Time");
            d->valueType = QVariant::DateTime;
//            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::Manufacturer:
            d->name = QStringLiteral("manufacturer");
            d->displayName = tr("Manufacturer");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Model:
            d->name = QStringLiteral("model");
            d->displayName = tr("Model");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::ImageOrientation:
            d->name = QStringLiteral("imageOrientation");
            d->displayName = tr("Image Orientation");
            d->valueType = QVariant::Int;
//            d->formatAsString = &FormatStrings::formatOrientationValue;
            break;

        case Property::Keywords:
            d->name = QStringLiteral("keywords");
            d->displayName = tr("Keywords");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Language:
            d->name = QStringLiteral("language");
            d->displayName = tr("Language");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::LineCount:
            d->name = QStringLiteral("lineCount");
            d->displayName = tr("Line Count");
            d->valueType = QVariant::Int;
            break;

        case Property::Lyricist:
            d->name = QStringLiteral("lyricist");
            d->displayName = tr("Lyricist");
            d->valueType = QVariant::String;
            break;

        case Property::PageCount:
            d->name = QStringLiteral("pageCount");
            d->displayName = tr("Page Count");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoApertureValue:
            d->name = QStringLiteral("photoApertureValue");
            d->displayName = tr("Aperture Value");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsFNumber;
            break;

        case Property::PhotoDateTimeOriginal:
            d->name = QStringLiteral("photoDateTimeOriginal");
            d->displayName = tr("Original Date Time");
            d->valueType = QVariant::DateTime;
//            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::PhotoExposureBiasValue:
            d->name = QStringLiteral("photoExposureBiasValue");
            d->displayName = tr("Exposure Bias");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatPhotoExposureBias;
            break;

        case Property::PhotoExposureTime:
            d->name = QStringLiteral("photoExposureTime");
            d->displayName = tr("Exposure Time");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatPhotoTime;
            break;

        case Property::PhotoFlash:
            d->name = QStringLiteral("photoFlash");
            d->displayName = tr("Flash");
            d->valueType = QVariant::Int;
//            d->formatAsString = &FormatStrings::formatPhotoFlashValue;
            break;

        case Property::PhotoFNumber:
            d->name = QStringLiteral("photoFNumber");
            d->displayName = tr("F Number");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsFNumber;
            break;

        case Property::PhotoFocalLength:
            d->name = QStringLiteral("photoFocalLength");
            d->displayName = tr("Focal Length");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsMilliMeter;
            break;

        case Property::PhotoFocalLengthIn35mmFilm:
            d->name = QStringLiteral("photoFocalLengthIn35mmFilm");
            d->displayName = tr("Focal Length 35mm");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsMilliMeter;
            break;

        case Property::PhotoGpsLatitude:
            d->name = QStringLiteral("photoGpsLatitude");
            d->displayName = tr("GPS Latitude");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsDegree;
            break;

        case Property::PhotoGpsLongitude:
            d->name = QStringLiteral("photoGpsLongitude");
            d->displayName = tr("GPS Longitude");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsDegree;
            break;

        case Property::PhotoGpsAltitude:
            d->name = QStringLiteral("photoGpsAltitude");
            d->displayName = tr("GPS Altitude");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatAsMeter;
            break;

        case Property::PhotoISOSpeedRatings:
            d->name = QStringLiteral("photoISOSpeedRatings");
            d->displayName = tr("ISO Speed Rating");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoMeteringMode:
            d->name = QStringLiteral("photoMeteringMode");
            d->displayName = tr("Metering Mode");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoPixelXDimension:
            d->name = QStringLiteral("photoPixelXDimension");
            d->displayName = tr("X Dimension");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoPixelYDimension:
            d->name = QStringLiteral("photoPixelYDimension");
            d->displayName = tr("Y Dimension");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoSaturation:
            d->name = QStringLiteral("photoSaturation");
            d->displayName = tr("Saturation");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoSharpness:
            d->name = QStringLiteral("photoSharpness");
            d->displayName = tr("Sharpness");
            d->valueType = QVariant::Int;
            break;

        case Property::PhotoWhiteBalance:
            d->name = QStringLiteral("photoWhiteBalance");
            d->displayName = tr("White Balance");
            d->valueType = QVariant::Int;
            break;

        case Property::Publisher:
            d->name = QStringLiteral("publisher");
            d->displayName = tr("Publisher");
            d->valueType = QVariant::String;
            break;

        case Property::Label:
            d->name = QStringLiteral("label");
            d->displayName = tr("Label");
            d->valueType = QVariant::String;
            break;

        case Property::ReleaseYear:
            d->name = QStringLiteral("releaseYear");
            d->displayName = tr("Release Year");
            d->valueType = QVariant::Int;
            break;

        case Property::SampleRate:
            d->name = QStringLiteral("sampleRate");
            d->displayName = tr("Sample Rate");
            d->valueType = QVariant::Int;
//            d->formatAsString = &FormatStrings::formatSampleRate;
            break;

        case Property::Subject:
            d->name = QStringLiteral("subject");
            d->displayName = tr("Subject");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::Title:
            d->name = QStringLiteral("title");
            d->displayName = tr("Title");
            d->valueType = QVariant::String;
            break;

        case Property::TrackNumber:
            d->name = QStringLiteral("trackNumber");
            d->displayName = tr("Track Number");
            d->valueType = QVariant::Int;
            break;

        case Property::DiscNumber:
            d->name = QStringLiteral("discNumber");
            d->displayName = tr("Disc Number");
            d->valueType = QVariant::Int;
            break;

        case Property::Location:
            d->name = QStringLiteral("location");
            d->displayName = tr("Location");
            d->valueType = QVariant::String;
            break;

        case Property::Performer:
            d->name = QStringLiteral("performer");
            d->displayName = tr("Performer");
            d->valueType = QVariant::String;
            break;

        case Property::Ensemble:
            d->name = QStringLiteral("ensemble");
            d->displayName = tr("Ensemble");
            d->valueType = QVariant::String;
            break;

        case Property::Arranger:
            d->name = QStringLiteral("arranger");
            d->displayName = tr("Arranger");
            d->valueType = QVariant::String;
            break;

        case Property::Conductor:
            d->name = QStringLiteral("conductor");
            d->displayName = tr("Conductor");
            d->valueType = QVariant::String;
            break;

        case Property::Compilation:
            d->name = QStringLiteral("compilation");
            d->displayName = tr("Compilation");
            d->valueType = QVariant::String;
            break;

        case Property::License:
            d->name = QStringLiteral("license");
            d->displayName = tr("License");
            d->valueType = QVariant::String;
            break;

        case Property::Lyrics:
            d->name = QStringLiteral("lyrics");
            d->displayName = tr("Lyrics");
            d->valueType = QVariant::String;
            break;

        case Property::Opus:
            d->name = QStringLiteral("opus");
            d->displayName = tr("Opus");
            d->valueType = QVariant::Int;
            break;

        case Property::Rating:
            d->name = QStringLiteral("embeddedRating");
            d->displayName = tr("Rating");
            d->valueType = QVariant::Int;
            break;

        case Property::ReplayGainAlbumPeak:
            d->name = QStringLiteral("replayGainAlbumPeak");
            d->displayName = tr("Replay Gain Album Peak");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainAlbumGain:
            d->name = QStringLiteral("replayGainAlbumGain");
            d->displayName = tr("Replay Gain Album Gain");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainTrackPeak:
            d->name = QStringLiteral("replayGainTrackPeak");
            d->displayName = tr("Replay Gain Track Peak");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::ReplayGainTrackGain:
            d->name = QStringLiteral("replayGainTrackGain");
            d->displayName = tr("Replay Gain Track Gain");
            d->valueType = QVariant::Double;
//            d->formatAsString = &FormatStrings::formatDouble;
            break;

        case Property::Width:
            d->name = QStringLiteral("width");
            d->displayName = tr("Width");
            d->valueType = QVariant::Int;
            break;

        case Property::WordCount:
            d->name = QStringLiteral("wordCount");
            d->displayName = tr("Word Count");
            d->valueType = QVariant::Int;
            break;

        case Property::TranslationUnitsTotal:
            d->name = QStringLiteral("translationUnitsTotal");
            d->displayName = tr("Translatable Units");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationUnitsWithTranslation:
            d->name = QStringLiteral("translationUnitsWithTranslation");
            d->displayName = tr("Translations");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationUnitsWithDraftTranslation:
            d->name = QStringLiteral("translationUnitsWithDraftTranslation");
            d->displayName = tr("Draft Translations");
            d->valueType = QVariant::Int;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationLastAuthor:
            d->name = QStringLiteral("translationLastAuthor");
            d->displayName = tr("Author");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::TranslationLastUpDate:
            d->name = QStringLiteral("translationLastUpDate");
            d->displayName = tr("Last Update");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
//            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::TranslationTemplateDate:
            d->name = QStringLiteral("translationTemplateDate");
            d->displayName = tr("Template Creation");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
//            d->formatAsString = &FormatStrings::formatDate;
            break;

        case Property::OriginUrl:
            d->name = QStringLiteral("originUrl");
            d->displayName = tr("Downloaded From");
            d->valueType = QVariant::Url;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailSubject:
            d->name = QStringLiteral("originEmailSubject");
            d->displayName = tr("E-Mail Attachment Subject");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailSender:
            d->name = QStringLiteral("originEmailSender");
            d->displayName = tr("E-Mail Attachment Sender");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::OriginEmailMessageId:
            d->name = QStringLiteral("originEmailMessageId");
            d->displayName = tr("E-Mail Attachment Message ID");
            d->valueType = QVariant::String;
            d->shouldBeIndexed = false;
            break;

        case Property::PropertyCount: // To silence the compiler.
            break;

        // NOTE: new properties must also be added to ::fromName()
    }

    if (d->valueType == QVariant::Int || d->valueType == QVariant::DateTime ||
        d->valueType == QVariant::Double)
    {
        d->shouldBeIndexed = false;
    }
}

PropertyInfo::PropertyInfo(const PropertyInfo& pi)
    : d(new PropertyInfoPrivate(*pi.d))
{
}

PropertyInfo::~PropertyInfo() = default;

PropertyInfo& PropertyInfo::operator=(const PropertyInfo& rhs)
{
    *d = *rhs.d;
    return *this;
}

bool PropertyInfo::operator==(const PropertyInfo& rhs) const
{
    return d->name == rhs.d->name && d->displayName == rhs.d->displayName &&
           d->prop == rhs.d->prop && d->shouldBeIndexed == rhs.d->shouldBeIndexed;
}

QString PropertyInfo::displayName() const
{
    return d->displayName;
}

QString PropertyInfo::name() const
{
    return d->name;
}

Property::Property PropertyInfo::property() const
{
    return d->prop;
}

QVariant::Type PropertyInfo::valueType() const
{
    return d->valueType;
}

bool PropertyInfo::shouldBeIndexed() const
{
    return d->shouldBeIndexed;
}

QString PropertyInfo::formatAsDisplayString(const QVariant &value) const
{
    if (value.type() == QVariant::List || value.type() == QVariant::StringList) {
        if (d->valueType == QVariant::String) {
            return QLocale().createSeparatedList(value.toStringList());
        } else {
// TODO: add a format method.
//            QStringList displayList;
//            const auto valueList = value.toList();
//            for (const auto& entry : valueList) {
//                displayList << d->formatAsString(entry);
//            }
//            return QLocale().createSeparatedList(displayList);
            return value.toString();
        }
    } else {
//        return d->formatAsString(value);
        return value.toString();
    }
}

PropertyInfo PropertyInfo::fromName(const QString& name)
{
    static QHash<QString, Property::Property> propertyHash = {
        { QStringLiteral("bitrate"), Property::BitRate },
        { QStringLiteral("channels"), Property::Channels },
        { QStringLiteral("duration"), Property::Duration },
        { QStringLiteral("genre"), Property::Genre },
        { QStringLiteral("samplerate"), Property::SampleRate },
        { QStringLiteral("tracknumber"), Property::TrackNumber },
        { QStringLiteral("discnumber"), Property::DiscNumber },
        { QStringLiteral("releaseyear"), Property::ReleaseYear },
        { QStringLiteral("comment"), Property::Comment },
        { QStringLiteral("description"), Property::Description },
        { QStringLiteral("artist"), Property::Artist },
        { QStringLiteral("album"), Property::Album },
        { QStringLiteral("albumartist"), Property::AlbumArtist },
        { QStringLiteral("composer"), Property::Composer },
        { QStringLiteral("lyricist"), Property::Lyricist },
        { QStringLiteral("location"), Property::Location },
        { QStringLiteral("performer"), Property::Performer },
        { QStringLiteral("ensemble"), Property::Ensemble },
        { QStringLiteral("arranger"), Property::Arranger },
        { QStringLiteral("conductor"), Property::Conductor },
        { QStringLiteral("opus"), Property::Opus },
        { QStringLiteral("embeddedrating"), Property::Rating },
        { QStringLiteral("author"), Property::Author },
        { QStringLiteral("title"), Property::Title },
        { QStringLiteral("subject"), Property::Subject },
        { QStringLiteral("generator"), Property::Generator },
        { QStringLiteral("pagecount"), Property::PageCount },
        { QStringLiteral("wordcount"), Property::WordCount },
        { QStringLiteral("linecount"), Property::LineCount },
        { QStringLiteral("language"), Property::Language },
        { QStringLiteral("copyright"), Property::Copyright },
        { QStringLiteral("publisher"), Property::Publisher },
        { QStringLiteral("label"), Property::Label },
        { QStringLiteral("compilation"), Property::Compilation },
        { QStringLiteral("license"), Property::License },
        { QStringLiteral("lyrics"), Property::Lyrics },
        { QStringLiteral("replaygainalbumpeak"), Property::ReplayGainAlbumPeak },
        { QStringLiteral("replaygainalbumgain"), Property::ReplayGainAlbumGain },
        { QStringLiteral("replaygaintrackpeak"), Property::ReplayGainTrackPeak },
        { QStringLiteral("replaygaintrackgain"), Property::ReplayGainTrackGain },
        { QStringLiteral("creationdate"), Property::CreationDate },
        { QStringLiteral("keywords"), Property::Keywords },
        { QStringLiteral("width"), Property::Width },
        { QStringLiteral("height"), Property::Height },
        { QStringLiteral("aspectratio"), Property::AspectRatio },
        { QStringLiteral("framerate"), Property::FrameRate },
        { QStringLiteral("manufacturer"), Property::Manufacturer },
        { QStringLiteral("model"), Property::Model },
        { QStringLiteral("imagedatetime"), Property::ImageDateTime },
        { QStringLiteral("imageorientation"), Property::ImageOrientation },
        { QStringLiteral("photoflash"), Property::PhotoFlash },
        { QStringLiteral("photopixelxdimension"), Property::PhotoPixelXDimension },
        { QStringLiteral("photopixelydimension"), Property::PhotoPixelYDimension },
        { QStringLiteral("photodatetimeoriginal"), Property::PhotoDateTimeOriginal },
        { QStringLiteral("photofocallength"), Property::PhotoFocalLength },
        { QStringLiteral("photofocallengthin35mmfilm"), Property::PhotoFocalLengthIn35mmFilm },
        { QStringLiteral("photoexposuretime"), Property::PhotoExposureTime },
        { QStringLiteral("photofnumber"), Property::PhotoFNumber },
        { QStringLiteral("photoaperturevalue"), Property::PhotoApertureValue },
        { QStringLiteral("photoexposurebiasvalue"), Property::PhotoExposureBiasValue },
        { QStringLiteral("photowhitebalance"), Property::PhotoWhiteBalance },
        { QStringLiteral("photometeringmode"), Property::PhotoMeteringMode },
        { QStringLiteral("photoisospeedratings"), Property::PhotoISOSpeedRatings },
        { QStringLiteral("photosaturation"), Property::PhotoSaturation },
        { QStringLiteral("photosharpness"), Property::PhotoSharpness },
        { QStringLiteral("photogpslatitude"), Property::PhotoGpsLatitude },
        { QStringLiteral("photogpslongitude"), Property::PhotoGpsLongitude },
        { QStringLiteral("photogpsaltitude"), Property::PhotoGpsAltitude },
        { QStringLiteral("translationunitstotal"), Property::TranslationUnitsTotal },
        { QStringLiteral("translationunitswithtranslation"), Property::TranslationUnitsWithTranslation },
        { QStringLiteral("translationunitswithdrafttranslation"), Property::TranslationUnitsWithDraftTranslation },
        { QStringLiteral("translationlastauthor"), Property::TranslationLastAuthor },
        { QStringLiteral("translationlastupdate"), Property::TranslationLastUpDate },
        { QStringLiteral("translationtemplatedate"), Property::TranslationTemplateDate },
        { QStringLiteral("originurl"), Property::OriginUrl },
        { QStringLiteral("originemailsubject"), Property::OriginEmailSubject },
        { QStringLiteral("originemailsender"), Property::OriginEmailSender },
        { QStringLiteral("originemailmessageid"), Property::OriginEmailMessageId }
    };

    return PropertyInfo(propertyHash.value(name.toLower()));
}
