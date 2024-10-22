#ifndef MAINTHREAD_H_
#define MAINTHREAD_H_

#include <QtCore/QBasicTimer>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

#include <QDir>
#include <QFileDialog>
#include <QRandomGenerator>
#include <QTextStream>

#include <QProgressBar>
#include <QTimer>

#include "threadProcess.h"

class cMainThread : public QMainWindow {
    Q_OBJECT

public:
    cMainThread(QWidget* parent = nullptr);
    ~cMainThread();

    void initMainThread(eTypeAction _typeAction);
    void startMainThread();
    void stopMainThread();

    bool isRunning();

protected:
public slots:
    void updateTimer_Copy();
    void updateTimer_Modify();
    void updateTimer_Delete();

    void updateTimer_Dir_Delete();

    void p_receptFinished(bool b_success);

signals:
    void p_copyInProcessSignal();

    void p_delete_upgate_Signal();
    void p_modify_upgate_Signal();
    void p_copy_upgate_Signal();

    void p_dir_delete_upgate_Signal();

    void p_copyFinishedSignal();

private:
    QTimer* m_timer = nullptr;
    eTypeAction e_typeAction;
    int statMachine;

    cThreadProcess* m_fileCopyier = nullptr;

    void connect_timer();
    void disconnect_timer();

    QString _error_free_space;
};

#endif // MAINTHREAD_H_
