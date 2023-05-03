#include "manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::addVariable(const VariableData& var)
{
    variables.append(var);
    Manager::instance()->recalculationMeasurementCount();
}

void Manager::recalculationMeasurementCount() {
    measurement_count = 0;
    for (int i = 0; i < this->getVariablesCount(); ++i)
        if (variables.at(i).measurements.size() > measurement_count)
            measurement_count = variables.at(i).measurements.size();
    for (int i = 0; i < this->getCalculatedCount(); ++i)
        if (calculated.at(i).measurements.size() > measurement_count)
            measurement_count = calculated.at(i).measurements.size();
}

int Manager::getCalculatedCount() { return calculated.size(); }

void Manager::deleteVariable(int index)
{
    if (index < 0 || index > variables.count())
        throw std::out_of_range("There isn't a column with this index");
    variables.removeAt(index);
    Manager::instance()->recalculationMeasurementCount();
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
        if (variables[i].measurements.count() > num_row)
            variables[i].measurements.removeAt(num_row);
    Manager::instance()->recalculationMeasurementCount();
}

void Manager::addCalculated(const VariableData& var)
{
    calculated.append(var);
    Manager::instance()->recalculationMeasurementCount();
}

void Manager::clearCalculated()
{
    calculated.clear();
    Manager::instance()->recalculationMeasurementCount();
}

Manager *Manager::instance()
{
    return GlobalManager;
}

int Manager::getVariablesCount() { return variables.size(); }

int Manager::getMeasurementsCount() { return measurement_count; }

VariableData* Manager::getVariable(const QString& name)
{
    for (auto& v: variables)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    return nullptr;
}

VariableData* Manager::getVariable(int index)
{
    if (index >= variables.size()) throw std::runtime_error("No such index");
    return &variables[index];
}

VariableData* Manager::getCalculated(const QString& name)
{
    for (auto& v: calculated)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    throw std::runtime_error("No such index");
}

VariableData* Manager::getCalculated(int index)
{
    if (index >= variables.size()) throw std::runtime_error("No such index");
    return &calculated[index];
}


int Manager::getVarAndCalcCount() {
    return this->getCalculatedCount() + this->getVariablesCount();
}

void Manager::clear() {
    variables.clear();
    calculated.clear();
    measurement_count = 0;
}


