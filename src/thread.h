#ifndef THREAD_H_
#define THREAD_H_

#include <QDebug>
#include <QThread>
#include <QWidget>

#include "structs.h"

class cThread : public QThread {
    Q_OBJECT

public:
    cThread(QWidget* parent = nullptr);
    ~cThread();

    void p_begin();
    void p_stop();

    void setPath(QString _path, bool _exept = true)
    {
        path = _path;
        exept = _exept;
    }
    void setFolder(sFolder* _folder) { folder = _folder; }

private slots:
    void slot_cthread_start();
    void slot_cthread_finished();

signals:
    void signal_cthread_start();
    void signal_cthread_finished();

private:
    void run();

    bool b_running;

    QString path = "";
    bool exept = true;
    sFolder* folder;
};

#endif // THREAD_H_
