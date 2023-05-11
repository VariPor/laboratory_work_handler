#ifndef VARIABLEDATA_H
#define VARIABLEDATA_H

#include <QList>
#include <QString>
#include <utility>
#include <QColor>
#include "qcustomplot.h"

class VariableData
{
public:
    QList<double> measurements;
    QList<double> calcErrors;
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
        double value = 0.1;

        static QMap<VariableData::Instrument::ErrorType, QString> error_types;
        static constexpr int FILEDS = 2;
    } instrumentError;

    struct VisualOptions
    {
        bool visible = true;
        int width = 1;
        Qt::PenStyle line_type = Qt::SolidLine;
        QCPScatterStyle::ScatterShape point_type = QCPScatterStyle::ScatterShape::ssNone;
        QColor color = "black";

        static QMap<Qt::PenStyle, QString> line_types;
        static QMap<QCPScatterStyle::ScatterShape, QString> point_types;

        static constexpr int FILEDS = 5;
    } visual;

    double error(int index = 0);
    int getMeasurementsCount();
    VariableData(QString fullNaming, QString shortNaming = "",
                 QList<double> meas = QList<double> {}, QList<double> calcErrors = QList<double> {});
    VariableData(int size);
};

#endif // VARIABLEDATA_H
