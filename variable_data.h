#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>

enum class ErrorType {
    relative,
    absolute
};

class VariableData {
public:
    QList<double> measurements;
    QString fullNaming;
    QString shortNaming;
    std::pair<ErrorType, double> instrumentError;
    double error(double measurement);
};

#endif // VARIABLEDATA_H
