#ifndef MANAGER_H
#define MANAGER_H

#include "variable_data.h"
#include "plots/plot.h"
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
   int getVarAndCalcCount();
   int getMeasurementsCount();
   VariableData* getVariable(const QString& shortName);
   VariableData* getVariable(int index);
   VariableData* getCalculated(const QString& shortName);
   VariableData* getCalculated(int index);
   void clear();
   int getCalculatedCount();
   VariableData* getVarOrCalc(int index);
   VariableData* getVarOrCalc(const QString& name);

   static Manager* instance();

   Plot *plot;
private:
   int measurement_count = 0;
   QList<VariableData> variables;
   QList<VariableData> calculated;
   void recalculationMeasurementCount();
};

#endif // MANAGER_H
