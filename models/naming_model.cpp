#include "naming_model.h"
#include "variable_data.h"
#include "manager.h"

int NamingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVarAndCalcCount();
}

int NamingModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 2;   // short and full names
}

QVariant NamingModel::data(const QModelIndex &index, int role) const
{
    int variable = index.row();
    int option  = index.column();
    auto* name = Manager::instance()->getVarOrCalc(variable);

    switch (role)
    {
        case Qt::DisplayRole:
            switch (option)
            {
              case 0:
                return name->fullNaming;
              case 1:
                return name->shortNaming;
            }
    }
    return QVariant();
}

bool NamingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    auto* name = Manager::instance()->getVarOrCalc(variable);

    if (role == Qt::EditRole)
    {
        switch (option)
        {
          case 0:
            if (value.toString().isEmpty()) return false;
            name->fullNaming = value.toString();
            return true;
          case 1:
            if (value.toString().isEmpty()) return false;
            name->shortNaming = value.toString();
            return true;
        }
    }
    return false;
}

QVariant NamingModel::headerData( int section, Qt::Orientation orientation, int role ) const {
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if( orientation == Qt::Vertical )
    {
        return QString(Manager::instance()->getVarOrCalc(section)->shortNaming);
    }

    switch( section )
    {
    case 0:
        return QString( "Full" );
    case 1:
        return QString( "Short" );
    }
    return QVariant();
}

Qt::ItemFlags NamingModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

