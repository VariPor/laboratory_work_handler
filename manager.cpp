#include "manager.h"

Q_GLOBAL_STATIC(Manager, GlobalManager)

void Manager::addVariable(const VariableData& var)
{
    variables.append(var);
}

void Manager::recalculationMeasurementCount() {
    measurement_count = 0;
    for (int i = 0; i < this->getVariableCount(); ++i)
        if (variables.at(i).measurements.size() > measurement_count)
            measurement_count = variables.at(i).measurements.size();
    for (int i = 0; i < this->getCalculatedCount(); ++i)
        if (calculated.at(i).measurements.size() > measurement_count)
            measurement_count = calculated.at(i).measurements.size();
}

int Manager::getCalculatedCount() const { return calculated.size(); }

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

void Manager::addMeasurementRowWithZeros()
{
    for (int i = 0; i < getVariableAndCalculatedCount(); ++i)
    {
        getVariableOrCalculated(i)->measurements.append(0.);
    }
}

void Manager::removeMeasurementRow(int num_row)
{
    if (num_row < 0 || num_row >= measurement_count)
        throw std::out_of_range("Can't remove row");
    for (int i = 0; i < variables.count(); ++i)
        if (variables[i].measurements.count() > num_row)
            variables[i].measurements.removeAt(num_row);
    for (int i = 0; i < calculated.count(); ++i)
        if (calculated[i].measurements.count() > num_row)
            calculated[i].measurements.removeAt(num_row);
    recalculationMeasurementCount();
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

int Manager::getVariableCount() const { return variables.size(); }

int Manager::getMeasurementCount() const {
    Manager::instance()->recalculationMeasurementCount();
    return measurement_count;
}

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
    if (index >= variables.size()) throw std::runtime_error("No such index (in getVariable(int index))");
    return &variables[index];
}

VariableData* Manager::getCalculated(const QString& name)
{
    for (auto& v: calculated)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    throw std::runtime_error("No such index (in getCalculated(const QString& name))");
}

VariableData* Manager::getCalculated(int index)
{
    if (index >= calculated.size()) throw std::runtime_error("No such index (in getCalculated(int index))");
    return &calculated[index];
}


int Manager::getVariableAndCalculatedCount() const {
    return this->getCalculatedCount() + this->getVariableCount();
}

VariableData* Manager::getVariableOrCalculated(int index)
{
    if (index >= getVariableAndCalculatedCount()) throw std::runtime_error("No such index (in getVarOrCalc(int index))");
    if (index < getVariableCount()) return getVariable(index);
    else return getCalculated(index - getVariableCount());
}

VariableData* Manager::getVariableOrCalculated(const QString& name)
{
    for (auto& v: variables)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    for (auto& v: calculated)
    {
        if (v.shortNaming == name || v.fullNaming == name)
            return &v;
    }
    return nullptr;
}

void Manager::clear() {
    variables.clear();
    calculated.clear();
    measurement_count = 0;
}

bool Manager::isInManager(QString name) {
    for (auto var : variables)
        if (var.shortNaming == name) return true;
    for (auto var : calculated)
        if (var.shortNaming == name) return true;
    return false;
}

void Manager::deleteCalculated(int index)
{
    if (index < 0 || index >= calculated.count())
        throw std::out_of_range("There isn't a column with this index (from deleteCalculated)");
    calculated.removeAt(index);
}
