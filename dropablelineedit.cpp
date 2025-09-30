#include "dropablelineedit.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

DropableLineEdit::DropableLineEdit(QWidget *parent)
    : QLineEdit(parent)
{
    setAcceptDrops(true);
}

void DropableLineEdit::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void DropableLineEdit::dropEvent(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();
        if (!urlList.isEmpty()) {
            QString filePath = urlList.first().toLocalFile();
            setText(filePath);
            event->acceptProposedAction();
        }
    }
}
