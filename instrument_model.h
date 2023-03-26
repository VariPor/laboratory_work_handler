#ifndef INSTRUMENT_MODEL_H
#define INSTRUMENT_MODEL_H

#include <QAbstractTableModel>
#include <QObject>

#include "variable_data.h"

class InstrumentModel : public QAbstractTableModel {
 public:
  InstrumentModel(QObject* parent = nullptr) : QAbstractTableModel(parent){};
  ~InstrumentModel(){};

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
};

#endif // INSTRUMENT_MODEL_H
