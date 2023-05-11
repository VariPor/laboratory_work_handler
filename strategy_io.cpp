#include <QDataStream>
#include <QTextStream>
#include <QFile>
#include <QDebug>

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

    Manager::instance()->clear();

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

    if (manager->getVariablesCount() > 0)
        for (int i = 0; i < manager->getVariablesCount(); ++i)
        {
            if (i == 0)
                outstream << manager->getVariable(i)->shortNaming;
            else
                outstream << "," << manager->getVariable(i)->shortNaming;
        }
        outstream << endl;

        for (int i = 0; i < manager->getMeasurementsCount(); ++i) {
            for (int j = 0; j < manager->getVariablesCount(); ++j)
            {
                if (j == 0)
                    outstream << manager->getVariable(j)->measurements.at(i);
                else
                    outstream << "," << manager->getVariable(j)->measurements.at(i);
            }
            outstream << endl;
        }
    file.close();
}

void StrategyIO_JSON::load(const QString& input)
{
   QString val;
   QFile file;
   file.setFileName(input);
   file.open(QIODevice::ReadOnly | QIODevice::Text);
   val = file.readAll();
   file.close();

   QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
   QJsonArray array = d.array();
   for (int i = 0; i < array.size(); ++i)
   {
       QJsonObject temp = array[i].toObject();
       QString short_name = temp["names"].toObject()["shortNaming"].toString();

       auto& variable = *Manager::instance()->getVariable(short_name);

       variable.fullNaming = temp["names"].toObject()["fullNaming"].toString();

       variable.instrumentError.type = VariableData::Instrument::error_types.key((temp["instrumentErrors"].toObject()["type"]).toString());

       variable.instrumentError.value = temp["instrumentError"].toObject()["value"].toDouble();


       variable.visual.visible = temp["visualOptions"].toObject()["visible"].toBool();
       variable.visual.width = temp["visualOptions"].toObject()["width"].toInt();
       variable.visual.line_type = VariableData::VisualOptions::line_types.key(temp["visualOptions"].toObject()["line_type"].toString());
       variable.visual.point_type = VariableData::VisualOptions::point_types.key(temp["visualOptions"].toObject()["point_type"].toString());
       variable.visual.color = temp["visualOptions"].toObject()["color"].toString();
   }
}

void StrategyIO_JSON::save(const QString& output)
{
    QFile file;
    file.setFileName(output);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    auto* manager = Manager::instance();

    QJsonArray array;
    for (int i = 0; i < manager->getVariablesCount(); ++i)
    {
        QJsonObject temp;

        QJsonObject names;
        names["fullNaming"] = manager->getVariable(i)->fullNaming;
        names["shortNaming"] = manager->getVariable(i)->shortNaming;

        QJsonObject instrumentError;
        instrumentError["type"] =  VariableData::Instrument::error_types[manager->getVariable(i)->instrumentError.type];
        instrumentError["value"] = manager->getVariable(i)->error();

        QJsonObject visualOptions;
        visualOptions["visible"] = manager->getVariable(i)->visual.visible;
        visualOptions["width"] = manager->getVariable(i)->visual.width;
        visualOptions["color"] = manager->getVariable(i)->visual.color.name();
        visualOptions["point_type"] = VariableData::VisualOptions::point_types[manager->getVariable(i)->visual.point_type];
        visualOptions["line_type"] = VariableData::VisualOptions::line_types[manager->getVariable(i)->visual.line_type];

        temp["names"] = QJsonValue (names);
        temp["instrumentError"] = QJsonValue (instrumentError);
        temp["visualOptions"] = QJsonValue (visualOptions);


        array.append(temp);
    }

    QJsonDocument d(array);
    file.write(d.toJson());

    file.close();
}
