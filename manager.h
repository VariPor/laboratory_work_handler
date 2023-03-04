#ifndef MANAGER_H
#define MANAGER_H

#include <variable_data.h>

class Manager {
public:
   QList <VariableData> variables;
   void addVariable(VariableData);
   void deleteVariable();
};

#endif // MANAGER_H
