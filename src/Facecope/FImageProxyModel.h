#ifndef QIMAGEPROXYMODEL_H
#define QIMAGEPROXYMODEL_H
#include <QSet>
#include <QSortFilterProxyModel>

class FImageProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  FImageProxyModel(QObject *parent = 0);
  ~FImageProxyModel();
  bool filterAcceptsRow(int source_row, const QModelIndex &source_parent);

private:
  bool show_recognized;
  bool show_unrecognized;
  bool show_without_human;
  bool show_only_human;
  int min_human_number;
  QSet<int> allowed_id;
};

#endif // QIMAGEPROXYMODEL_H
