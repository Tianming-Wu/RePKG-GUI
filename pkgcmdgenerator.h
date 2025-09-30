#ifndef PKGCMDGENERATOR_H
#define PKGCMDGENERATOR_H

#include <QObject>
#include <QProcess>
#include <QFile>

struct pkgExtractCmd {
    QString file, output;
    bool dontConvertTex, debug, singleDir, recursive, copyProject, useName, overWrite;
    QStringList ignoreExts, onlyExts;
};

struct pkgInfoCmd {
    QString file;

};

class PKGCmdGenerator : public QObject
{
    Q_OBJECT
public:
    explicit PKGCmdGenerator(QObject *parent = nullptr);

    void PkgExtract(const pkgExtractCmd &ec);
    void PkgInfo(const pkgInfoCmd &ic);

signals:
    void finished(int exitcode);
    void consoleOutput(const QString&);

private:
    QProcess proc;
    QString repkg_exec;
};

#endif // PKGCMDGENERATOR_H
