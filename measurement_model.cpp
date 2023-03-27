#include "measurement_model.h"
#include "variable_data.h"
#include "manager.h"

int maxSizeOfMeasurement(const Manager& m)
{
    int max = 0;
    for (int i = 0; i < m.variables.size(); ++i)
    {
        max = std::max(m.variables[i].measurements.size(), max);
    }
    return max;
}

int MeasurementModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return maxSizeOfMeasurement(*Manager::instance()); //очень плохо срочно адекватную идею
}

int MeasurementModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Manager::instance()->variables.size();
}

QVariant MeasurementModel::data(const QModelIndex &index, int role) const
{
    int option = index.row();
    int variable  = index.column();

    if (Manager::instance()->variables[variable].measurements.size() <= option)
    {
        return QVariant();
    }

    switch (role)
    {
        case Qt::DisplayRole: //тоже плохо, надо что-то добавить
        {
            QString r = QVariant(Manager::instance()->variables[variable].measurements[option]).toString() + " ± " +
                    QVariant(Manager::instance() -> variables[variable].instrumentError.value).toString();
            return r;
        }

    }
    return QVariant();
}

QVariant MeasurementModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole )
    {
        return QVariant();
    }

    if( orientation == Qt::Vertical )
    {
        return section + 1;
    }

    return Manager::instance()->variables[section].fullNaming;
}

bool MeasurementModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    int option = index.row();
    int variable  = index.column();
    bool ok = true;

    if (role == Qt::EditRole)
    {
        if (!value.toDouble(&ok)) return false;
        if (!ok) return false;
        if (Manager::instance()->variables[variable].measurements.size() <= option)
        {
            Manager::instance()->variables[variable].measurements.append(value.toDouble());
            return true;
        }
        Manager::instance()->variables[variable].measurements[option] = value.toDouble();
        return true;
    }
    return false;
}

Qt::ItemFlags MeasurementModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
