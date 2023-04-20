#include "instrument_model.h"
#include "variable_data.h"
#include "manager.h"

int InstrumentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVariablesCount();
}

int InstrumentModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return VariableData::Instrument::FILEDS;
}

QVariant InstrumentModel::data(const QModelIndex &index, int role) const
{
    int variable = index.row();
    int option  = index.column();
    auto& instrument = Manager::instance() -> variables[variable].instrumentError;

    switch (role)
    {
        case Qt::DisplayRole:
            switch (option)
            {
              case 0:
                return instrument.error_types.value(instrument.type);
              case 1:
                return instrument.value;
            }
    }
    return QVariant();
}

bool InstrumentModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    auto& instrument = Manager::instance() -> variables[variable].instrumentError;

    if (role == Qt::EditRole)
    {
        switch (option)
        {
          case 0:
            instrument.type = VariableData::Instrument::error_types.key(value.toString());
            emit dataChanged(index, index);
            return true;
          case 1:
            instrument.value = value.toDouble();
            emit dataChanged(index, index);
            return true;
        }
    }
    return false;
}

QVariant InstrumentModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if( orientation == Qt::Vertical )
    {
        return QString(Manager::instance() -> variables[section].fullNaming);
    }

    switch( section )
    {
    case 0:
        return QString( "Type" );
    case 1:
        return QString( "Value" );
    }
    return QVariant();
}

Qt::ItemFlags InstrumentModel::flags(const QModelIndex &index) const
{
    int option  = index.column();
    switch (option) {
        case 0:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case 1:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    return Qt::ItemIsEditable;
}

