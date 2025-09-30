#ifndef DROPABLELINEEDIT_H
#define DROPABLELINEEDIT_H

#include <QLineEdit>
#include <QWidget>

class DropableLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    DropableLineEdit(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void dropped(const QString&);
};

#endif // DROPABLELINEEDIT_H
