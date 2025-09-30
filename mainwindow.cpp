#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(PGSettings &settings, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(settings)
{
    ui->setupUi(this);

    // UI Init
    this->setFixedSize(this->size());
    QLabel *about = new QLabel(this);
    about->setText("RePKG-GUI by Tianming");
    about->setStyleSheet("color: grey");
    ui->statusbar->addWidget(about, 140);

    // Load settings into ui
    ui->dle_defaultOpenPath->setText(settings.getDefaultOpenPath());
    ui->cb_autoExec->setChecked(settings.getAutoExecute());
    ui->cb_dontConvertTex->setChecked(settings.getDontConvertTex());

    // settings update
    connect(ui->dle_defaultOpenPath, &QLineEdit::editingFinished, this, [&]{ settings.setDefaultOpenPath(ui->dle_defaultOpenPath->text()); });
    connect(ui->cb_autoExec, &QCheckBox::clicked, &settings, &PGSettings::setAutoExecute);
    connect(ui->cb_dontConvertTex, &QCheckBox::clicked, &settings, &PGSettings::setDontConvertTex);

    // Browse buttons
    connect(ui->pb_selectSourcePath, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getOpenFileName(this, tr("Select PKG file"), settings.getOpenPath(), tr("PKG File (*.pkg);;Any (*)"));
        if(!path.isEmpty()) {
            updateSourceDir(path);
            ui->dle_sourcePath->setText(path);
        }
    });
    connect(ui->pb_selectOutputPath, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getExistingDirectory(this, tr("Select a output directory"), genOutputPath());
        if(!path.isEmpty()) {
            updateOutputDir(path);
            ui->dle_outputPath->setText(path);
        }
    });
    connect(ui->pb_defaultOpenPath, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getExistingDirectory(this, tr("Select a directory"), settings.getDefaultOpenPath());
        if(!path.isEmpty()) {
            ui->dle_defaultOpenPath->setText(path);
            settings.setDefaultOpenPath(path);
        }
    });

    // Auto save settings on DropEvent
    connect(ui->dle_sourcePath, &DropableLineEdit::dropped, this, &MainWindow::updateSourceDir);
    connect(ui->dle_outputPath, &DropableLineEdit::dropped, this, &MainWindow::updateOutputDir);

    // Sub Process
    connect(&cmdgen, &PKGCmdGenerator::consoleOutput, ui->pte_log, &QPlainTextEdit::appendPlainText);
    connect(&cmdgen, &PKGCmdGenerator::finished, this, &MainWindow::execFinished);

    // Actions
    connect(ui->pb_Extract, &QPushButton::clicked, this, &MainWindow::start);

    // Auto Trigger
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::genOutputPath()
{

    return QString();
}

void MainWindow::updateSourceDir(const QString &path)
{
    QDir fileDir = QFileInfo(path).absoluteDir();
    QString parentDir = fileDir.absolutePath();

    settings.setLastOpenPath(parentDir);
}

void MainWindow::updateOutputDir(const QString &path)
{
    settings.setLastOpenPath(path);
}

void MainWindow::start()
{
    pkgExtractCmd ec;

    ec.file = ui->dle_sourcePath->text();

    ui->pb_Extract->setEnabled(true);
    cmdgen.PkgExtract(ec);
}

void MainWindow::execFinished(int exitcode)
{
    if(exitcode != 0) {

    }

    ui->pb_Extract->setEnabled(true);
}
