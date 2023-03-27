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
    : measurements { meas }, fullNaming { fullN }, shortNaming { shortN }
{
    for (int i = 0; i < measurements.size(); ++i)
    {
        calcErrors.append(0);
    }
}
