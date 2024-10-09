#include "syncFolder.h"

#include "GlobalVar.h"

void cReadFolder::run()
{
    cSyncFolder* syncFolder = new cSyncFolder;
    folder->init();
    *folder = syncFolder->readFolder(path, exept_folders, exept_files);
    quit();
}

void cCompareFolder::run()
{
    cSyncFolder* syncFolder = new cSyncFolder;
    c_globalVar.s_compare.init();
    c_globalVar.s_compare = syncFolder->compareFolder(&c_globalVar.s_folderSrc, &c_globalVar.s_folderDst);
    quit();
}

cSyncFolder::cSyncFolder()
{
    _readInfo.init();
}

bool cSyncFolder::verifExeptDir(QString _path)
{
    for (int i = 0; i < c_globalVar._exeptDir.size(); i++) {

        if (_path.contains(c_globalVar._exeptDir.at(i)))
            return true;
    }
    return false;
}
bool cSyncFolder::verifExeptFileExt(QString _path)
{

    for (int i = 0; i < c_globalVar._exeptFile.size(); i++) {

        if (_path.contains(c_globalVar._exeptFile.at(i)))
            return true;
    }
    return false;
}

void cSyncFolder::readDirPath(QString _path, bool exept)
{
    QDir dir(_path);
    foreach (QFileInfo item, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
        if (item.isDir())
            if (item.absoluteFilePath().size() > dir.path().size())
                if (exept) {
                    if (not verifExeptDir(item.absoluteFilePath()))
                        _readInfo.listDirRead.push_back(item.absoluteFilePath());
                } else
                    _readInfo.listDirRead.push_back(item.absoluteFilePath());
    }
}

void cSyncFolder::readFilePath(QString _path, bool exept)
{
    QDir dir(_path);
    foreach (QFileInfo item, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
        if (item.isFile())
            if (exept) {
                if (not verifExeptFileExt(item.absoluteFilePath()))
                    _readInfo.listFileRead.push_back(item.absoluteFilePath());
            } else
                _readInfo.listFileRead.push_back(item.absoluteFilePath());
    }
}

sFolder cSyncFolder::readFolder(QString _path, bool exept_folders , bool exept_files)
{
    sFolder _folder;
    _folder.init();
    _folder.folder_dir = _path;

    _readInfo.init();
    _readInfo.pathSrc = _path;
    _readInfo.listDirRead.push_back(_readInfo.pathSrc);

    while (_readInfo.nbreDirectory < _readInfo.listDirRead.size()) {
        readFilePath(_readInfo.listDirRead.at(_readInfo.nbreDirectory), exept_files);
        readDirPath(_readInfo.listDirRead.at(_readInfo.nbreDirectory), exept_folders);
        _readInfo.nbreDirectory++;
    }

    foreach (QString dir, _readInfo.listDirRead) {
        if (dir.size() > _readInfo.pathSrc.size()) {

            QString _dstDir = dir;
            _dstDir.replace(_readInfo.pathSrc, "");

            sDirInfo _dirInfo;
            _dirInfo.path = _dstDir;
            _dirInfo.path_full = dir;
            _folder.listDir.push_back(_dirInfo);
        }
    }
    foreach (QString file, _readInfo.listFileRead) {

        QString _dstFile = file;
        _dstFile.replace(_readInfo.pathSrc, "");

        QFileInfo qfi_f_dst(file);

        sFileInfo _fileInfo;
        _fileInfo.path = _dstFile;
        _fileInfo.path_full = file;
        _fileInfo.size = qfi_f_dst.size();
        _folder.listFile.push_back(_fileInfo);
    }
    return _folder;
}

sCompare cSyncFolder::compareFolder(sFolder* _folder_src, sFolder* _folder_dst)
{
    sCompare _compare;
    _compare.init();

    _compare.folder_src_dir = _folder_src->folder_dir;
    _compare.folder_dst_dir = _folder_dst->folder_dir;

    ////
    ////    DIRECTORY
    ////

    for (int i_src = 0; i_src < _folder_src->listDir.size(); i_src++) {

        for (int i_dst = 0; i_dst < _folder_dst->listDir.size(); i_dst++) {

            if (not _folder_src->listDir.at(i_src).path.compare(_folder_dst->listDir.at(i_dst).path)) {

                _compare.listDirEqual.push_back(_folder_src->listDir.at(i_src));
            }
        }
    }

    for (int i_dst = 0; i_dst < _folder_dst->listDir.size(); i_dst++) {

        bool existe = false;

        for (int i_src = 0; i_src < _folder_src->listDir.size(); i_src++) {

            if (not _folder_dst->listDir.at(i_dst).path.compare(_folder_src->listDir.at(i_src).path)) {
                existe = true;
            }
        }
        if (not existe)
            _compare.listDirDelete.push_back(_folder_dst->listDir.at(i_dst));
    }

    ////
    ////    FILES
    ////

    for (int i_src = 0; i_src < _folder_src->listFile.size(); i_src++) {

        bool existe = false;

        QFileInfo _fileInfoSrc(_folder_src->listFile.at(i_src).path_full);

        for (int i_dst = 0; i_dst < _folder_dst->listFile.size(); i_dst++) {

            if (not _folder_src->listFile.at(i_src).path.compare(_folder_dst->listFile.at(i_dst).path)) {

                existe = true;

                QFileInfo _fileInfoDst(_folder_dst->listFile.at(i_dst).path_full);

                if (_fileInfoSrc.size() != _fileInfoDst.size()) {

                    _compare.listFileModify.push_back(_folder_src->listFile.at(i_src));

                } else if (_fileInfoSrc.lastModified().toSecsSinceEpoch() != _fileInfoDst.lastModified().toSecsSinceEpoch()) {

                    qDebug() << _fileInfoSrc.lastModified() << _fileInfoDst.lastModified();

                    if (c_globalVar.is_video_file(_fileInfoSrc.suffix()))
                        _compare.listFileEqual.push_back(_folder_src->listFile.at(i_src));
                    else
                        _compare.listFileModify.push_back(_folder_src->listFile.at(i_src));

                } else
                    _compare.listFileEqual.push_back(_folder_src->listFile.at(i_src));

                i_dst = _folder_dst->listFile.size();
            }
        }
        if (not existe) {
            _compare.listFileCopy.push_back(_folder_src->listFile.at(i_src));
        }
    }
    for (int i_dst = 0; i_dst < _folder_dst->listFile.size(); i_dst++) {

        bool existe = false;
        for (int i_src = 0; i_src < _folder_src->listFile.size(); i_src++) {

            if (not _folder_dst->listFile.at(i_dst).path.compare(_folder_src->listFile.at(i_src).path)) {
                existe = true;
                i_src = _folder_src->listFile.size();
            }
        }
        if (not existe) {
            _compare.listFileDelete.push_back(_folder_dst->listFile.at(i_dst));
        }
    }

    return _compare;
}
