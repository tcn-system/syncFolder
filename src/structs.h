#ifndef STRUCTS_H
#define STRUCTS_H

#include <QList>
#include <QString>

struct sReadInfo {

    QString pathSrc;
    QString pathDest;

    int nbreDirectory;

    QStringList listDirRead;
    QStringList listFileRead;

    void init()
    {
        pathSrc = "";
        pathDest = "";

        nbreDirectory = 0;

        listDirRead.clear();
        listFileRead.clear();
    }
};

struct sFileInfo {

    QString path_full;
    QString path;
    long size;

    sFileInfo()
    {
        init();
    }
    void init()
    {
        path_full = "";
        path = "";
        size = 0;
    }
};

struct sDirInfo {

    QString path_full;
    QString path;

    sDirInfo()
    {
        init();
    }
    void init()
    {
        path_full = "";
        path = "";
    }
};

struct sFolder {

    QString folder_dir;
    qint64 folder_free_space_size;

    QList<sDirInfo> listDir;
    QList<sFileInfo> listFile;

    sFolder()
    {
        init();
    }
    void init()
    {
        folder_dir = "";
        folder_free_space_size = -1;

        listDir.clear();
        listFile.clear();
    }
};

struct sCompare {

    QString folder_src_dir;
    QString folder_dst_dir;

    QList<sDirInfo> listDirDelete;
    QList<sDirInfo> listDirEqual;

    QList<sFileInfo> listFileCopy;
    QList<sFileInfo> listFileModify;
    QList<sFileInfo> listFileDelete;
    QList<sFileInfo> listFileEqual;

    sCompare()
    {
        init();
    }
    void init()
    {
        folder_src_dir = "";
        folder_dst_dir = "";

        listDirDelete.clear();
        listDirEqual.clear();

        listFileCopy.clear();
        listFileModify.clear();
        listFileDelete.clear();
        listFileEqual.clear();
    }
};

#endif // STRUCTS_H
