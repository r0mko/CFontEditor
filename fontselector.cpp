#include "fontselector.h"
#include <QTextCodec>
#include <QDebug>
#include <QFontMetrics>

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
        m_currentFont.setStyleStrategy(QFont::NoAntialias);
        qDebug() << "Set current font" << m_currentFont.family() << "size:" << m_pointSize;
    }
    
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
    return QFontMetrics(m_currentFont).height();
}

int FontSelector::fontWidth() const
{
    return QFontMetrics(m_currentFont).maxWidth();
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

void FontSelector::setEncoding(QString encoding)
{
    if (m_encoding == encoding)
        return;
    
    m_encoding = encoding;
    emit encodingChanged();
}
