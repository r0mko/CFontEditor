#ifndef FONTMODEL_H
#define FONTMODEL_H
#include <QAbstractListModel>
#include <QFont>
#include <QVector>
#include <QImage>

class FontModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(bool isEmpty READ isEmpty NOTIFY isEmptyChanged)
public:
    explicit FontModel(QObject *parent = nullptr);
    enum Roles {
        ImageRole = Qt::UserRole + 1,
        MaskRole,
        WidthRole,
        HeightRole,
        IsNullRole,
    };

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
    bool isEmpty() const;
    
public slots:
    void initFromFont(QFont font, const QString &encoding, bool antialiasing, bool renderAsPath = true);
    void createMasks();
    void clear();
signals:
    void isEmptyChanged();
    
private:
    void clearHelper();
    
    QVector<QImage> m_images;
    QVector<QImage> m_masks;
    bool m_isEmpty = true;
};

#endif // FONTMODEL_H
