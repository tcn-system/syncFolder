#include "GlobalVar.h"

#include "Define.h"

#include <QStorageInfo>

cGlobalVar::cGlobalVar()
{
    fileManager = new cFileManager(QDir::homePath() + _D_PROJET_PATH_FILE);
    fileManager->verifyAllDirCreate();

    fileManager->readParametres();

    s_folderSrc.init();
    s_folderDst.init();

    s_compare.init();

    idxFile = 0;
    idxFile_percent = 0;

    b_src_exept_folders = true;
    b_src_exept_files = true;
    b_dst_exept_folders = false;
    b_dst_exept_files = false;

    _exeptDir.clear();
    _exeptFile.clear();

    _videoFile_ext.clear();
    _cppFile_ext.clear();

    bool ini_exist = false;
    do {

        ini_exist = read_Ini_File();

        if (not ini_exist)
            save_Default_Ini_File();

    } while (not ini_exist);
}
cGlobalVar::~cGlobalVar()
{
}

bool cGlobalVar::is_video_file(QString _suffix)
{
    for (int i = 0; i < _videoFile_ext.size(); i++) {
        if (not _suffix.compare(_videoFile_ext.at(i)))
            return true;
    }

    return false;
}

void cGlobalVar::save_Default_Ini_File()
{
    QString fileNameIni = c_globalVar.fileManager->parameterDir().path() + "/parametres_" + cMake_projectVersion + ".ini";

    QSettings settings(fileNameIni, QSettings::IniFormat);

    settings.beginGroup("Generale");
    settings.setValue("_exeptDir", C_exeptDir);
    settings.setValue("_exeptFile", C_exeptFile);

    settings.setValue("_videoFile_ext", C_videoFile_ext);
    settings.setValue("_cppFile_ext", C_cppFile_ext);

    settings.endGroup();
}

void cGlobalVar::save_Ini_File()
{
    QString fileNameIni = c_globalVar.fileManager->parameterDir().path() + "/parametres_" + cMake_projectVersion + ".ini";

    QSettings settings(fileNameIni, QSettings::IniFormat);

    settings.beginGroup("Generale");
    settings.setValue("_exeptDir", _exeptDir);
    settings.setValue("_exeptFile", _exeptFile);

    settings.setValue("_videoFile_ext", _videoFile_ext);
    settings.setValue("_cppFile_ext", _cppFile_ext);

    settings.endGroup();
}

bool cGlobalVar::read_Ini_File()
{
    QString fileNameIni = c_globalVar.fileManager->parameterDir().path() + "/parametres_" + cMake_projectVersion + ".ini";

    QFile iniFile(fileNameIni);

    if (iniFile.exists()) {

        QSettings settings(fileNameIni, QSettings::IniFormat);

        _exeptDir = settings.value("Generale/_exeptDir").value<QStringList>();
        _exeptFile = settings.value("Generale/_exeptFile").value<QStringList>();

        _videoFile_ext = settings.value("Generale/_videoFile_ext").value<QStringList>();
        _cppFile_ext = settings.value("Generale/_cppFile_ext").value<QStringList>();

        return true;
    }
    return false;
}


qint64 cGlobalVar::get_storage_space_free(QString _path, QString &error)
{
    error = QString();

    QStorageInfo storage(_path);

    // qDebug() << "export root path: " <<storage.rootPath();
    // qDebug() << "volume name:" << storage.name();
    // qDebug() << "fileSystemType:" << storage.fileSystemType();
    // qDebug() << "size:" << storage.bytesTotal() / 1000 / 1000 << "MB";
    // qDebug() << "availableSize:" << storage.bytesAvailable() / 1000 / 1000 << "MB";

    if (storage.isValid() && storage.isReady()) {

        if (!storage.isReadOnly()) {

            return storage.bytesAvailable();

        } else {

            error = "No permission to write to current folder ";

            return -2;
        }

    } else {

        error = "Selected drive validity: "+ QString::number(storage.isValid()) + "or storage availability: " +QString::number(storage.isReady());

        return -1;
    }
}

qint64 cGlobalVar::verif_storage_space_free(QString _path , qint64 sizeFile , QString &error)
{
    error = QString();

    QFileInfo _finf(_path);

    QStorageInfo storage(_finf.absoluteDir().path());

    // qDebug() << "export root path: " <<storage.rootPath();
    // qDebug() << "volume name:" << storage.name();
    // qDebug() << "fileSystemType:" << storage.fileSystemType();
    // qDebug() << "size:" << storage.bytesTotal() / 1000 / 1000 << "MB";
    // qDebug() << "availableSize:" << storage.bytesAvailable() / 1000 / 1000 << "MB";

    if (storage.isValid() && storage.isReady()) {

        if (!storage.isReadOnly()) {

            float MBavailable = storage.bytesAvailable() / 1024 / 1024;

            if(storage.bytesAvailable() > sizeFile) {

                return storage.bytesAvailable();

            } else {

                error = "Not enough disk space, available disk space is only : " + QString::number(MBavailable);
                return -3;
            }

        } else {

            error = "No permission to write to current folder ";

            return -2;
        }

    } else {

        error = "Selected drive validity: "+ QString::number(storage.isValid()) + "or storage availability: " +QString::number(storage.isReady());

        return -1;
    }
}

cGlobalVar c_globalVar;

// QList<QStringList> _listProfile;
