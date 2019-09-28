#include "glyph.h"
#include "fontselector.h"
#include <QDebug>
#include <QFontMetrics>
#include <QPainter>
#include <QTextCodec>

Glyph::Glyph(QQuickItem *parent)
    : QQuickPaintedItem (parent)
{
    setFlag(QQuickItem::ItemHasContents);
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
    if (m_charCode == charCode || charCode < 32)
        return;
    m_charCode = charCode;
    emit charCodeChanged();
    fix();
    update();
}

void Glyph::paint(QPainter *painter)
{
    painter->drawImage(0, 0, m_image);
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
    m_glyph = codec->toUnicode(arr);
    QRect size = metrics.boundingRect(m_glyph);
    m_baseline = -size.top();
    int width = metrics.width(m_glyph) + metrics.leftBearing(m_glyph[0]) + metrics.rightBearing(m_glyph[0]);
    setImplicitWidth(width);
    setImplicitHeight(metrics.height());
    setWidth(width);
    setHeight(metrics.height());
    if (width <= 0 || size.height() <= 0)
        return;
    QImage img(QSize(width, metrics.height()), QImage::Format_Grayscale8);
    img.fill(0xff);
    QPainter painter(&img);
    
    QPen pen;
    pen.setColor(m_color);
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setRenderHint(QPainter::TextAntialiasing, false);
    painter.setFont(m_fontSelector->currentFont());
    painter.drawText(0, m_baseline, m_glyph);
    m_image = img;
    update();
}
