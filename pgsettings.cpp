#include "pgsettings.h"

#include <QApplication>

PGSettings::PGSettings(QObject *parent)
    : QObject{parent}
    , settings( QApplication::applicationDirPath() + "/repkg-gui.ini", QSettings::IniFormat, this)
{}

QString PGSettings::getOpenPath()
{
    QString result = getDefaultOpenPath();
    if(result.isEmpty()) result = getLastOpenPath();
    // if(result.isEmpty()) {
    // find wallpaper engine
    // }

    return result;
}
