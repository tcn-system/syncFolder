#ifndef SYNCFOLDER_H_
#define SYNCFOLDER_H_

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QString>
#include <QTextStream>

#include <QThread>

#include "structs.h"

class cReadFolder : public QThread {

public:
    void run();

    void setPath(QString _path, bool _exept_folders = true, bool _exept_files = true)
    {
        path = _path;
        exept_folders = _exept_folders;
        exept_files = _exept_files;
    }
    void setFolder(sFolder* _folder) { folder = _folder; }

private:
    QString path = "";
    bool exept_folders = true;
    bool exept_files = true;
    sFolder* folder;
};

class cCompareFolder : public QThread {

public:
    void run();

private:
};

class cSyncFolder {

public:
    cSyncFolder();

    sFolder readFolder(QString _path, bool exept_folders = true, bool exept_files = true);
    sCompare compareFolder(sFolder* _folder_src, sFolder* _folder_dst);

private:
    sReadInfo _readInfo;

    void readDirPath(QString _path, bool exept = true);
    void readFilePath(QString _path, bool exept = true);

    bool verifExeptDir(QString _path);
    bool verifExeptFileExt(QString _path);
};

#endif // SYNCFOLDER_H_
