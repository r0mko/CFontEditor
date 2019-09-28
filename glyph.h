#ifndef GLYPH_H
#define GLYPH_H

#include <QImage>
#include <QQuickPaintedItem>

class FontSelector;

class Glyph : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(FontSelector *fontSelector READ fontSelector WRITE setFontSelector NOTIFY fontSelectorChanged)
    Q_PROPERTY(int charCode READ charCode WRITE setCharCode NOTIFY charCodeChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    
    FontSelector *m_fontSelector = nullptr;
    int m_charCode = 0;
    QString m_glyph;
    int m_baseline;
    QColor m_color;
    QImage m_image;
    
public:
    Glyph(QQuickItem *parent = nullptr);
    
    FontSelector *fontSelector() const;
    void setFontSelector(FontSelector *fontSelector);
    
    int charCode() const;
    void setCharCode(int charCode);

    // QQuickPaintedItem interface
    virtual void paint(QPainter *painter) override;
    
    QColor color() const;
    void setColor(QColor color);
    
public slots:
    void fix();
    
signals:
    void fontSelectorChanged();
    void charCodeChanged();
    void colorChanged();
};

#endif // GLYPH_H
