#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QtCore/QDate>
#include <QtCore/QDir>

class cFileManager {
public:
    cFileManager(const QDir& root);

    const QDir& root() const;

    QDir parameterDir() const;

    bool verifyAllDirCreate() const;

    void readParametres();
    void writeParametres();

private:
    QDir storageRoot;

    QList<QStringList> _listProfile;
};

#endif // FILE_MANAGER_H
