#include "pkgcmdgenerator.h"

#include <QApplication>

PKGCmdGenerator::PKGCmdGenerator(PGSettings &settings, QObject *parent)
    : QObject{parent}
    , settings(settings)
{
    proc.setProcessChannelMode(QProcess::MergedChannels);

    connect(&proc, &QProcess::readyRead, this, [&]() {
        emit consoleOutput(QString::fromLatin1(proc.readAll()));
    });

    connect(&proc, &QProcess::finished, this, [&](int exitcode) {
        emit consoleOutput(QString::fromLatin1(proc.readAll()));
        emit finished(exitcode);
    });
}

void PKGCmdGenerator::PkgExtract(const pkgExtractCmd &ec)
{
    QStringList argl = { "extract", "-o", ec.output };



    if(ec.dontConvertTex) argl.append("--no-tex-convert");

    argl.append(ec.file);
    proc.start(settings.getRePKGPath(), argl);
}

void PKGCmdGenerator::PkgInfo(const pkgInfoCmd &ic)
{
    // not supported yet :(
}

QString PKGCmdGenerator::getVersion()
{
    QProcess p;
    p.setProcessChannelMode(QProcess::MergedChannels);
    p.start(settings.getRePKGPath(), {"version"});
    return p.waitForFinished(1000) ? QString::fromLatin1(p.readAll()).trimmed() : "";
}
