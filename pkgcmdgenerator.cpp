#include "pkgcmdgenerator.h"

#include <QApplication>

PKGCmdGenerator::PKGCmdGenerator(QObject *parent)
    : QObject{parent}
{
    repkg_exec = QApplication::applicationDirPath() + "/repkg.exe";
    connect(&proc, &QProcess::readyRead, this, [&]() { emit consoleOutput(proc.readAll()); });
    connect(&proc, &QProcess::finished, this, [&](int exitcode) { emit finished(exitcode); });
}

void PKGCmdGenerator::PkgExtract(const pkgExtractCmd &ec)
{
    QStringList argl = { "extract", "-o", ec.output };



    if(ec.dontConvertTex) argl.append("--no-tex-convert");

    argl.append(ec.file);
    proc.execute(repkg_exec, argl);
}

void PKGCmdGenerator::PkgInfo(const pkgInfoCmd &ic)
{
    // not supported yet :(
}
