#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QAbstractListModel>

class Glyph;


class ImageModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(Glyph* glyph READ glyph WRITE setGlyph NOTIFY glyphChanged)
    
    Glyph* m_glyph;
    
public:
    explicit ImageModel(QObject *parent = nullptr);
    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    
    
    Glyph* glyph() const
    {
        return m_glyph;
    }
    void setGlyph(Glyph* glyph)
    {
        if (m_glyph == glyph)
            return;
        
        m_glyph = glyph;
        emit glyphChanged();
    }
public slots:
signals:
    void glyphChanged();
    
};

#endif // IMAGEMODEL_H
