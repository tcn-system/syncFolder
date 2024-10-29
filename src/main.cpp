#include <QApplication>
#include <QFile>
#include <QIcon>
#include <QScreen>
#include <QTextStream>
#include <QtCore/QCoreApplication>

#include "Define.h"
#include "mainwindow.h"
#include "tcnStyle.h"

#ifdef _WIN32
//#include <iostream>
//#include <psapi.h>
#include <windows.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

void create_cqtdeploy_file();

int main(int argc, char* argv[])
{
    // cqtdeployer -bin syncFolder -qmake ~/Qt/5.15.2/gcc_64/bin/qmake

    QApplication app(argc, argv);

    create_cqtdeploy_file();

    c_tcnStyle = new cTcnStyle(&app, e_profile_choose_standard);
    c_tcnStyle->load_tcnStyle();

    cMainWindow w;

    w.setWindowTitle(cMake_projectName + QString(" ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
    w.setWindowIcon(QIcon(_D_ICON_PATH));

    float resize = 1.0;

    QRect size1 = QGuiApplication::primaryScreen()->geometry();
    w.resize(size1.width() * resize, size1.height() * resize);

    w.show();
    return app.exec();
}

void create_cqtdeploy_file()
{

#ifndef _WIN32
    QString filename_desktop = cMake_binaryPath + QString("/") + cMake_projectName + QString(".desktop");
    QFile file_desktop(filename_desktop);

    if (file_desktop.exists())
        file_desktop.remove();

    //    #!/usr/bin/env xdg-open
    //    [Desktop Entry]
    //    Version=2022.3
    //    Exec=/home/tcousin//Bureau/0_qt_app/app_playVideo/playVideo.sh
    //    Icon=/home/tcousin//Bureau/0_qt_app/0_app_icon/tcnSystemIcon.png
    //    Name=playVideo
    //    GenericName=playVideo
    //    Comment=Develop QT Applications
    //    Encoding=UTF-8
    //    Terminal=false
    //    Type=Application
    //    Categories=Application;IDE;

    if (file_desktop.open(QIODevice::ReadWrite)) {

        QTextStream stream(&file_desktop);
        stream << "#!/usr/bin/env xdg-open\n";

        stream << "[Desktop Entry]\n";
        stream << "Version=2024.0\n";

        stream << "Exec=" << QDir::homePath() << "/Bureau/0_qt_app/app_" << cMake_projectName << "/" << cMake_projectName << ".sh\n";

        stream << "Icon=/home/tcousin/Bureau/0_qt_app/0_app_icon/tcnSystemIcon.png\n";

        stream << "Name=" << cMake_projectName << "\n";
        stream << "GenericName=" << cMake_projectName << "\n";

        stream << "Comment=Develop QT Applications\n"
               << "Encoding=UTF-8\n"
               << "Terminal=false\n"
               << "Type=Application\n"
               << "Categories=Application;IDE;\n";

        file_desktop.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_desktop.close();
    }

    // cqtdeployer -bin playVideo -qmake ~/Qt/5.15.2/gcc_64/bin/qmake

    // #! /bin/sh.

    QString filename_deploy = cMake_binaryPath + QString("/cqtDeploy.sh");
    QFile file_deploy(filename_deploy);

    if (file_deploy.exists())
        file_deploy.remove();

    if (file_deploy.open(QIODevice::ReadWrite)) {

        QTextStream stream(&file_deploy);
        stream << "#!/bin/sh"
               << "\n";

        stream << "\n";

        stream << "rm -rf " << QDir::homePath() << "/Bureau/0_qt_app/app_" << cMake_projectName << "\n";

        stream << "\n";

        stream << "cqtdeployer -bin "
               << cMake_projectName
               << " -qmake "
               << cMake_qtLibPath
               << "/bin/qmake -targetDir "
               << QDir::homePath()
               << "/Bureau/0_qt_app/app_"
               << cMake_projectName
               << "\n";

        stream << "\n";

        stream << "cp " << filename_desktop << " " << QDir::homePath() << "/Bureau/0_qt_app/\n";

        file_deploy.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_deploy.close();
    }

#else

    // #! /bin/sh.

    QString filename_deploy = cMake_binaryPath + QString("/cqtDeploy.bat");
    QFile file_deploy(filename_deploy);

    if (file_deploy.exists())
        file_deploy.remove();

    if (file_deploy.open(QIODevice::ReadWrite)) {

        // "C:/Program Files/CQtDeployer/1.6/CQtDeployer.exe" -bin manageModBus.exe -qmake C:/Qt/6.7.1/mingw_64/bin/qmake.exe

        QTextStream stream(&file_deploy);
        stream << "\n";

        stream << QChar('"') << "C:/Program Files/CQtDeployer/1.6/CQtDeployer.exe" << QChar('"')
               << " -bin "
               << cMake_projectName << ".exe"
               << " -qmake "
               << cMake_qtLibPath
               << "/bin/qmake.exe"
               << "\n";

        stream << "\n";
        stream << "pause\n";
        stream << "\n";

        //        file_deploy.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner | QFileDevice::ExeOwner);

        file_deploy.close();
    }

#endif
}
