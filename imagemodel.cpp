#include "imagemodel.h"
#include "glyph.h"
#include <QDebug>
#include <QRgb>
ImageModel::ImageModel(QObject *parent)
    : QAbstractListModel(parent)
{
    
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    if (!m_glyph) {
        return 0;
    }
    return m_glyph->image().width() * m_glyph->image().height();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    if (!m_glyph)
        return QVariant();
    auto i = index.row();
    const QImage &image = m_glyph->image();
    return image.pixel(i % image.width(), i / image.width());
}
