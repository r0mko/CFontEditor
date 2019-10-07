#ifndef FONTMODEL_H
#define FONTMODEL_H
#include <QAbstractListModel>
#include <QFont>
#include <QVector>
#include <QImage>

class FontModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit FontModel(QObject *parent = nullptr);
    enum Roles {
        ImageRole = Qt::UserRole + 1,
        MaskRole,
        WidthRole,
        HeightRole,
    };

    // QAbstractItemModel interface
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;
public slots:
    void initFromFont(QFont font, const QString &encoding, bool antialiasing, bool renderAsPath = true);
    void createMasks();
    
private:
    QVector<QImage> m_images;
    QVector<QImage> m_masks;
};

#endif // FONTMODEL_H
