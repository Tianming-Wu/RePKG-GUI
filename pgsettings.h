#ifndef PGSETTINGS_H
#define PGSETTINGS_H

#include <QObject>
#include <QSettings>
#include <QApplication>

class PGSettings : public QObject
{
    Q_OBJECT
public:
    explicit PGSettings(QObject *parent = nullptr);

    // section [Application]
    inline QString getLanguage() { return settings.value("Application/Language").toString(); }

    inline bool getAutoExecute() { return settings.value("Application/AutoExecute", false).toBool(); }
    inline void setAutoExecute(bool e) { settings.setValue("Application/AutoExecute", e); }

    inline QString getRePKGPath() { return settings.value("Application/RePKGPath", QApplication::applicationDirPath() + "/RePKG.exe").toString(); }
    inline void setRePKGPath(const QString& path) { settings.setValue("Application/RePKGPath", path); }

    // section [Extract]
    inline bool getDontConvertTex() { return settings.value("Extract/DontConvertTex", false).toBool(); }
    inline void setDontConvertTex(bool e) { settings.setValue("Extract/DontConvertTex", e); }

    // section [Default]
    inline QString getDefaultOpenPath() { return settings.value("Default/DefaultOpenPath").toString(); }
    inline void setDefaultOpenPath(const QString& path) { settings.setValue("Default/DefaultOpenPath", path); }

    inline QString getDefaultOutputPathMatch() { return settings.value("Default/DefaultOutputPathMatch").toString(); }
    inline void setDefaultOutputPathMatch(const QString& match) { settings.setValue("Default/DefaultOutputPathMatch", match); }

    inline QString getDefaultOutputPathReplace() { return settings.value("Default/DefaultOutputPathReplace").toString(); }
    inline void setDefaultOutputPathReplace(const QString& rep) { settings.setValue("Default/DefaultOutputPathReplace", rep); }

    // section [History]
    inline QString getLastOpenPath() { return settings.value("History/LastOpenPath").toString(); }
    inline void setLastOpenPath(const QString& path) { settings.setValue("History/LastOpenPath", path); }

    QString getOpenPath();

signals:

private:
    QSettings settings;
};

#endif // PGSETTINGS_H
