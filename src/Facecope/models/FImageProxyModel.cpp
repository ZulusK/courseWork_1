#include "FImageProxyModel.h"

FImageProxyModel::FImageProxyModel(QObject *parent):QSortFilterProxyModel(parent){

}
FImageProxyModel::~FImageProxyModel(){

}

bool filterAcceptsRow(int source_row, const QModelIndex &source_parent){
    return true;
}

int FImageProxyModel::getDisplaingPhotos(){
    return this->rowCount();
}
