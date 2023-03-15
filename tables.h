#ifndef TABLES_H
#define TABLES_H

#include <QAbstractTableModel>

#include "variable_data.h"

struct MeasurementModel : QAbstractTableModel
{
    int rowCount();
    int ColoumnCount();
    VariableData& data(int index);
    void setData(int index, VariableData& value);
};

struct MeasurementView : QTableView
{
    void setModel();
};

struct VisualModel : QAbstractTableModel
{
    int rowCount();
    int ColoumnCount();
    VariableData& data(int index);
    void setData(int index, VariableData& value);
};

struct VisualView : QTableView
{
    void setModel();
};

struct InstrumentModel : QAbstractTableModel
{
    int rowCount();
    int ColoumnCount();
    VariableData& data(int index);
    void setData(int index, VariableData& value);
};

struct InstrumentView : QTableView
{
    void setModel();
};

struct NamingModel : QAbstractTableModel
{
    int rowCount();
    int ColoumnCount();
    VariableData& data(int index);
    void setData(int index, VariableData& value);
};

struct NamingView : QTableView
{
    void setModel();
};

#endif // TABLES_H
