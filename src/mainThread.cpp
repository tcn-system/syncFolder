#include "mainThread.h"

//#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

//#include "Define.h"
#include "GlobalVar.h"
//#include "Tools.h"

cMainThread::cMainThread(QWidget* parent)
{
    m_timer = new QTimer;
    e_typeAction = e_action_null;

    m_fileCopyier = new cThreadProcess;
    m_fileCopyier->setMinimumWidth(600);
    m_fileCopyier->setWindowTitle(cMake_projectName + QString(" page::fileCopyier ") + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");

    connect(m_fileCopyier, &cThreadProcess::p_emitFinished, this, &cMainThread::p_receptFinished);
}

cMainThread::~cMainThread()
{
    if (m_timer->isActive())
        m_timer->stop();

    if (m_timer != nullptr)
        delete m_timer;
}

void cMainThread::connect_timer()
{
    switch (e_typeAction) {
    case e_action_copy:
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Copy()));
        break;
    case e_action_modify:
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Modify()));
        break;
    case e_action_delete:
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Delete()));
        break;
    case e_action_dir_delete:
        connect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Dir_Delete()));
        break;
    default:
        break;
    }
}
void cMainThread::disconnect_timer()
{
    switch (e_typeAction) {
    case e_action_copy:
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Copy()));
        break;
    case e_action_modify:
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Modify()));
        break;
    case e_action_delete:
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Delete()));
        break;
    case e_action_dir_delete:
        disconnect(m_timer, SIGNAL(timeout()), this, SLOT(updateTimer_Dir_Delete()));
        break;
    default:
        break;
    }
}

void cMainThread::initMainThread(eTypeAction _typeAction)
{
    e_typeAction = _typeAction;

    statMachine = 0;
    c_globalVar.idxFile = 0;
    c_globalVar.idxFile_percent = 0;
}

void cMainThread::startMainThread()
{
    if (not m_timer->isActive()) {

        connect_timer();
        m_timer->start(10);
    }
    if (e_typeAction != e_action_dir_delete)
        m_fileCopyier->show();
}
void cMainThread::stopMainThread()
{
    if (m_timer->isActive()) {
        m_timer->stop();
    }
    disconnect_timer();
    m_fileCopyier->hide();
}
bool cMainThread::isRunning()
{
    return m_timer->isActive();
}

void cMainThread::updateTimer_Copy()
{
    disconnect_timer();

    switch (statMachine) {
    case 0:
        if (c_globalVar.idxFile < c_globalVar.s_compare.listFileCopy.size()) {

            c_globalVar.idxFile_percent = (c_globalVar.idxFile * 100) / c_globalVar.s_compare.listFileCopy.size();

            QString dstFileName = c_globalVar.s_compare.listFileCopy.at(c_globalVar.idxFile).path_full;
            dstFileName.replace(c_globalVar.s_compare.folder_src_dir, "");

            QString dstFilePath = c_globalVar.s_compare.listFileCopy.at(c_globalVar.idxFile).path_full;
            dstFilePath.replace(c_globalVar.s_compare.folder_src_dir, c_globalVar.s_compare.folder_dst_dir);

            QFile _file(c_globalVar.s_compare.listFileCopy.at(c_globalVar.idxFile).path_full);
            qint64 _freeSize = c_globalVar.verif_storage_space_free(dstFilePath , _file.size() , _error_free_space);

            qDebug() << "_freeSize" << _freeSize;

            if(_freeSize > 0)
            {
                c_globalVar.s_folderDst.folder_free_space_size = _freeSize;

                m_fileCopyier->p_copy(dstFileName, c_globalVar.s_compare.listFileCopy.at(c_globalVar.idxFile).path_full, dstFilePath);
                m_fileCopyier->setWindowTitle(cMake_projectName
                                              + QString(" page::fileCopyier::copy ( ") + QString::number(c_globalVar.idxFile) + " / " + QString::number(c_globalVar.s_compare.listFileCopy.size()) + QString(" ) ")
                                              + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
                m_fileCopyier->adjustSize();

                statMachine = 1;

            } else {

                stopMainThread();
                Q_EMIT p_copyFinishedSignal();
                return;
            }

        } else {

            stopMainThread();
            Q_EMIT p_copyFinishedSignal();
            return;
        }
        break;
    case 1:
        // qDebug() << "in process";
        break;
    }
    connect_timer();
}

void cMainThread::updateTimer_Modify()
{
    disconnect_timer();

    switch (statMachine) {
    case 0:
        if (c_globalVar.idxFile < c_globalVar.s_compare.listFileModify.size()) {

            c_globalVar.idxFile_percent = (c_globalVar.idxFile * 100) / c_globalVar.s_compare.listFileModify.size();

            QString dstFileName = c_globalVar.s_compare.listFileModify.at(c_globalVar.idxFile).path_full;
            dstFileName.replace(c_globalVar.s_compare.folder_src_dir, "");

            QString dstFilePath = c_globalVar.s_compare.listFileModify.at(c_globalVar.idxFile).path_full;
            dstFilePath.replace(c_globalVar.s_compare.folder_src_dir, c_globalVar.s_compare.folder_dst_dir);

            QFile _file(c_globalVar.s_compare.listFileModify.at(c_globalVar.idxFile).path_full);
            qint64 _freeSize = c_globalVar.verif_storage_space_free(dstFilePath , _file.size() , _error_free_space);

            qDebug() << "_freeSize" << _freeSize;

            if(_freeSize > 0)
            {
                c_globalVar.s_folderDst.folder_free_space_size = _freeSize;

                m_fileCopyier->p_copy(dstFileName, c_globalVar.s_compare.listFileModify.at(c_globalVar.idxFile).path_full, dstFilePath);
                m_fileCopyier->setWindowTitle(cMake_projectName
                                              + QString(" page::fileCopyier::modify ( ") + QString::number(c_globalVar.idxFile) + " / " + QString::number(c_globalVar.s_compare.listFileModify.size()) + QString(" ) ")
                                              + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
                m_fileCopyier->adjustSize();

                statMachine = 1;

            } else {

                stopMainThread();
                Q_EMIT p_copyFinishedSignal();
                return;
            }

        } else {

            stopMainThread();
            Q_EMIT p_copyFinishedSignal();
            return;
        }
        break;
    case 1:
        // qDebug() << "in process";
        break;
    }
    connect_timer();
}

void cMainThread::updateTimer_Delete()
{
    disconnect_timer();

    switch (statMachine) {
    case 0:
        if (c_globalVar.idxFile < c_globalVar.s_compare.listFileDelete.size()) {

            c_globalVar.idxFile_percent = (c_globalVar.idxFile * 100) / c_globalVar.s_compare.listFileDelete.size();

            QString dstFileName = c_globalVar.s_compare.listFileDelete.at(c_globalVar.idxFile).path_full;
            dstFileName.replace(c_globalVar.s_compare.folder_src_dir, "");

            QString dstFilePath = c_globalVar.s_compare.listFileDelete.at(c_globalVar.idxFile).path_full;
            dstFilePath.replace(c_globalVar.s_compare.folder_src_dir, c_globalVar.s_compare.folder_dst_dir);

            m_fileCopyier->p_delete(dstFileName, c_globalVar.s_compare.listFileDelete.at(c_globalVar.idxFile).path_full, dstFilePath);
            m_fileCopyier->setWindowTitle(cMake_projectName
                                          + QString(" page::fileCopyier::delete ( ") + QString::number(c_globalVar.idxFile) + " / " + QString::number(c_globalVar.s_compare.listFileDelete.size()) + QString(" ) ")
                                          + cMake_projectVersion + " qt" + cMake_qtVersion + " - tcn-system.com");
            m_fileCopyier->adjustSize();

            statMachine = 1;
        } else {

            stopMainThread();
            Q_EMIT p_copyFinishedSignal();
            return;
        }
        break;
    case 1:
        // qDebug() << "in process";
        break;
    }
    connect_timer();
}

void cMainThread::updateTimer_Dir_Delete()
{
    disconnect_timer();

    switch (statMachine) {
    case 0:
        if (c_globalVar.idxFile < c_globalVar.s_compare.listDirDelete.size()) {

            c_globalVar.idxFile_percent = (c_globalVar.idxFile * 100) / c_globalVar.s_compare.listDirDelete.size();

            Q_EMIT p_dir_delete_upgate_Signal();

            statMachine = 1;
        } else {

            for (int i = 0; i < c_globalVar.s_compare.listDirDelete.size(); i++) {

                QDir dir(c_globalVar.s_compare.listDirDelete.at(i).path_full);

                if (dir.exists(c_globalVar.s_compare.listDirDelete.at(i).path_full)) {

                    c_globalVar.idxFile = 0;
                    connect_timer();
                    return;
                }
            }

            //            qDebug() << " all dir not exist";

            stopMainThread();

            Q_EMIT p_copyFinishedSignal();
            return;
        }
        break;
    case 1:

        QString dirName = c_globalVar.s_compare.listDirDelete.at(c_globalVar.idxFile).path_full;

        //        qDebug() << " verif dir" << dirName;

        QDir dir(dirName);

        if (dir.exists(dirName)) {

            QFileInfoList infoList = dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden | QDir::AllDirs | QDir::Files, QDir::DirsFirst);

            if (infoList.size() == 0) {
                dir.rmdir(dirName);
                //                qDebug() << " dir " << dirName << " removed";
            }
        }

        c_globalVar.idxFile++;

        statMachine = 0;

        break;
    }
    connect_timer();
}

void cMainThread::p_receptFinished(bool b_success)
{
    if (b_success) {

        c_globalVar.idxFile++;

        switch (e_typeAction) {
        case e_action_delete:
            Q_EMIT p_delete_upgate_Signal();
            break;
        case e_action_modify:
            Q_EMIT p_modify_upgate_Signal();
            break;
        case e_action_copy:
            Q_EMIT p_copy_upgate_Signal();
            break;
        }

        Q_EMIT p_copyInProcessSignal();
    }
    statMachine = 0;
}
