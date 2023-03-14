#ifndef MANAGER_H
#define MANAGER_H

#include <variable_data.h>
#include <QGlobalStatic>

class Manager
{
public:
   void addVariable(VariableData&);
   void deleteVariable(int);
   void addMeasurementRow(QList<double>&);
   void removeMeasurementRow(int);
   void clearCalculated();
   void addCalculated(VariableData&);
private:
   QList<VariableData> variables;
   QList<VariableData> calculated;
};

Q_GLOBAL_STATIC(Manager, StaticManager)

#endif // MANAGER_H
