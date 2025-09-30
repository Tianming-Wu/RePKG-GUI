#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(PGSettings &settings, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , settings(settings)
    , cmdgen(settings)
{
    ui->setupUi(this);

    // UI Init
    this->setFixedSize(this->size());

    QLabel *about = new QLabel(this);
    about->setText("<a href=\"https://github.com/Tianming-Wu/RePKG-GUI\">RePKG-GUI</a> by <a href=\"https://github.com/Tianming-Wu\">Tianming</a>");
    about->setStyleSheet("color: grey");
    about->setOpenExternalLinks(true);
    ui->statusbar->addWidget(about, 140);

    // Availability Test
    QString repkgVersion = cmdgen.getVersion();
    if(!repkgVersion.isEmpty()) {
        ui->label_repkgVersion->setText(repkgVersion);
    } else {
        QMessageBox::warning(this, "RePKG-GUI", tr("Failed to parse RePKG version"));
        // exit?
    }

    // Load settings into ui
    ui->dle_defaultOpenPath->setText(settings.getDefaultOpenPath());
    ui->cb_autoExec->setChecked(settings.getAutoExecute());
    ui->cb_dontConvertTex->setChecked(settings.getDontConvertTex());

    ui->dle_defaultOutputPathMatch->setText(settings.getDefaultOutputPathMatch());
    ui->dle_defaultOutputPathReplace->setText(settings.getDefaultOutputPathReplace());

    // Settings update
    connect(ui->dle_defaultOpenPath, &QLineEdit::editingFinished, this, [&]{ settings.setDefaultOpenPath(ui->dle_defaultOpenPath->text()); });
    connect(ui->cb_autoExec, &QCheckBox::clicked, &settings, &PGSettings::setAutoExecute);
    connect(ui->cb_dontConvertTex, &QCheckBox::clicked, &settings, &PGSettings::setDontConvertTex);

    // Browse buttons
    connect(ui->pb_selectSourcePath, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getOpenFileName(this, tr("Select PKG file"), settings.getOpenPath(), tr("PKG File (*.pkg);;Any (*)"));
        if(!path.isEmpty()) {
            updateSourceDir(path);
            ui->dle_sourcePath->setText(path);
            ui->dle_outputPath->setText(genOutputPath(path));
        }
    });
    connect(ui->pb_selectOutputPath, &QPushButton::clicked, this, [&]{
        QString path = QFileDialog::getExistingDirectory(this, tr("Select a output directory"), genOutputPath(ui->dle_sourcePath->text()));
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

    // Auto complete output dir
    connect(ui->dle_sourcePath, &DropableLineEdit::dropped, this, [&](const QString &source) {
        ui->dle_outputPath->setText(genOutputPath(source));
    });

    // Sub Process
    connect(&cmdgen, &PKGCmdGenerator::consoleOutput, ui->pte_log, &QPlainTextEdit::appendPlainText);
    connect(&cmdgen, &PKGCmdGenerator::finished, this, &MainWindow::execFinished);

    // Actions
    connect(ui->pb_Extract, &QPushButton::clicked, this, &MainWindow::startExtract);
    // connect(ui->dle_sourcePath, &QLineEdit::editingFinished, this, &MainWindow::startExtract); // This login isn't right

    // Auto Trigger
    connect(ui->dle_sourcePath, &DropableLineEdit::dropped, this, [&] { if(settings.getAutoExecute()) startExtract(); });

}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::genOutputPath(const QString& source)
{
    if(source.isEmpty()) return "";

    QString matchPattern = settings.getDefaultOutputPathMatch();
    QString replaceTemplate = settings.getDefaultOutputPathReplace();

    if (replaceTemplate.isEmpty()) {
        QFileInfo fileInfo(source);
        return fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + "_extracted";
    }

    if (matchPattern.isEmpty()) {
        return replaceTemplate;
    }

    QRegularExpression regex(matchPattern);

    if (!regex.isValid()) {
        // Not valid regex, fallback
        QFileInfo fileInfo(source);
        return fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + "_extracted";
    }

    QRegularExpressionMatch match = regex.match(source);
    if (match.hasMatch()) {
        // 执行替换，支持 $1, $2 等反向引用
        QString result = source;
        result.replace(regex, replaceTemplate);
        return result;
    } else {
        // 没有匹配，使用默认逻辑
        QFileInfo fileInfo(source);
        return fileInfo.absolutePath() + "/" + fileInfo.completeBaseName() + "_extracted";
    }
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

void MainWindow::startExtract()
{
    if(running || ui->dle_sourcePath->text().isEmpty()) return;
    pkgExtractCmd ec;

    ec.file = ui->dle_sourcePath->text();
    if(!QFile::exists(ec.file)) {
        setExtractResult(tr("ERROR: File not exists."), Qt::red);
        return;
    }

    ec.output = ui->dle_outputPath->text();
    ec.dontConvertTex = settings.getDontConvertTex();

    ui->pb_Extract->setEnabled(false);
    cmdgen.PkgExtract(ec);
    setExtractResult(tr("Extracting..."));
    running = true;
}

void MainWindow::setExtractResult(const QString &text, const QColor &color)
{
    ui->label_ExtractResult->setText(text);

    QColor actualColor = color.isValid() ? color : palette().color(QPalette::WindowText);
    QString style = QString("color: %1;").arg(actualColor.name());
    ui->label_ExtractResult->setStyleSheet(style);
}

void MainWindow::execFinished(int exitcode)
{
    running = false;
    if(exitcode != 0) {
        setExtractResult(tr("ERROR Occoured"), Qt::red);
    }

    ui->pb_Extract->setEnabled(true);
    setExtractResult(tr("Complete"));
}
