#include <QDataStream>
#include <QTextStream>
#include <QFile>

#include "strategy_io.h"

void StrategyIO_CSV::load(const QString& input)
{
    QFile file(input);
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
    while (!instream.atEnd())
    {
        double number;
        instream >> number;
        QString ch = instream.read(1);
        data.push_back(number);
        if (ch == '\r')      // end of string
        {
            Manager::instance()->addMeasurementRow(data);
            data.clear();
        }
    }
    file.close();
}

void StrategyIO_CSV::save(const QString& output)
{
    QFile file(output);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            throw std::runtime_error(" error opening file: " + file.error());
            return;
        }

    QTextStream outstream(&file);


    auto& variables = Manager::instance()->variables;

    if (variables.size() > 0)
        for (int i = 0; i < variables.size(); ++i)
        {
            if (i == 0)
                outstream << variables[i].fullNaming;
            else
                outstream << "," << variables[i].fullNaming;
        }

        for (int i = 0; i < variables[0].measurements.size(); ++i) {
            for (int j = 0; j < variables.size(); ++j)
            {
                if (j == 0)
                    outstream << variables[i].measurements[j];
                else
                    outstream << "," << variables[i].measurements[j];
            }
            outstream << '\n';
        }
    file.close();
}
