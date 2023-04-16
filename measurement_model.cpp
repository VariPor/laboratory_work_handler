#include "measurement_model.h"
#include "variable_data.h"
#include "manager.h"

int maxSizeOfMeasurement()
{
    int max = 0;
    for (int i = 0; i < Manager::instance()->variables.size(); ++i)
    {
        max = std::max(Manager::instance()->variables[i].measurements.size(), max);
    }
    return max;
}

int MeasurementModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return maxSizeOfMeasurement();
}

int MeasurementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->variables.size();
}

QVariant MeasurementModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int variable  = index.column();
    auto v = Manager::instance()->variables[variable];

    if (v.measurements.size() <= row) return QVariant();

    if (role == Qt::DisplayRole)
    {
        QString r = QVariant(v.measurements[row]).toString() + " ± " +
                    QVariant(v.instrumentError.value).toString();
        return r;
    }
    return QVariant();
}

QVariant MeasurementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) return QVariant();

    if (orientation == Qt::Vertical) return section + 1;

    return Manager::instance()->variables[section].fullNaming;
}

bool MeasurementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int row = index.row();
    int variable = index.column();
    auto m = Manager::instance();

    if (role == Qt::EditRole)
    {
        if (!value.canConvert<double>()) return false;
        if (m->variables[variable].measurements.size() <= row)
        {
            m->variables[variable].measurements.append(value.toDouble());
            emit dataChanged(index, index);
            return true;
        }
        m->variables[variable].measurements[row] = value.toDouble();
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

Qt::ItemFlags MeasurementModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
