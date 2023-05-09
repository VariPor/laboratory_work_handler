#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextFrame>

#include "mainwindow.h"

class Block
{
  public:
    Block() {}
    ~Block() {}

};

class TextBlock : public Block
{
    QString text;
  public:
   TextBlock(QString text = "") : text{text} {  }
    ~TextBlock() {}
};

class PlotBlock : public Block
{
    QPicture picture;
  public:
    PlotBlock(QPicture picture) : picture{picture} {}
    ~PlotBlock() {}
};

class TableBlock : public Block
{
    QList<QList<QVariant>> table;
  public:
    TableBlock(QList<QList<QVariant>> table = QList<QList<QVariant>>()) : table{table} { }
    ~TableBlock() {}
};

#endif // BLOCK_H

