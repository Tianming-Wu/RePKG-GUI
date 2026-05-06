#include "pgsettings.h"

#include <QApplication>

PGSettings::PGSettings(QObject *parent)
    : QObject{parent}
    , settings( QApplication::applicationDirPath() + "/repkg-gui.ini", QSettings::IniFormat, this)
{}

QString PGSettings::getOpenPath()
{
    QString result;

    if (getAutoFindWorkshopDir()) {
        result = getCachedOpenPath();
    } else {
        result = getDefaultOpenPath();
    }

    if (result.isEmpty()) result = getLastOpenPath();
    return result;
}
