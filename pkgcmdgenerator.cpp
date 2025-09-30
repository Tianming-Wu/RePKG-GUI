#include "pkgcmdgenerator.h"

#include <QApplication>

PKGCmdGenerator::PKGCmdGenerator(PGSettings &settings, QObject *parent)
    : QObject{parent}
    , settings(settings)
{
    connect(&proc, &QProcess::readyRead, this, [&]() { emit consoleOutput(proc.readAll()); });
    connect(&proc, &QProcess::finished, this, [&](int exitcode) { emit finished(exitcode); });
}

void PKGCmdGenerator::PkgExtract(const pkgExtractCmd &ec)
{
    QStringList argl = { "extract", "-o", ec.output };



    if(ec.dontConvertTex) argl.append("--no-tex-convert");

    argl.append(ec.file);
    proc.execute(settings.getRePKGPath(), argl);
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
