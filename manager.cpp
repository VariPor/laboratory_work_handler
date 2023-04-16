#include "manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::addVariable(const VariableData& var)
{
    variables.append(var);
    if (measurement_count < var.measurements.size())
        measurement_count = var.measurements.size();
}

void Manager::deleteVariable(int index)
{
    if (index < 0 || index > variables.count())
        throw std::out_of_range("There isn't a column with this index");
    if (variables.at(index).measurements.size() == measurement_count)
    {
        measurement_count = 0;
        for (int i = 0; i < this->getVariablesCount(); ++i)
        {
            if (variables.at(i).measurements.size() > measurement_count && i != index)
                measurement_count = variables.at(i).measurements.size();
            if (variables.at(i).measurements.size() == variables.at(index).measurements.size() && i != index)
                break;
        }
    }

    variables.removeAt(index);
}

void Manager::addMeasurementRow(QList<double>& meas)
{
    if (meas.count() != variables.count())
        throw std::out_of_range("Too few or too many measurement");
    for (int i = 0; i < meas.count(); ++i)
        variables[i].measurements.append(meas[i]);
    measurement_count += 1;
}

void Manager::removeMeasurementRow(int num_row)
{
    if (num_row < 0 || num_row >= measurement_count)
        throw std::out_of_range("Can't remove row");
    for (int i = 0; i < variables.count(); ++i)
        variables[i].measurements.removeAt(i);
    measurement_count -= 1;
}

void Manager::addCalculated(const VariableData& var)
{
    calculated.append(var);
}

void Manager::clearCalculated()
{
    calculated.clear();
}

Manager *Manager::instance()
{
    return GlobalManager;
}

int Manager::getVariablesCount() { return variables.size(); }

int Manager::getMeasurementsCount() { return measurement_count; }

int Manager::getVariable(const QString& name)
{
    for (int i = 0; i < this->getVariablesCount(); ++i)
    {
        if (variables.at(i).shortNaming == name || variables.at(i).fullNaming == name)
            return i;
    }
    throw std::out_of_range("no variable with this name");
}




