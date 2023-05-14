#include "block.h"

Block::Block(int number) : deleteButton(new QPushButton), upButton(new QPushButton), downButton(new QPushButton), layout(new QHBoxLayout) {
    deleteButton->setObjectName("delete" + QString::number(number));
    upButton->setObjectName("up" + QString::number(number));
    downButton->setObjectName("down" + QString::number(number));
    layout->addWidget(deleteButton);
    layout->addWidget(upButton);
    layout->addWidget(downButton);
    deleteButton->setText("delete");
    upButton->setText("up");
    downButton->setText("down");
    deleteButton->show();
    upButton->show();
    downButton->show();
}

Block::~Block() {
    layout->removeWidget(deleteButton);
    layout->removeWidget(downButton);
    layout->removeWidget(upButton);
    layout->disconnect();
    deleteButton->hide();
    upButton->hide();
    upButton->hide();
    if (deleteButton != nullptr) delete deleteButton;
    if (upButton != nullptr) delete upButton;
    if (downButton != nullptr) delete downButton;
    if (layout != nullptr) delete layout;
}

TextBlock::TextBlock(QVBoxLayout* blockHolder, int number) : Block(number), editor(new QLineEdit){
    blockHolder->addLayout(layout);
    layout->addWidget(editor);
    editor->show();
}

void TextBlock::saveToDocument(QTextCursor* cursor) {
    cursor->insertText(editor->text());
    cursor->insertBlock();
}

void TextBlock::removeFromBlockHolder(QVBoxLayout* blockHolder) {
    blockHolder->removeItem(layout);
    editor->hide();
    deleteButton->hide();
    upButton->hide();
    downButton->hide();
}

void TextBlock::addToBlockHolder(QVBoxLayout* blockHolder, int position) {
    blockHolder->insertItem(position, layout);
    editor->show();
    deleteButton->show();
    upButton->show();
    downButton->show();
}

TextBlock::~TextBlock() {
    layout->removeWidget(editor);
    if (editor != nullptr) delete editor;
}

TableBlock::TableBlock(QVBoxLayout* blockHolder, int number) : Block(number), table { new QTableWidget } {
    auto* manager = Manager::instance();
    table->setColumnCount(manager->getVariableCount());
    table->setRowCount(manager->getMeasurementCount());

    for (int i = 0; i < manager->getVariableCount(); ++i) {
        QTableWidgetItem* item = new QTableWidgetItem (manager->getVariable(i)->shortNaming);
        table->setHorizontalHeaderItem(i, item);
    }

    for (int i = 0; i < manager->getVariableCount(); ++i)
        for (int j = 0; j < manager->getMeasurementCount(); ++j) {
                QTableWidgetItem* item = new QTableWidgetItem
                        (QString::number(manager->getVariable(i)->measurements.at(j)), QTableWidgetItem::Type);
                table->setItem(j, i, item);
                table->item(j, i)->setFlags(Qt::NoItemFlags);
        }
    blockHolder->addLayout(layout);
    layout->addWidget(table);
    table->show();
}

void TableBlock::saveToDocument(QTextCursor* cursor) {
    cursor->insertTable(table->rowCount() + 1, table->columnCount());
    for (int i = 0; i < table->columnCount(); ++i) {
        cursor->insertText(table->horizontalHeaderItem(i)->text());
        cursor->movePosition(QTextCursor::NextCell);
    }

    for (int i = 0; i < table->rowCount(); ++i)
        for (int j = 0; j < table->columnCount(); ++j) {
            cursor->insertText(table->item(i, j)->text());
            cursor->movePosition(QTextCursor::NextCell);
        }
    cursor->insertBlock();
}

void TableBlock::removeFromBlockHolder(QVBoxLayout* blockHolder) {
    blockHolder->removeItem(layout);
    table->hide();
    deleteButton->hide();
    upButton->hide();
    downButton->hide();
}

void TableBlock::addToBlockHolder(QVBoxLayout* blockHolder, int position) {
    blockHolder->insertItem(position, layout);
    table->show();
    deleteButton->show();
    upButton->show();
    downButton->show();
}

TableBlock::~TableBlock() {
    layout->removeWidget(table);
    if (table != nullptr) delete table;       
}

PlotBlock::PlotBlock(QPixmap pixmap, QVBoxLayout* blockHolder, int number) : Block(number), pixmap{ new QPixmap (pixmap) }, label { new QLabel } {
    label->setPixmap(pixmap);
    image = pixmap.toImage();
    blockHolder->addLayout(layout);
    layout->addWidget(label);
    label->show();
}

void PlotBlock::saveToDocument(QTextCursor* cursor) {
    QImage chartImage = image;
    cursor->document()->addResource(QTextDocument::ImageResource, QUrl(""), chartImage);

    QTextImageFormat imageFormat;
    imageFormat.setQuality(100);

    cursor->insertImage(imageFormat);
    cursor->insertBlock();
}

void PlotBlock::removeFromBlockHolder(QVBoxLayout* blockHolder) {
    blockHolder->removeItem(layout);
    label->hide();
    deleteButton->hide();
    upButton->hide();
    downButton->hide();
}

void PlotBlock::addToBlockHolder(QVBoxLayout* blockHolder, int position) {
    blockHolder->insertItem(position, layout);
    label->show();
    deleteButton->show();
    upButton->show();
    downButton->show();
}

PlotBlock::~PlotBlock() {
    layout->removeWidget(label);
    if (pixmap != nullptr) delete pixmap;
    if (label != nullptr) delete label;
}



