#include "thread.h"

#include "GlobalVar.h"
#include "syncFolder.h"

cThread::cThread(QWidget* parent)
    : QThread(parent)
{
    b_running = false;

    connect(this, &cThread::started, this, &cThread::slot_cthread_start);
    connect(this, &cThread::finished, this, &cThread::slot_cthread_finished);
}
cThread::~cThread()
{
    qDebug() << "~cThread";
    p_stop();
}

void cThread::p_begin()
{
    b_running = true;
    start();
}

void cThread::run()
{
    qDebug() << "cThread::run";
    //    while (b_running) {
    //    }
    cSyncFolder* syncFolder = new cSyncFolder;
    folder->init();
    *folder = syncFolder->readFolder(path, exept);

    quit();
    //    exec();
}

void cThread::p_stop()
{
    qDebug() << "cThread::p_stop";
    if (isRunning()) {
        b_running = false;
        exit();
    }

    wait();

    quit();
    deleteLater();
}

void cThread::slot_cthread_start()
{
    Q_EMIT signal_cthread_start();
}
void cThread::slot_cthread_finished()
{
    qDebug() << "cThread::slot_cthread_finished";

    Q_EMIT signal_cthread_finished();

    //    deleteLater();
}
