#include <iostream>
#include "variable_data.h"

double VariableData::error(double measurement, int index)
{

  switch(int(VariableData::instrumentError.type))
  {
    case Instrument::ErrorType::relative:
      return VariableData::instrumentError.value * measurement;
    case Instrument::ErrorType::absolute:
      return VariableData::instrumentError.value;
    case Instrument::ErrorType::calculated:
        return calcErrors.at(index);
    default:
      throw "Wrong ErrorType!";
  }
    
}


VariableData::VariableData(QString fullN, QString shortN, QList<double> meas)
    : fullNaming { fullN }, shortNaming { shortN }, measurements { meas }
{}
