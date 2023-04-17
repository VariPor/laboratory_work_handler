#ifndef MANAGER_H
#define MANAGER_H

#include "variable_data.h"
#include "plot.h"
#include <QGlobalStatic>

class Manager
{
public:
   void addVariable(const VariableData&);
   void deleteVariable(int);
   void addMeasurementRow(QList<double>&);
   void removeMeasurementRow(int);
   void clearCalculated();
   void addCalculated(const VariableData&);
   int getVariablesCount();
   int getMeasurementsCount();
   int getVariable(const QString& name);

   static Manager* instance();

   QList<VariableData> variables;
   QList<VariableData> calculated;

   Plot *plot;
private:
   int measurement_count = 0;
};

#endif // MANAGER_H
