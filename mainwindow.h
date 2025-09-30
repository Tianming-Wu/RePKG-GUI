#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pgsettings.h"
#include "pkgcmdgenerator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(PGSettings &settings ,QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString genOutputPath(const QString &source);

private slots:
    void updateSourceDir(const QString& path);
    void updateOutputDir(const QString& path);

    void startExtract();
    void setExtractResult(const QString& text, const QColor& color = QColor());

    void execFinished(int exitcode);

private:
    Ui::MainWindow *ui;

    PGSettings &settings;
    PKGCmdGenerator cmdgen;

    bool running = false;
};
#endif // MAINWINDOW_H
