#include <QDataStream>
#include <QTextStream>
#include <QFile>

#include "strategy_io.h"

void StrategyIO_CSV::load()
{
    QFile file("test.csv");
    if(!file.open(QIODevice::ReadOnly))
        {
            throw std::runtime_error(" error opening file: " + file.error());
            return;
        }
    QTextStream instream(&file);

    QString str = instream.readLine();
    QString name;
    for (int i = 0; i < str.size(); ++i)
    {
        if (str[i] == ',')
        {
            Manager::instance()->addVariable(VariableData (name));
            name.clear();
            continue;
        }
        name += str[i];
        if (i == str.size() - 1)
            Manager::instance()->addVariable(VariableData (name));
    }

    QList<double> data;
    //str = instream.readLine();
    while (!instream.atEnd())
    {
        double number;
        instream >> number;
        QString ch = instream.read(1);
        data.push_back(number);
        if (ch == '\n')     // end of string
        {
            Manager::instance()->addMeasurementRow(data);
            data.clear();
        }
    }
    file.close();
}
