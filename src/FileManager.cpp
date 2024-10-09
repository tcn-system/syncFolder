#include "FileManager.h"

#include <QSettings>

#include "GlobalVar.h"

cFileManager::cFileManager(const QDir& root)
    : storageRoot(root)
{
}

const QDir& cFileManager::root() const
{
    return storageRoot;
}

QDir cFileManager::parameterDir() const
{
    return storageRoot.path() + "/parameter";
}

bool cFileManager::verifyAllDirCreate() const
{
    QDir ldir;

    ldir = parameterDir();
    if (!ldir.exists()) {
        ldir.mkpath(".");
    }
    return false;
}

void cFileManager::readParametres()
{
    _listProfile.clear();

    QSettings settings(parameterDir().path() + "/paramere.ini", QSettings::IniFormat);

    int nbre = settings.value("GENERALE/NBRE").toInt();

    for (int i = 0; i < nbre; i++)
        _listProfile.push_back(settings.value("PROFILE/PRO_" + QString::number(i)).toStringList());
}
void cFileManager::writeParametres()
{
    QSettings settings(parameterDir().path() + "/paramere.ini", QSettings::IniFormat);

    settings.beginGroup("GENERALE");
    settings.setValue("NBRE", _listProfile.size());
    settings.endGroup();

    settings.beginGroup("PROFILE");
    for (int i = 0; i < _listProfile.size(); i++)
        settings.setValue("PRO_" + QString::number(i), _listProfile[i]);
    settings.endGroup();
}
