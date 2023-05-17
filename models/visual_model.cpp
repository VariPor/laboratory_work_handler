#include "visual_model.h"
#include "variable_data.h"
#include "manager.h"

enum Fields
{
    visibleField,
    widthField,
    pointTypeField,
    lineTypeField,
    colorField
};

int VisualModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVarAndCalcCount();
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
    auto& visual = Manager::instance()->getVarOrCalc(variable)->visual;

    switch (role)
    {
        case Qt::BackgroundColorRole:
            switch (option)
            {
              case Fields::visibleField:
                return visual.visible ? Qt::Checked : Qt::Unchecked;
              case Fields::colorField:
                return visual.color;
            }
         break;

        case Qt::CheckStateRole:
            switch (option)
            {
              case Fields::visibleField:
                return visual.visible ? Qt::Checked : Qt::Unchecked;
            }
            break;

        case Qt::DisplayRole:
            switch (option)
            {
              case Fields::widthField:
                return visual.width;
              case Fields::pointTypeField:
                return visual.point_types.value(visual.point_type);
              case Fields::lineTypeField:
                return visual.line_types.value(visual.line_type);
            }
    }
    return QVariant();
}

bool VisualModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int variable = index.row();
    int option  = index.column();
    bool ok = true;
    auto& visual = Manager::instance()->getVarOrCalc(variable)->visual;

    if (role == Qt::CheckStateRole)
    {
        switch (option)
        {
          case Fields::visibleField:
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
          case Fields::widthField:
            if (!value.toInt(&ok)) return false;
            if (!ok) return false;
            visual.width = value.toInt();
            emit dataChanged(index, index);
            return true;
          case Fields::pointTypeField:
            visual.point_type = VariableData::VisualOptions::point_types.key(value.toString());
            emit dataChanged(index, index);
            return true;
          case Fields::lineTypeField:
            visual.line_type = VariableData::VisualOptions::line_types.key(value.toString());
            emit dataChanged(index, index);
            return true;
          case Fields::colorField:
            visual.color = value.value<QColor>();
            emit dataChanged(index, index);
            return true;
        }
        emit dataChanged(index, index);
        return true;
    }
    emit dataChanged(index, index);
    return false;
}

QVariant VisualModel::headerData (int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Vertical) return QString(Manager::instance()->getVarOrCalc(section)->shortNaming);

    switch (section)
    {
      case Fields::visibleField:
        return QString("Visible");
      case Fields::widthField:
        return QString("Width");
      case Fields::pointTypeField:
        return QString("Point type");
      case Fields::lineTypeField:
        return QString("Line type");
      case Fields::colorField:
        return QString("Color");
    }
    return QVariant();
}

Qt::ItemFlags VisualModel::flags(const QModelIndex &index) const
{
    int option  = index.column();
    switch (option)
    {
      case Fields::visibleField:
        return Qt::ItemIsEnabled | Qt::ItemIsUserCheckable | QAbstractItemModel::flags(index);

      case Fields::widthField: case Fields::lineTypeField:
      case Fields::colorField:case Fields::pointTypeField:
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    }
    return QAbstractItemModel::flags(index);
}

void VisualModel::insertRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
}

void VisualModel::removeRow(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
}
