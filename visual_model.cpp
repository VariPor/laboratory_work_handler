#include "visual_model.h"
#include "variable_data.h"
#include "manager.h"

#include <QColor>
#include <QColorDialog>

int VisualModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->variables.size();
}

int VisualModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return VariableData::VisualOptions::FILEDS;
}

QVariant VisualModel::data(const QModelIndex &index, int role) const
{
    int variable = index.row();
    int option  = index.column();
    auto& visual = Manager::instance() -> variables[variable].visual;

    switch (role)
    {
        case Qt::BackgroundColorRole:
            switch (option)
            {
                case 0:
                    return visual.visible ? Qt::Checked : Qt::Unchecked;
                case 4:
                    return visual.color;
            }
         break;

        case Qt::CheckStateRole:
            switch (option)
            {
            case 0:
                return visual.visible ? Qt::Checked : Qt::Unchecked;
            }
            break;

        case Qt::DisplayRole:
            switch (option)
            {
              case 0:
                return visual.visible;
              case 1:
                return visual.width;
              case 2:
                return visual.point_type;
              case 3:
                return visual.line_type;
            }
    }
    return QVariant();
}

bool VisualModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    bool ok = true;
    auto& visual = Manager::instance() -> variables[variable].visual;

    if (role == Qt::CheckStateRole)
    {
        switch (option)
        {
          case 0:
            if (!value.canConvert<int>()) return false;
            if (value.toInt() < Qt::Unchecked || value.toInt()> Qt::Checked) return false;
            auto state = static_cast<Qt::CheckState>(value.toInt());
            visual.visible = (state == Qt::Checked);
            return true;
          break;
        }
    }

    if (role == Qt::EditRole)
    {
        switch (option)
        {
          case 0:
            return visual.visible;
          case 1:
            if (!value.toInt(&ok)) return false;
            if (!ok) return false;
            visual.width = value.toInt();
            return true;
          case 2:
            visual.point_type = value.toString();
            return true;
          case 3:
            if (!value.canConvert<QString>()) return false;
            if (value.toString().isEmpty()) return false;
            visual.line_type = value.toString();
            return true;
          case 4:
            visual.color = value.value<QColor>();
            return true;
        }
        return true;
    }
    return false;
}

QVariant VisualModel::headerData( int section, Qt::Orientation orientation, int role ) const {
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
        return QString( "visible" );
    case 1:
        return QString( "width" );
    case 2:
        return QString( "point_type" );
    case 3:
        return QString( "line_type" );
    case 4:
        return QString( "color" );
    }
    return QVariant();
}

Qt::ItemFlags VisualModel::flags(const QModelIndex &index) const
{
    int option  = index.column();
    switch (option) {
        case 0:
            return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | QAbstractItemModel::flags(index);
        case 1:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case 2:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case 3:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
        case 4:
            return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    return Qt::ItemIsEditable;
}

