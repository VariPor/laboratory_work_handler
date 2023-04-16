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

QMap<VariableData::Instrument::ErrorType, QString> VariableData::Instrument::error_types = {
    {VariableData::Instrument::ErrorType::relative, "relative"},
    {VariableData::Instrument::ErrorType::absolute, "absolute"},
    {VariableData::Instrument::ErrorType::calculated, "calculated"},
};

double VariableData::error(int index)
{
  switch(int(VariableData::instrumentError.type))
  {
    case Instrument::ErrorType::relative:
      return VariableData::instrumentError.value * VariableData::measurements.at(index);
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
