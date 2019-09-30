#include "glyph.h"
#include "fontselector.h"
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QTextCodec>



Glyph::Glyph(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_color = QColor(Qt::black);
    m_backgroundColor = QColor(Qt::transparent);
}

Glyph::~Glyph()
{
}

void Glyph::componentComplete()
{
    QQuickPaintedItem::componentComplete();
    if (m_fontSelector)
        update();
}

FontSelector *Glyph::fontSelector() const
{
    return m_fontSelector;
}

void Glyph::setFontSelector(FontSelector *fontSelector)
{
    
    if (m_fontSelector == fontSelector)
        return;
    
    if (m_fontSelector) {
        disconnect(m_fontSelector, nullptr, this, nullptr);
    }
    
    m_fontSelector = fontSelector;
    connect(m_fontSelector, &FontSelector::pointSizeChanged, this, &Glyph::fix);
    connect(m_fontSelector, &FontSelector::currentFontChanged, this, &Glyph::fix);
    connect(m_fontSelector, &FontSelector::encodingChanged, this, &Glyph::fix);
    emit fontSelectorChanged();
}

int Glyph::charCode() const
{
    return m_charCode;
}

void Glyph::setCharCode(int charCode)
{
    if (m_charCode == charCode || charCode < 32) {
        return;
    }
    setFlag(QQuickItem::ItemHasContents);
    m_charCode = charCode;
    emit charCodeChanged();
    fix();
    update();
}

void Glyph::paint(QPainter *painter)
{
    painter->drawImage(QPoint(), m_image);
}

QColor Glyph::color() const
{
    return m_color;
}

void Glyph::setColor(QColor color)
{
    if (m_color == color)
        return;
    
    m_color = color;
    emit colorChanged();
    update();
}

QSize Glyph::size() const
{
    return m_size;
}

QString Glyph::glyph() const
{
    return m_glyph;
}

const QImage &Glyph::image() const
{
    return m_image;
}

QImage &Glyph::image()
{
    return m_image;
}

QColor Glyph::backgroundColor() const
{
    return m_backgroundColor;
}

void Glyph::setBackgroundColor(QColor backgroundColor)
{
    if (m_backgroundColor == backgroundColor)
        return;
    
    m_backgroundColor = backgroundColor;
    emit backgroundColorChanged();
}

void Glyph::fix()
{
    if (!m_fontSelector) {
        return;
    }
    QFontMetrics metrics(m_fontSelector->currentFont());
    QByteArray arr;
    arr.push_back(static_cast<char>(m_charCode));
    QTextCodec *codec = QTextCodec::codecForName(m_fontSelector->encoding().toLatin1());
    if (!codec) {
        qWarning() << "Unknown encoding" + m_fontSelector->encoding();
        return;
    }
    QString glyph = codec->toUnicode(arr);
    if (m_glyph != glyph) {
        m_glyph = glyph;
        emit glyphChanged();
    }
    QRect rect = metrics.boundingRect(m_glyph);
    m_baseline = -rect.top();
    int width = rect.width(); //metrics.width(m_glyph) + metrics.leftBearing(m_glyph[0]) + metrics.rightBearing(m_glyph[0]);
    setImplicitWidth(width);
    setImplicitHeight(metrics.height());
//    setWidth(width);
//    setHeight(metrics.height());
    if (width <= 0 || rect.height() <= 0)
        return;
    QSize size(width, metrics.height());
    QImage img(size, QImage::Format_ARGB32_Premultiplied);
    if (size != m_size) {
        m_size = size;
        emit sizeChanged();
    }
    img.fill(m_backgroundColor);
    QPainter painter(&img);
    
    painter.setPen(m_color);
    painter.setFont(m_fontSelector->currentFont());
    painter.drawText(0, m_baseline, m_glyph);
    m_image = img;
    update();
}
