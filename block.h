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
  protected:
    QPushButton* deleteButton;
    QHBoxLayout* layout;
  public:
    Block(int number);
    virtual ~Block();
    virtual void saveToDocument(QTextCursor* cursor) = 0;
    virtual void removeFromBlockHolder(QVBoxLayout* blockHolder) = 0;
    virtual QWidget* returnWidget() = 0;
    QPushButton* returnButton() { return deleteButton; }
};

class TextBlock : public Block
{
    QLineEdit* editor;
  public:
   TextBlock(QVBoxLayout* blockHolder, int number);
    ~TextBlock();
   virtual void saveToDocument(QTextCursor* cursor) override;
   virtual void removeFromBlockHolder(QVBoxLayout* blockHolder) override;
   virtual QWidget* returnWidget() override { editor; }

};

class PlotBlock : public Block
{
    QLabel* label;
    QPixmap* pixmap;
    QImage image;
  public:
    PlotBlock(QPixmap pixmap, QVBoxLayout* blockHolder, int number);
    ~PlotBlock();
    virtual void saveToDocument(QTextCursor* cursor) override;
    virtual void removeFromBlockHolder(QVBoxLayout* blockHolder) override;
    virtual QWidget* returnWidget() override { return label; }
};

class TableBlock : public Block
{
    QTableWidget* table;
  public:
    TableBlock(QVBoxLayout* blockHolder, int number);
    ~TableBlock();
    virtual void saveToDocument(QTextCursor* cursor) override;
    virtual void removeFromBlockHolder(QVBoxLayout* blockHolder) override;
    virtual QWidget* returnWidget() override { return table; }
};

#endif // BLOCK_H
