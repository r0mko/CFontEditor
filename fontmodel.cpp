#include "fontmodel.h"

#include <QFontMetrics>
#include <QPainter>
#include <QRawFont>
#include <QTextCodec>
#include <QDebug>

FontModel::FontModel(QObject *parent)
    : QAbstractListModel(parent)
{
    
}

int FontModel::rowCount(const QModelIndex &parent) const
{
    return 256;
}

QVariant FontModel::data(const QModelIndex &index, int role) const
{
    int i = index.row();
    if (!index.isValid() || i < 0 || i > 255) {
        return QVariant();
    }
    const QImage &img = m_images.at(i);
    switch (role) {
    case ImageRole:
        return img;
        break;
    case MaskRole:
        if (m_masks.size() < i) {
            return m_masks.at(i);
        } else {
            return QImage();
        }
        break;
    case WidthRole:
        return img.width();
        break;
    case HeightRole:
        return img.height();
        break;
    default:
        break;
    }
    return QVariant();
}

QHash<int, QByteArray> FontModel::roleNames() const
{
    return {
        { ImageRole, "image" },
        { MaskRole, "mask" },
        { WidthRole, "glyphWidth"},
        { HeightRole, "glyphHeight"}
    };
}

void FontModel::initFromFont(QFont font, const QString &encoding, bool antialiasing, bool renderAsPath)
{
    QFontMetrics metrics(font);
    m_images.clear();
    m_images.resize(256);
    for (int ch = 32; ch < 256; ++ch) {
        QByteArray arr;
        arr.push_back(static_cast<char>(ch));
        QTextCodec *codec = QTextCodec::codecForName(encoding.toLatin1());
        if (!codec) {
            qWarning() << "Unknown encoding" + encoding;
            return;
        }
        QString glyph = codec->toUnicode(arr);
        QRect rect = metrics.boundingRect(glyph);
        int baseline = -rect.top();
        int width = rect.width();
        QSize size(width, metrics.height());
        QImage img(size, QImage::Format_ARGB32);
        img.fill(Qt::transparent);
        QPainter painter(&img);
        if (renderAsPath) {
            QRawFont rf = QRawFont::fromFont(font);
            auto glyphs = rf.glyphIndexesForString(glyph);
            QPainterPath p = rf.pathForGlyph(glyphs.first());
            painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing, antialiasing);
            painter.translate(0, baseline);
            painter.fillPath(p, QBrush(Qt::black));
        } else {
            painter.setPen(Qt::black);
            painter.drawText(0, baseline, glyph);
        }
        m_images[ch] = img;
    }
}

void FontModel::createMasks()
{
    m_masks.clear();
    m_masks.resize(256);
    for (int i = 0; i < 256; ++i) {
        const QImage &img = m_images.at(i);
        if (img.isNull()) {
            continue;
        }
        QImage mask = img.copy();
        QPainter painter(&mask);
        painter.drawImage(-1, -1, img);
        painter.drawImage(0, -1, img);
        painter.drawImage(1, -1, img);
        painter.drawImage(-1, 0, img);
        painter.drawImage(1, 0, img);
        painter.drawImage(-1, 1, img);
        painter.drawImage(0, 1, img);
        painter.drawImage(1, 1, img);
        m_masks[i] = mask;
    }
}
