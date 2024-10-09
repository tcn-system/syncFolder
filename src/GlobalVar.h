#ifndef VARGLOBALE_H_
#define VARGLOBALE_H_

#include <QSettings>
#include <QString>

#include "Define.h"
#include "structs.h"

#include "FileManager.h"
#include "tcnStyle.h"

class cGlobalVar {

public:
    cGlobalVar();
    ~cGlobalVar();

    cFileManager* fileManager;

    sFolder s_folderSrc;
    sFolder s_folderDst;

    sCompare s_compare;

    int idxFile;
    int idxFile_percent;

    bool b_src_exept_folders;
    bool b_src_exept_files;
    bool b_dst_exept_folders;
    bool b_dst_exept_files;

    QStringList _exeptDir;
    QStringList _exeptFile;

    QStringList _videoFile_ext;
    QStringList _cppFile_ext;

    bool is_video_file(QString _suffix);

    void save_Default_Ini_File();
    void save_Ini_File();
    bool read_Ini_File();

private:
};

extern cGlobalVar c_globalVar;

// extern QList<QStringList> _listProfile;

#endif // VARGLOBALE_H_
