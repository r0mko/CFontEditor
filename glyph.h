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
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QSize size READ size NOTIFY sizeChanged)
    Q_PROPERTY(QString glyph READ glyph NOTIFY glyphChanged)
    
    FontSelector *m_fontSelector = nullptr;
    int m_charCode = 0;
    QString m_glyph;
    int m_baseline;
    QColor m_color;
    QImage m_image;
    QSize m_size;
    QColor m_backgroundColor;
    
public:
    explicit Glyph(QQuickItem *parent = nullptr);
    ~Glyph() override;
    
    // QQmlParserStatus interface
    virtual void componentComplete() override;
    
    FontSelector *fontSelector() const;
    void setFontSelector(FontSelector *fontSelector);
    
    int charCode() const;
    void setCharCode(int charCode);

    // QQuickPaintedItem interface
    virtual void paint(QPainter *painter) override;
    
    QColor color() const;
    void setColor(QColor color);
    
    QSize size() const;
    
    QString glyph() const;
    
    const QImage &image() const;
    QImage &image();
    
    QColor backgroundColor() const;
    void setBackgroundColor(QColor backgroundColor);
    
    
public slots:
    void fix();
signals:
    void fontSelectorChanged();
    void charCodeChanged();
    void colorChanged();
    void sizeChanged();
    void glyphChanged();
    void backgroundColorChanged();
};

#endif // GLYPH_H
