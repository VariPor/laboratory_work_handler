#include "naming_model.h"
#include "variable_data.h"
#include "manager.h"

#include <QColor>
#include <QColorDialog>

int NamingModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->variables.size();
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
    auto& name = Manager::instance() -> variables[variable];

    switch (role)
    {
        case Qt::DisplayRole:
            switch (option)
            {
              case 0:
                return name.fullNaming;
              case 1:
                return name.shortNaming;
            }
    }
    return QVariant();
}

bool NamingModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    bool ok = true;
    auto& name = Manager::instance() -> variables[variable];

    if (role == Qt::EditRole)
    {
        switch (option)
        {
          case 0:
            if (value.toString().isEmpty()) return false;
            name.fullNaming = value.toString();
            return true;
          case 1:
            if (value.toString().isEmpty()) return false;
            name.shortNaming = value.toString();
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
        return QString(Manager::instance() -> variables[section].fullNaming);
    }

    switch( section )
    {
    case 0:
        return QString( "full" );
    case 1:
        return QString( "short" );
    }
    return QVariant();
}

Qt::ItemFlags NamingModel::flags(const QModelIndex &index) const
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
