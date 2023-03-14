#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>


class VariableData
{
    enum class ErrorType
    {
        relative,
        absolute,
        calculated
    };
    QList<double> measurements;
    QString fullNaming;
    QString shortNaming;
    std::pair<ErrorType, double> instrumentError;
    friend class Manager;
public:  
    double error(double measurement);
};

#endif // VARIABLEDATA_H
