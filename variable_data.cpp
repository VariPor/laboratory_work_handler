#include "variable_data.h"
QMap<Qt::PenStyle, QString> VariableData::VisualOptions::line_types = {
    {Qt::SolidLine, "Solid"},
    {Qt::DashLine, "Dashed"},
    {Qt::DotLine, "Dotted"},
};

QMap<QCPScatterStyle::ScatterShape, QString> VariableData::VisualOptions::point_types = {
    {QCPScatterStyle::ScatterShape::ssNone, "None"},
    {QCPScatterStyle::ScatterShape::ssCross, "Cross"},
    {QCPScatterStyle::ScatterShape::ssCircle, "Circle"},
};

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
    : measurements { meas }, fullNaming { fullN }, shortNaming { shortN } {}
