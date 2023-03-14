#include "manager.h"


void Manager::addVariable(VariableData& var)
{
    variables.append(var);
}

void Manager::deleteVariable(int index)
{
    if (index < 0 || index > variables.count())
        throw std::out_of_range("There isn't a column with this index");
    variables.removeAt(index);
}

void Manager::addMeasurementRow(QList<double>& meas)
{
    if (meas.count() != variables.count())
        throw std::out_of_range("Too few or too many measurement");
    for (int i = 0; i < meas.count(); ++i)
        variables[i].measurements.append(meas[i]);
}

void Manager::removeMeasurementRow(int num_row)
{
    if (num_row < 0 || num_row >= variables[0].measurements.count())
        throw std::out_of_range("Can't remove row");
    for (int i = 0; i < variables.count(); ++i)
        variables[i].measurements.removeAt(i);
}

void Manager::addCalculated(VariableData& var)
{
    calculated.append(var);
}

void Manager::clearCalculated()
{
    calculated.clear();
}
