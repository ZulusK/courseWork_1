/** @file
    @brief Declaration of the class for image view filtering
*/
#ifndef QIMAGEPROXYMODEL_H
#define QIMAGEPROXYMODEL_H
#include <FImage.h>
#include <FMainFacecopeModel.h>
#include <QSet>
#include <QSortFilterProxyModel>
class FImageProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  FImageProxyModel(FMainFacecopeModel &src_model, QObject *parent = 0);
  ~FImageProxyModel();
  bool filterAcceptsRow(int source_row, const QModelIndex &source_parent)const ;
  int getDisplaingPhotos();

public slots:
  void clear();
  void setShow_recognized(bool value);

  void setShow_unrecognized(bool value);

  void setShow_without_human(bool value);

  void setShow_only_human(bool value);

  void setMin_human_number(int value);
  void apply();

private:
  bool isValid(FImage *fimage)const;
  bool show_recognized;
  bool show_unrecognized;
  bool show_without_human;
  bool show_only_human;
  int min_human_number;
  QSet<int> allowed_id;
  FMainFacecopeModel *src_model;
};

#endif // QIMAGEPROXYMODEL_H
