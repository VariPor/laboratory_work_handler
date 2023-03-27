#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>
#include <QColor>

class VariableData
{
public:
    QList<double> measurements;
    QString fullNaming;
    QString shortNaming;
    struct Instrument
    {
        enum ErrorType
        {
            relative,
            absolute,
            calculated
        } type = ErrorType::absolute;
        double value = 0;

        static constexpr int FILEDS = 2;
    } instrumentError;
    QList<double> calcErrors;

    struct VisualOptions
    {
        bool visible = true;
        int width = 1;
        QString line_type = "solid";
        QString point_type = "square";
        QColor color = "red";

        static constexpr int FILEDS = 5;
    } visual;

    double error(double measurement, int index = 0);
    VariableData(QString fullNaming, QString shortNaming = "", QList<double> meas = QList<double> {});
};

#endif // VARIABLEDATA_H
