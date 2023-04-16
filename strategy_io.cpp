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
        if (i + 1 == str.size())
            Manager::instance()->addVariable(VariableData (name));
    }

    QList<double> data;
    while (!instream.atEnd())
    {
        QString str = instream.readLine();
        QStringList num_strings = str.split(u',');
        for (QString num_str : num_strings)
        {
            bool ok;
            int num = num_str.toInt(&ok, 10);
            if (ok)
                data.push_back(num);
            else
                data.push_back(NAN);
        }
        for (int i = data.size(); i < Manager::instance()->getVariablesCount(); ++i)
            data.push_back(NAN);
        Manager::instance()->addMeasurementRow(data);
        data.clear();
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


    auto* manager = Manager::instance();
    auto& variables = Manager::instance()->variables;

    if (manager->getVariablesCount() > 0)
        for (int i = 0; i < manager->getVariablesCount(); ++i)
        {
            if (i == 0)
                outstream << variables.at(i).fullNaming;
            else
                outstream << "," << variables.at(i).fullNaming;
        }

        for (int i = 0; i < manager->getMeasurementsCount(); ++i) {
            for (int j = 0; j < manager->getVariablesCount(); ++j)
            {
                if (j == 0)
                    outstream << variables.at(i).measurements.at(j);
                else
                    outstream << "," << variables.at(i).measurements.at(j);
            }
            outstream << '\n';
        }
    file.close();
}
