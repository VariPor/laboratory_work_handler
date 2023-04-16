#include "instrument_model.h"
#include "variable_data.h"
#include "manager.h"

int InstrumentModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->variables.size();
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
                return instrument.type;
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
            if (value.toString() == "relative")
                instrument.type = VariableData::Instrument::relative;
            if (value.toString() == "absolute")
                instrument.type = VariableData::Instrument::absolute;
            if (value.toString() == "calculated")
                instrument.type = VariableData::Instrument::calculated;
            return true;
          case 1:
            instrument.value = value.toDouble();
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
        return QString( "type" );
    case 1:
        return QString( "value" );
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

