#include "fontselector.h"
#include <QTextCodec>
#include <QDebug>
#include <QFontMetrics>

QRect FontSelector::fontRect() const
{
    return m_fontRect;
}

bool FontSelector::antialiased() const
{
    return m_antialiased;
}

void FontSelector::setAntialiased(bool antialiased)
{
    if (m_antialiased == antialiased)
        return;

    m_antialiased = antialiased;
    if (!m_antialiased) {
        m_currentFont.setStyleStrategy(QFont::NoAntialias);
    } else {
        m_currentFont.setStyleStrategy(QFont::PreferAntialias);
    }
    emit antialiasedChanged();
    emit currentFontChanged();
}

FontSelector::FontSelector(QObject *parent) : QObject(parent)
{

}

QStringList FontSelector::fonts() const
{
    return m_database.families(static_cast<QFontDatabase::WritingSystem>(m_writingSystem));
}

QFont FontSelector::currentFont() const
{
    return m_currentFont;
}

int FontSelector::fontIndex() const
{
    return m_fontIndex;
}

void FontSelector::setFontIndex(int fontIndex)
{
    if (m_fontIndex == fontIndex)
        return;

    m_fontIndex = fontIndex;
    if (m_fontIndex >=0 && m_fontIndex < fonts().size()) {
        m_currentFont = QFont(fonts()[m_fontIndex], m_pointSize);
        m_currentFont.setBold(m_bold);
        if (!m_antialiased) {
            m_currentFont.setStyleStrategy(QFont::NoAntialias);
        }
        qDebug() << "Set current font" << m_currentFont.family() << "size:" << m_pointSize;
    }

    calculateBoundingBox();
    emit currentFontChanged();
    emit fontIndexChanged();
    emit pointSizeChanged();
}

FontSelector::WritingSystem FontSelector::writingSystem() const
{
    return m_writingSystem;
}

void FontSelector::setWritingSystem(WritingSystem writingSystem)
{
    if (m_writingSystem == writingSystem)
        return;

    m_writingSystem = writingSystem;
    m_fontIndex = 0;
    calculateBoundingBox();
    emit fontIndexChanged();
    emit fontsChanged();
    emit writingSystemChanged();
}

int FontSelector::pointSize() const
{
    return m_currentFont.pointSize();
}

void FontSelector::setPointSize(int pointSize)
{
    if (m_pointSize == pointSize)
        return;
    m_currentFont.setPointSize(pointSize);
    m_pointSize = pointSize;
    calculateBoundingBox();
    emit pointSizeChanged();
}

QStringList FontSelector::encodings() const
{
    QStringList ret;
    for (auto a : QTextCodec::availableCodecs()) {
        QTextCodec *c = QTextCodec::codecForName(a);
        if (!c->canEncode("Йøä")) { // stupid way but it works: keep only 8-bit encodings
            ret.push_back(QString(a));
        }
    }
    return ret;

}

QString FontSelector::encoding() const
{
    return m_encoding;
}

int FontSelector::fontHeight() const
{
    return m_fontRect.height();
}

int FontSelector::fontWidth() const
{
    return m_fontRect.width();
}

bool FontSelector::bold() const
{
    return m_bold;
}

void FontSelector::setBold(bool bold)
{
    if (m_bold == bold)
        return;

    m_currentFont.setBold(bold);
    emit currentFontChanged();
    m_bold = bold;
    emit boldChanged();
}

void FontSelector::calculateBoundingBox()
{
    m_fontRect = QRect();
    if (m_encoding.isEmpty()) {
        return;
    }
    QTextCodec *codec = QTextCodec::codecForName(m_encoding.toLatin1());
    if (!codec) {
        qWarning() << "Unknown encoding" << m_encoding;
        return;
    }
    QFontMetrics metrics(m_currentFont);
    for (uint8_t c = 32; c < 255; ++c) {
        QByteArray ba;
        ba.append(static_cast<char>(c));
        QString glyph = codec->toUnicode(ba);
        m_fontRect = m_fontRect.united(metrics.boundingRect(glyph));
    }
    emit fontRectChanged();
    qDebug() << "Font rect for" << m_currentFont.family() << "is" << m_fontRect;
}

void FontSelector::setEncoding(QString encoding)
{
    if (m_encoding == encoding)
        return;

    m_encoding = encoding;
    calculateBoundingBox();
    emit encodingChanged();
}
