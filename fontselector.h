#ifndef FONTSELECTOR_H
#define FONTSELECTOR_H

#include <QFont>
#include <QObject>
#include <QFontDatabase>
#include <QQmlParserStatus>
#include <QRect>

class FontSelector : public QObject
{
public:
    enum WritingSystem
    {
        Latin = QFontDatabase::Latin,
        Cyrillic = QFontDatabase::Cyrillic,
        Symbol = QFontDatabase::Symbol
    };
    Q_ENUM(WritingSystem)
    
    
private:
    Q_OBJECT
    Q_PROPERTY(QStringList fonts READ fonts NOTIFY fontsChanged)
    Q_PROPERTY(QStringList encodings READ encodings CONSTANT)

    Q_PROPERTY(QFont::Weight weight READ weight WRITE setWeight NOTIFY weightChanged)
    Q_PROPERTY(QString encoding READ encoding WRITE setEncoding NOTIFY encodingChanged)

    Q_PROPERTY(QFont currentFont READ currentFont NOTIFY currentFontChanged)
    Q_PROPERTY(int fontIndex READ fontIndex WRITE setFontIndex NOTIFY fontIndexChanged)
    Q_PROPERTY(int pointSize READ pointSize WRITE setPointSize NOTIFY pointSizeChanged)
    Q_PROPERTY(WritingSystem writingSystem READ writingSystem WRITE setWritingSystem NOTIFY writingSystemChanged)
    Q_PROPERTY(int fontHeight READ fontHeight NOTIFY fontRectChanged)
    Q_PROPERTY(int fontWidth READ fontWidth NOTIFY fontRectChanged)
    Q_PROPERTY(bool antialiased READ antialiased WRITE setAntialiased NOTIFY antialiasedChanged)
    Q_PROPERTY(QSize fontSize READ fontSize NOTIFY fontSizeChanged)

public:
    explicit FontSelector(QObject *parent = nullptr);

    QStringList fonts() const;
    QFont currentFont() const;

    int fontIndex() const;
    void setFontIndex(int fontIndex);

    WritingSystem writingSystem() const;
    void setWritingSystem(WritingSystem writingSystem);

    int pointSize() const;
    void setPointSize(int pointSize);

    QStringList encodings() const;
    QString encoding() const;
    void setEncoding(QString encoding);

    int fontHeight() const;
    int fontWidth() const;

    QRect fontRect() const;
    QSize fontSize() const;
    
    bool antialiased() const;
    void setAntialiased(bool antialiased);
    
    QFont::Weight weight() const;
    void setWeight(QFont::Weight weight);
    
    
signals:
    void currentFontChanged();
    void fontIndexChanged();
    void writingSystemChanged();
    void fontsChanged();
    void pointSizeChanged();
    void encodingChanged();
    void fontRectChanged();
    void antialiasedChanged();
    void weightChanged();
    void fontSizeChanged();

public slots:


private:
    void calculateBoundingBox();

    QFont m_currentFont;
    QFontDatabase m_database;
    int m_fontIndex;
    WritingSystem m_writingSystem = Latin;
    QString m_encoding;
    int m_pointSize = 12;
    QRect m_fontRect;
    bool m_antialiased = false;
};

#endif // FONTSELECTOR_H
