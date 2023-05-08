#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextFrame>

#include "mainwindow.h"

class Block : QObject
{
    Q_OBJECT
  public:
    Block(QObject* parent = nullptr) : QObject(parent) {}
    ~Block() {}

};

class TextBlock : public Block
{
   QTextFrame text_frame;
  public:
   TextBlock(QTextDocument *parent = nullptr) : Block(parent), text_frame(parent) {  }
    ~TextBlock() {}
};

class PlotBlock : Block
{
  public:
    PlotBlock(QWidget *parent = nullptr) : Block(parent){}
    ~PlotBlock() {}
};

class TableBlock : public Block
{
    QTextTable text_table;
  public:
    TableBlock(QTextDocument *parent = nullptr) : text_table(parent), Block(parent) { text_table.appendColumns(3); }
    ~TableBlock() {}
};

#endif // BLOCK_H

