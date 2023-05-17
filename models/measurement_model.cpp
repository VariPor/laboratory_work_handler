#include "measurement_model.h"
#include "variable_data.h"
#include "manager.h"

int MeasurementModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getMeasurementsCount() + extraRows;
}

int MeasurementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->getVariableAndCalculatedCount();
}

QVariant MeasurementModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int variable  = index.column();
    VariableData* v = Manager::instance()->getVariableOrCalculated(variable);

    if (v->measurements.size() <= row) return QVariant();

    if (role == Qt::DisplayRole)
    {
        QVariant r = QVariant(v->measurements[row]).toString() + " ± " +
                    QVariant(v->getError(row)).toString();
        return r;
    }
    return QVariant();
}

QVariant MeasurementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Vertical) return section + 1;

    VariableData* v = Manager::instance()->getVariableOrCalculated(section);

    return v->shortNaming;
}

bool MeasurementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int variable = index.column();

    if (role == Qt::EditRole)
    {
        if (!value.canConvert<double>()) return false;
        VariableData* v = Manager::instance()->getVariableOrCalculated(variable);

        if (v->measurements.size() <= row)
        {
            v->measurements.append(value.toDouble());
            emit dataChanged(index, index);
            return true;
        }
        v->measurements[row] = value.toDouble();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MeasurementModel::flags(const QModelIndex &index) const
{
    if (index.column() < Manager::instance()->getVariableCount())
        return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
    else
        return QAbstractItemModel::flags(index);
}

void MeasurementModel::insertColumn(int column)
{
    beginInsertColumns(QModelIndex(), column, column);
    endInsertColumns();
}

void MeasurementModel::insertRow(int row)
{
    beginInsertRows(QModelIndex(), row, row);
    endInsertRows();
    extraRows++;
}

