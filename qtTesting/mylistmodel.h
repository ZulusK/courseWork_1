#ifndef MYLISTMODEL_H
#define MYLISTMODEL_H

#include <QAbstractListModel>
#include <QList>
class MyListModel : public QAbstractListModel {
  Q_OBJECT

public:
  explicit MyListModel(const QStringList &strings, QObject *parent = 0)
      : QAbstractListModel(parent), stringList(strings){};

  // Header:
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  // Basic functionality:
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index,
                int role = Qt::DisplayRole) const override;
  void addData(const QString & str);

private:
  QStringList stringList;
};

#endif // MYLISTMODEL_H
