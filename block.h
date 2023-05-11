#ifndef BLOCK_H
#define BLOCK_H

#include <QWidget>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextEdit>
#include <QTextFrame>

#include "mainwindow.h"

class TextBlock;
class TableBlock;
class PlotBlock;

class Block
{

  public:
    Block() {}
    ~Block() {}
    virtual void saveToDocument() = 0;
    virtual TextBlock* textBlock() = 0;
    virtual TableBlock* tableBlock() = 0;
    virtual PlotBlock* plotBlock() = 0;
};

class TextBlock : public Block
{
  public:
   TextBlock() : Block(), editor(new QLineEdit) {}
    ~TextBlock() {}
   virtual void saveToDocument() override { }
   virtual TextBlock* textBlock() override { return this; }
   virtual TableBlock* tableBlock() override { return nullptr; }
   virtual PlotBlock* plotBlock() override { return nullptr; }
   QLineEdit* editor;

};

class PlotBlock : public Block
{
  public:
    PlotBlock(QPixmap pixmap) : pixmap{ new QPixmap (pixmap) }, label { new QLabel } {}
    ~PlotBlock() {}
    virtual void saveToDocument() override {}
    virtual TextBlock* textBlock() override { return nullptr; }
    virtual TableBlock* tableBlock() override { return nullptr; }
    virtual PlotBlock* plotBlock() override { return this; }
    QLabel* label;
    QPixmap* pixmap;
};

class TableBlock : public Block
{

  public:
    TableBlock() : table { new QTableWidget } {}
    ~TableBlock() {}
    virtual void saveToDocument() override {}
    virtual TextBlock* textBlock() override { return nullptr; }
    virtual TableBlock* tableBlock() override { return this; }
    virtual PlotBlock* plotBlock() override { return nullptr; }
    QTableWidget* table;
};

#endif // BLOCK_H
