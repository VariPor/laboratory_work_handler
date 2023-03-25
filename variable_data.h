#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>

struct Instrument
{
    enum ErrorType
    {
        relative,
        absolute,
        calculated
    } type;
    double value;
};

class VariableData
{
public:
    QList<double> measurements;
    QString fullNaming;
    QString shortNaming;
    Instrument instrumentError;
    QList<double> calcErrors;

    struct VisualOptions
    {
        bool visible = true;
        int width = 1;
    } visual;

    double error(double measurement, int index = 0);
    VariableData(QString fullNaming, QString shortNaming = "", QList<double> meas = QList<double> {});
};

#endif // VARIABLEDATA_H
