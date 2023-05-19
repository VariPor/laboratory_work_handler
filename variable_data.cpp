#include "variable_data.h"
#include "manager.h"

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
    {VariableData::Instrument::ErrorType::relative, "Relative"},
    {VariableData::Instrument::ErrorType::absolute, "Absolute"},
    {VariableData::Instrument::ErrorType::calculated, "Calculated"},
};

double VariableData::getError(int index) const
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

int VariableData::getMeasurementCount() {return measurements.size();}

VariableData::VariableData(QString shortNaming, QString fullNaming, QList<double> meas, QList<double> calcErrors)
    : measurements { meas }, fullNaming { fullNaming }, shortNaming { shortNaming }, calcErrors{ calcErrors }
{
    if (!calcErrors.empty())
        instrumentError.type = Instrument::ErrorType::calculated;
}

VariableData::VariableData(int size)
{
    static int new_counter = 0;
    for (int i = 0; i < size; ++i) measurements.append(0);
    if (size == 0) measurements.append(0);

    while (Manager::instance()->isInManager(QString::number(new_counter))) new_counter++;
    shortNaming = QString::number(new_counter);
    fullNaming = QString("New") + shortNaming;
}
