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
                outstream << variables.at(i).shortNaming;
            else
                outstream << "," << variables.at(i).shortNaming;
        }
        outstream << '\r';

        for (int i = 0; i < manager->getMeasurementsCount(); ++i) {
            for (int j = 0; j < manager->getVariablesCount(); ++j)
            {
                if (j == 0)
                    outstream << variables.at(j).measurements.at(i);
                else
                    outstream << "," << variables.at(j).measurements.at(i);
            }
            outstream << '\r';
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

       variable.instrumentError.type = VariableData::Instrument::error_types.key(temp["instrumentErrors"].toObject()["type"].toString());
       if (variable.instrumentError.type != VariableData::Instrument::ErrorType::calculated)
           variable.instrumentError.value = temp["instrumentErrors"].toObject()["value"].toDouble();
       else {
           auto list = temp["instrumentErrors"].toObject()["value"].toArray();
           for (int i = 0; i < list.size(); ++i)
               variable.calcErrors.push_back(list[i].toDouble());
       }

       variable.visual.visible = temp["visualOptions"].toObject()["visible"].toBool();
       variable.visual.width = temp["visualOptions"].toObject()["width"].toInt();
       variable.visual.line_type = VariableData::VisualOptions::line_types.key(temp["visualOptions"].toObject()["line_type"].toString());
       variable.visual.point_type = VariableData::VisualOptions::point_types.key(temp["visualOptions"].toObject()["point_type"].toString());
       variable.visual.color = temp["visualOptions"].toObject()["color"].toString();
   }
}

void StrategyIO_JSON::save(const QString& output)
{
    QString val;
    QFile file;
    file.setFileName(output);
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    auto& variables = Manager::instance()->variables;

    QJsonArray array;
    for (int i = 0; i < variables.size(); ++i)
    {
        QJsonObject temp;
        QJsonObject names;
        names.insert("fullNaming", variables[i].fullNaming);
        names.insert("shortNaming", variables[i].shortNaming);
        temp.insert(QString::fromStdString("names"), QJsonValue (names));

        QJsonObject instrumentError;
        instrumentError.insert("type", VariableData::Instrument::error_types[variables[i].instrumentError.type]);
        instrumentError.insert("value", variables[i].error());
        temp.insert(QString::fromStdString("instrumentError"), QJsonValue (instrumentError));

        QJsonObject visualOptions;
        visualOptions.insert("visible", variables[i].visual.visible);
        visualOptions.insert("width", variables[i].visual.width);
        visualOptions.insert("color", variables[i].visual.color.name());
        visualOptions.insert("point_type", VariableData::VisualOptions::point_types[variables[i].visual.point_type]);
        visualOptions.insert("line_type", VariableData::VisualOptions::line_types[variables[i].visual.line_type]);
        temp.insert(QString::fromStdString("visualOptions"), QJsonValue (visualOptions));

        array.append(temp);
    }

    QJsonDocument d(array);
    file.write(d.toJson());

    file.close();
}
