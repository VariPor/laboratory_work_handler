#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <QStyledItemDelegate>

class ColorDelegate : public QStyledItemDelegate
{
  Q_OBJECT
 public:
  ColorDelegate(QObject* parent = nullptr);
  ~ColorDelegate();

  QWidget* createEditor(QWidget* parent,
                        const QStyleOptionViewItem& option,
                        const QModelIndex& index) const override;
  void setEditorData(QWidget* editor, const QModelIndex& index) const override;
  void setModelData(QWidget* editor,
                    QAbstractItemModel* model,
                    const QModelIndex& index) const override;

 private:
};
#endif  // COLORDELEGATE_H
