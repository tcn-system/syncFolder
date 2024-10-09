#ifndef THREAD_PROCESS_H_
#define THREAD_PROCESS_H_

#include <QtCore/qdir.h>
#include <QtCore/qfile.h>
#include <QtCore/qfileinfo.h>
#include <QtCore/qobject.h>
#include <QtCore/qstring.h>
#include <QtCore/qthread.h>
#include <QtCore/qvector.h>

#include "enum.h"

class cProcess : public QObject {
    Q_OBJECT
    //    Q_PROPERTY(qint64 chunksize READ chunkSize WRITE setChunkSize)
    //    Q_PROPERTY(QString sourcePaths READ sourcePaths WRITE setSourcePaths)
    //    Q_PROPERTY(QString destinationPaths READ destinationPaths WRITE setDestinationPaths)

public:
    static const int DEFAULT_CHUNK_SIZE = 1024 * 1024 * 1;

    cProcess(QThread* qt_th, eTypeAction _typeAction);
    ~cProcess();

    qint64 chunkSize() const
    {
        return qi_chunk;
    }
    void setChunkSize(qint64 ch)
    {
        qi_chunk = ch;
    }

    QString sourcePaths() const
    {
        return qs_src;
    }
    void setSourcePaths(const QString& _src)
    {
        qs_src = _src;
    }

    QString destinationPaths() const
    {
        return qs_dst;
    }
    void setDestinationPaths(const QString& _dst)
    {
        qs_dst = _dst;
    }

protected slots:
    void p_processCopy();
    void p_processDelete();

private:
    QString qs_src, qs_dst;
    qint64 qi_chunk;

signals:
    void p_emitInProgress(qint64 i_idx, qint64 i_total);
    void p_emitFinished(bool b_success);
};

#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

class cThreadProcess : public QWidget {
    Q_OBJECT

public:
    cThreadProcess(QWidget* qw_parent = nullptr);
    ~cThreadProcess();

    bool p_copy(QString qs_name, QString qs_srcPath, QString qs_destPath);
    bool p_delete(QString qs_name, QString qs_srcPath, QString qs_destPath);

public slots:
    void p_receptInProcessSlot(qint64 i_idx, qint64 i_total);
    void p_receptFinishedSlot(bool b_success);

signals:
    void p_emitFinished(bool b_success);

private:
    QThread* qt_thread = nullptr;
    cProcess* m_process = nullptr;

    QLabel* ql_editProgressBar;
    QProgressBar* qpb_progressBar;
};

#endif // FILECOPYER_H
