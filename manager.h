#ifndef MANAGER_H
#define MANAGER_H

#include "variable_data.h"
#include "plots/plot.h"
#include <QGlobalStatic>

class Manager
{
public:
   void addVariable(const VariableData&);
   void deleteVariable(int index);
   void deleteCalculated(int index);
   void addMeasurementRow(QList<double>&);
   void addMeasurementRowWithZeros();
   void removeMeasurementRow(int index);
   void clearCalculated();
   void addCalculated(const VariableData&);
   int getVariableCount() const;
   int getVariableAndCalculatedCount() const;
   int getMeasurementCount() const;

   VariableData* getVariable(const QString& shortName);
   VariableData* getVariable(int index);
   VariableData* getCalculated(const QString& shortName);
   VariableData* getCalculated(int index);
   VariableData* getVariableOrCalculated(int index);
   VariableData* getVariableOrCalculated(const QString& name);

   void clear();
   int getCalculatedCount() const;

   bool isInManager(QString name);

   static Manager* instance();
   Plot *plot;

private:
   int measurement_count = 0;
   QList<VariableData> variables;
   QList<VariableData> calculated;
   void recalculationMeasurementCount();
};

#endif // MANAGER_H
