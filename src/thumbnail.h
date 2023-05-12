//
// Created by zpf on 2023/5/10.
//

#ifndef UKUI_FILE_METADATA_THUMBNAIL_H
#define UKUI_FILE_METADATA_THUMBNAIL_H
#include <QUrl>
#include <QSize>
#include "ukui-file-metadata_global.h"
class QString;
class QImage;
class ThumbnailRequestPrivate;
class ThumbnailPrivate;
namespace UkuiFileMetadata {
class UKUIFILEMETADATA_EXPORT ThumbnailRequest
{
public:
    ThumbnailRequest();
    explicit ThumbnailRequest(const QSize &targetSize, qreal dpr);
    ThumbnailRequest(const ThumbnailRequest &other);
    ThumbnailRequest &operator=(const ThumbnailRequest &other);
    ThumbnailRequest &operator=(ThumbnailRequest &&other) noexcept;
    ~ThumbnailRequest();

    QSize targetSize() const;
    qreal devicePixelRatio() const;
private:
    ThumbnailRequestPrivate *d;
};

class UKUIFILEMETADATA_EXPORT Thumbnail
{
public:
    explicit Thumbnail(const QImage &image);
    Thumbnail();
    Thumbnail(const Thumbnail &other);
    Thumbnail &operator=(const Thumbnail &other);
    Thumbnail &operator=(Thumbnail &&other) noexcept;
    ~Thumbnail();

    QImage image() const;
    bool isValid() const;

private:
    ThumbnailPrivate *d;
};

} // UkuiFileMetadata

#endif //UKUI_FILE_METADATA_THUMBNAIL_H
