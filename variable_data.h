#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>

enum ErrorType
{
    relative,
    absolute,
    calculated
};

class VariableData
{
    QList<double> measurements;
    QString fullNaming;
    QString shortNaming;
    std::pair<ErrorType, double> instrumentError;
    QList<double> calcErrors;
    friend class Manager;
public:  
    double error(double measurement, int index = 0);
    VariableData(QString fullNaming, QString shortNaming = "", QList<double> meas = QList<double> {});
};

#endif // VARIABLEDATA_H
