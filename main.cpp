#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSharedMemory>
#include <QFile>
#include <QMessageBox>

#include "pgsettings.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PGSettings settings;

    QSharedMemory shared("RePKG-GUI_SingleInstanceMarker");
    if (!shared.create(1, QSharedMemory::ReadWrite)) {
        return 0;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "RePKG_GUI_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    QString repkgPath = settings.getRePKGPath();

    if (!QFile::exists(repkgPath)) {
        QMessageBox::critical(nullptr, QApplication::tr("FATAL"), QApplication::tr("RePKG not found."));
        return 1;
    }

    MainWindow w(settings);
    w.show();
    return a.exec();
}
