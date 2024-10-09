#ifndef WDGCOMPARE_H
#define WDGCOMPARE_H

#include <QColor>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QScrollArea>
#include <QScrollBar>
#include <QString>
#include <QWidget>

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QGroupBox>

enum eStatFile {

    e_stat_file_none,
    e_stat_file_equal,
    e_stat_file_modify,
    e_stat_file_copy,
    e_stat_file_delete
};

struct sListFileCompare {

    QString _pathSrc;
    QString _pathDst;

    QString _path;

    qint64 _sizeSrc;
    qint64 _sizeDst;

    eStatFile e_stat;

    void init()
    {
        _pathSrc = "";
        _pathDst = "";

        _path = "";

        _sizeSrc = 0;
        _sizeDst = 0;

        e_stat = e_stat_file_none;
    }
};

class cWdgCompare : public QWidget {
    Q_OBJECT

public:
    cWdgCompare(QWidget* parent = nullptr);

private:
    QString pathFolder;

    QGroupBox* group_box;

    QLabel* ql_dirDetected;
    QLabel* ql_dirExcluded;

    QLabel* ql_fileDetected;
    QLabel* ql_fileExcluded;

    QList<sListFileCompare> l_listFile;

    void createListCompare();
    void trierListCompare();
};

class cWdgInfoFile : public QWidget {
    Q_OBJECT

public:
    cWdgInfoFile(QString _pathFile, QColor _background_color, QWidget* parent = nullptr);
    cWdgInfoFile(QString _pathFileSrc, QString _pathFileDst, QColor _background_color, QWidget* parent = nullptr);

public slots:

private:
};

#endif // WDGCOMPARE_H
