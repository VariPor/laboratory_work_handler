#ifndef MANAGER_H
#define MANAGER_H

#include <variable_data.h>
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

   static Manager* instance();

   QList<VariableData> variables;
   QList<VariableData> calculated;

   Plot *plot;
};

#endif // MANAGER_H
