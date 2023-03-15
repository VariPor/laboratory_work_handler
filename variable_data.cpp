#include <iostream>
#include "variable_data.h"

double VariableData::error(double measurement, int index)
{

  switch(int(VariableData::instrumentError.first))
  {
    case 0:
    { // relative error
      return VariableData::instrumentError.second * measurement;
    }
    case 1:
    { // absolute error
      return VariableData::instrumentError.second;
    }
    case 2:
    { // calculated error
        return calcErrors.at(index);
    }
    default: {
      throw "Wrong ErrorType!";
    }
  }
    
}


VariableData::VariableData(QString fullN, QString shortN, QList<double> meas)
    : fullNaming { fullN }, shortNaming { shortN }, measurements { meas }
{}
