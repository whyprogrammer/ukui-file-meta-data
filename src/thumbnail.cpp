//
// Created by zpf on 2023/5/10.
//

#include "thumbnail.h"
#include <QImage>

using namespace UkuiFileMetadata;
class ThumbnailRequestPrivate
{
public:
    QSize m_targetSize = QSize(128, 128);
    qreal m_dpr = 1;
};

ThumbnailRequest::ThumbnailRequest(): d(new ThumbnailRequestPrivate)
{
}

ThumbnailRequest::ThumbnailRequest(const QSize &targetSize, qreal dpr)
        : d(new ThumbnailRequestPrivate)
{
    d->m_targetSize = targetSize;
    d->m_dpr = dpr;
}
ThumbnailRequest::ThumbnailRequest(const ThumbnailRequest &other): d(new ThumbnailRequestPrivate(*other.d))
{
}
ThumbnailRequest &ThumbnailRequest::operator=(const ThumbnailRequest &other)
{
    *d = *other.d;
    return *this;
}
ThumbnailRequest &ThumbnailRequest::operator=(ThumbnailRequest &&other) noexcept
{
    d = other.d;
    other.d = nullptr;
    return *this;
}

ThumbnailRequest::~ThumbnailRequest()
{
    if(d) {
        delete d;
        d = nullptr;
    }
}

QSize ThumbnailRequest::targetSize() const
{
    return d->m_targetSize;
}

qreal ThumbnailRequest::devicePixelRatio() const
{
    return d->m_dpr;
}

class ThumbnailPrivate
{
public:
    QImage m_image;
};

Thumbnail::Thumbnail(const QImage &image): d(new ThumbnailPrivate)
{
    d->m_image = image;
}
Thumbnail::Thumbnail(): d(new ThumbnailPrivate)
{
}

Thumbnail::Thumbnail(const Thumbnail &other): d(new ThumbnailPrivate(*other.d))
{
}

Thumbnail &Thumbnail::operator=(const Thumbnail &other)
{
    *d = *other.d;
    return *this;
}

Thumbnail::~Thumbnail()
{
    if(d) {
        delete d;
        d = nullptr;
    }
}

QImage Thumbnail::image() const {
    return d->m_image;
}

bool Thumbnail::isValid() const {
    return !d->m_image.isNull();
}

Thumbnail &Thumbnail::operator=(Thumbnail &&other) noexcept
{
    d = other.d;
    other.d = nullptr;
    return *this;
}
