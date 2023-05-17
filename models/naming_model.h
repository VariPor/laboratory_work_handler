#ifndef NAMING_MODEL_H
#define NAMING_MODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "variable_data.h"

class NamingModel : public QAbstractTableModel
{
 public:
  NamingModel(QObject* parent = nullptr) : QAbstractTableModel(parent){};
  ~NamingModel(){};

  int rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int columnCount(const QModelIndex& parent = QModelIndex()) const override;
  QVariant data(const QModelIndex& index,
                int role = Qt::DisplayRole) const override;

  QVariant headerData(int section,
                      Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;

  bool setData(const QModelIndex& index,
               const QVariant& value,
               int role = Qt::EditRole) override;
  Qt::ItemFlags flags(const QModelIndex& index) const override;

  void insertRow(int row);
  void removeRow(int row);
};


#endif // NAMING_MODEL_H
