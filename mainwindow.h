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
    QString genOutputPath();

private slots:
    void updateSourceDir(const QString& path);
    void updateOutputDir(const QString& path);

    void start();

    void execFinished(int exitcode);

private:
    Ui::MainWindow *ui;

    PGSettings &settings;
    PKGCmdGenerator cmdgen;
};
#endif // MAINWINDOW_H
