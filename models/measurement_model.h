#ifndef MEASUREMENT_MODEL_H
#define MEASUREMENT_MODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "variable_data.h"

class MeasurementModel : public QAbstractTableModel
{
 public:
  MeasurementModel(QObject* parent = nullptr) : QAbstractTableModel(parent){}
  ~MeasurementModel(){};

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

  void insertColumn(int column);
  void removeColumn(int column);
  void insertRow(int row);
  void removeRows(int row, int count);

private:
  int extraRows = 0;
};

#endif // MEASUREMENT_MODEL_H
