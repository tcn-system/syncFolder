#ifndef DEFINE_H_
#define DEFINE_H_

#include <QList>
#include <QString>
#include <QStringList>

#define _D_ICON_PATH ":/images/tcnSystemIcon.png"
#define _D_PROJET_PATH_FILE "/tcn-system/" + cMake_projectName

const QStringList C_exeptDir = { "/0_Build", "/0_build", "/1_archive", "/1_Archive" };
const QStringList C_exeptFile = { ".txt.user", ".pro.user", "Thumbs.db", ".tcn.mp4" };

const QStringList C_videoFile_ext = { "ts", "mkv", "webm", "mp4", "mpeg", "m4v", "avi", "wmv", "flv", "mov" };
const QStringList C_cppFile_ext = { "cpp", "c", "h", "hpp" };

#endif // DEFINE_H_
