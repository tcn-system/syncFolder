#include "mainwindow.h"


#include <QMessageBox>

cMainWindow::cMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QVBoxLayout* main_layout = new QVBoxLayout;
    {
        QHBoxLayout* group_layout = new QHBoxLayout;
        {
            QGroupBox* groupSrc = new QGroupBox;
            {
                groupSrc->setTitle("Src");

                QVBoxLayout* src_layout = new QVBoxLayout;
                {
                    QHBoxLayout* pathSrc_layout = new QHBoxLayout;
                    {
                        qle_pathSrc = new QLineEdit;
                        qle_pathSrc->setReadOnly(true);
                        qle_pathSrc->setText("");
                        pathSrc_layout->addWidget(qle_pathSrc);

                        qpb_selectPathSrc = new QPushButton;
                        qpb_selectPathSrc->setText(" Select Src ");
                        connect(qpb_selectPathSrc, SIGNAL(clicked()), this, SLOT(p_selectPathSrcSlot()));
                        pathSrc_layout->addWidget(qpb_selectPathSrc);
                    }
                    src_layout->addLayout(pathSrc_layout);

                    QHBoxLayout* checkBox_src_layout = new QHBoxLayout;
                    {
                        qcb_src_exeptFolders = new QCheckBox("exept folders");
                        qcb_src_exeptFolders->setChecked(c_globalVar.b_src_exept_folders);
                        connect(qcb_src_exeptFolders, SIGNAL(clicked(bool)), this , SLOT(p_src_check_exept_folders_Slot(bool)) );

                        qsb_nbre_src_folders = new QSpinBox;
                        qsb_nbre_src_folders->setRange(0 , 9999999);
                        qsb_nbre_src_folders->setReadOnly(true);

                        qcb_src_exeptFiles = new QCheckBox("exept files");
                        qcb_src_exeptFiles->setChecked(c_globalVar.b_src_exept_files);
                        connect(qcb_src_exeptFiles, SIGNAL(clicked(bool)), this , SLOT(p_src_check_exept_files_Slot(bool)) );

                        qsb_nbre_src_files = new QSpinBox;
                        qsb_nbre_src_files->setRange(0 , 9999999);
                        qsb_nbre_src_files->setReadOnly(true);

                        checkBox_src_layout->addWidget(qcb_src_exeptFolders);
                        checkBox_src_layout->addWidget(qsb_nbre_src_folders);
                        checkBox_src_layout->addWidget(qcb_src_exeptFiles);
                        checkBox_src_layout->addWidget(qsb_nbre_src_files);
                    }
                    src_layout->addLayout(checkBox_src_layout);

                    listSrc = new QListWidget;
                    src_layout->addWidget(listSrc);
                }
                groupSrc->setLayout(src_layout);
            }
            group_layout->addWidget(groupSrc);

            QGroupBox* groupCompare = new QGroupBox;
            {
                groupCompare->setTitle("Compare");

                QVBoxLayout* cmp_layout = new QVBoxLayout;
                {
                    qpb_compare = new QPushButton;
                    qpb_compare->setText(" Compare ");
                    connect(qpb_compare, SIGNAL(clicked()), this, SLOT(p_compareSlot()));
                    cmp_layout->addWidget(qpb_compare);
                    qpb_compare->setEnabled(false);

                    listComp_Delete = new QListWidget;
                    cmp_layout->addWidget(listComp_Delete);

                    qpb_cmpDelete = new QPushButton;
                    qpb_cmpDelete->setText(" Delete ");
                    connect(qpb_cmpDelete, SIGNAL(clicked()), this, SLOT(p_cmp_Delete_Slot()));
                    cmp_layout->addWidget(qpb_cmpDelete);
                    qpb_cmpDelete->setEnabled(false);

                    listComp_Modify = new QListWidget;
                    cmp_layout->addWidget(listComp_Modify);

                    qpb_cmpModify = new QPushButton;
                    qpb_cmpModify->setText(" Modify ");
                    connect(qpb_cmpModify, SIGNAL(clicked()), this, SLOT(p_cmp_Modify_Slot()));
                    cmp_layout->addWidget(qpb_cmpModify);
                    qpb_cmpModify->setEnabled(false);

                    listComp_Copy = new QListWidget;
                    cmp_layout->addWidget(listComp_Copy);

                    qpb_cmpCopy = new QPushButton;
                    qpb_cmpCopy->setText(" Copy ");
                    connect(qpb_cmpCopy, SIGNAL(clicked()), this, SLOT(p_cmp_Copy_Slot()));
                    cmp_layout->addWidget(qpb_cmpCopy);
                    qpb_cmpCopy->setEnabled(false);

                    listComp_Dir_Delete = new QListWidget;
                    cmp_layout->addWidget(listComp_Dir_Delete);

                    qpb_clearDir = new QPushButton;
                    qpb_clearDir->setText(" clean DIR ");
                    connect(qpb_clearDir, SIGNAL(clicked()), this, SLOT(p_cmp_ClearDir_Slot()));
                    cmp_layout->addWidget(qpb_clearDir);
                    qpb_clearDir->setEnabled(false);
                }
                groupCompare->setLayout(cmp_layout);
            }
            group_layout->addWidget(groupCompare);

            QGroupBox* groupDst = new QGroupBox;
            {
                groupDst->setTitle("Dst");

                QVBoxLayout* dst_layout = new QVBoxLayout;
                {
                    QHBoxLayout* pathDst_layout = new QHBoxLayout;
                    {
                        qle_pathDst = new QLineEdit;
                        qle_pathDst->setReadOnly(true);
                        qle_pathDst->setText("");
                        pathDst_layout->addWidget(qle_pathDst);

                        qpb_selectPathDst = new QPushButton;
                        qpb_selectPathDst->setText(" Select Dst ");
                        connect(qpb_selectPathDst, SIGNAL(clicked()), this, SLOT(p_selectPathDstSlot()));
                        pathDst_layout->addWidget(qpb_selectPathDst);
                    }
                    dst_layout->addLayout(pathDst_layout);

                    QHBoxLayout* checkBox_dst_layout = new QHBoxLayout;
                    {
                        qcb_dst_exeptFolders = new QCheckBox("exept folders");
                        qcb_dst_exeptFolders->setChecked(c_globalVar.b_dst_exept_folders);
                        connect(qcb_dst_exeptFolders, SIGNAL(clicked(bool)), this , SLOT(p_dst_check_exept_folders_Slot(bool)) );

                        qsb_nbre_dst_folders = new QSpinBox;
                        qsb_nbre_dst_folders->setRange(0 , 9999999);
                        qsb_nbre_dst_folders->setReadOnly(true);

                        qcb_dst_exeptFiles = new QCheckBox("exept files");
                        qcb_dst_exeptFiles->setChecked(c_globalVar.b_dst_exept_files);
                        connect(qcb_dst_exeptFiles, SIGNAL(clicked(bool)), this , SLOT(p_dst_check_exept_files_Slot(bool)) );

                        qsb_nbre_dst_files = new QSpinBox;
                        qsb_nbre_dst_files->setRange(0 , 9999999);
                        qsb_nbre_dst_files->setReadOnly(true);

                        checkBox_dst_layout->addWidget(qcb_dst_exeptFolders);
                        checkBox_dst_layout->addWidget(qsb_nbre_dst_folders);
                        checkBox_dst_layout->addWidget(qcb_dst_exeptFiles);
                        checkBox_dst_layout->addWidget(qsb_nbre_dst_files);
                    }
                    dst_layout->addLayout(checkBox_dst_layout);

                    listDst = new QListWidget;
                    dst_layout->addWidget(listDst);
                }
                groupDst->setLayout(dst_layout);
            }
            group_layout->addWidget(groupDst);
        }
        main_layout->addLayout(group_layout);

        //        QHBoxLayout* profile_layout = new QHBoxLayout;
        //        {
        //            QLabel* ql_loadProfile = new QLabel;
        //            ql_loadProfile->setText("Select Profile:");
        //            profile_layout->addWidget(ql_loadProfile);

        //            qcb_loadProfile = new QComboBox;
        //            qcb_loadProfile->addItem("");
        //            for (int i = 0; i < _listProfile.size(); i++) {
        //                qcb_loadProfile->addItem(_listProfile[i][0]);
        //            }
        //            connect(qcb_loadProfile, SIGNAL(currentIndexChanged(int)), this, SLOT(p_loadProfileSlot(int)));
        //            profile_layout->addWidget(qcb_loadProfile);
        //        }
        //        main_layout->addLayout(profile_layout);

        qpb_progressBar = new QProgressBar;
        //        qpb_progressBar->setMaximum(100);
        //        qpb_progressBar->setMinimum(0);
        qpb_progressBar->setValue(0);
        qpb_progressBar->setTextVisible(true);
        qpb_progressBar->setFormat("0 %");
        qpb_progressBar->setAlignment(Qt::AlignCenter);
        qpb_progressBar->setVisible(false);
        main_layout->addWidget(qpb_progressBar);
    }

    QWidget* main_widget = new QWidget();
    main_widget->setLayout(main_layout);
    setCentralWidget(main_widget);

    refresh_auto = false;

    syncFolder = new cSyncFolder;
    mainThread = new cMainThread();
    connect(mainThread, &cMainThread::p_copyInProcessSignal, this, &cMainWindow::p_copyInProcessSlot);
    connect(mainThread, &cMainThread::p_copyFinishedSignal, this, &cMainWindow::p_copyFinishedSlot);

    connect(mainThread, &cMainThread::p_delete_upgate_Signal, this, &cMainWindow::p_update_Delete_Slot);
    connect(mainThread, &cMainThread::p_modify_upgate_Signal, this, &cMainWindow::p_update_Modify_Slot);
    connect(mainThread, &cMainThread::p_copy_upgate_Signal, this, &cMainWindow::p_update_Copy_Slot);

    connect(mainThread, &cMainThread::p_dir_delete_upgate_Signal, this, &cMainWindow::p_update_Dir_Delete_Slot);
}

cMainWindow::~cMainWindow()
{
}

void cMainWindow::closeEvent(QCloseEvent* ce)
{
    if (waitSrcRead != nullptr) {
        waitSrcRead->hide();
        delete waitSrcRead;
        waitSrcRead = nullptr;
    }
    if (waitDstRead != nullptr) {
        waitDstRead->hide();
        delete waitDstRead;
        waitDstRead = nullptr;
    }
    if (waitCompare != nullptr) {
        waitCompare->hide();
        delete waitCompare;
        waitCompare = nullptr;
    }
}

void cMainWindow::p_loadProfileSlot(int idx)
{
    qle_pathSrc->setText("");
    qle_pathDst->setText("");

    listSrc->clear();
    listDst->clear();

    //    if (idx > 0) {

    //        QString _srcPath = _listProfile[idx - 1][1];
    //        qle_pathSrc->setText(_srcPath);

    //        loadSrcList(_srcPath);

    //        QString _dstPath = _listProfile[idx - 1][2];
    //        qle_pathDst->setText(_dstPath);

    //        loadDstList(_dstPath);
    //    }

    qpb_progressBar->setVisible(false);
}

void cMainWindow::p_selectPathSrcSlot()
{
    QString _srcPath = QFileDialog::getExistingDirectory(
        this,
        tr("Select Src Directory"),
        QDir::currentPath());

    qle_pathSrc->setText(_srcPath);

    loadSrcList(_srcPath);
}
void cMainWindow::loadSrcList(QString _srcPath)
{
    if (_srcPath.size() > 0) {

        QString _error;
        qint64 _freeSize = c_globalVar.get_storage_space_free(_srcPath,_error);

        c_globalVar.s_folderSrc.folder_free_space_size = _freeSize;

        if(_freeSize > (1024 * 1024 * 1024)) // 1 Giga octets
        {
            setEnable_Src(false);

            waitSrcRead = new cWaitWindows(listSrc);
            waitSrcRead->show();

            cReadFolder* readFolder = new cReadFolder;
            connect(readFolder, &cReadFolder::finished, this, &cMainWindow::p_readSrcFolderFinishSlot);
            readFolder->setPath(_srcPath , c_globalVar.b_src_exept_folders , c_globalVar.b_src_exept_files);
            readFolder->setFolder(&c_globalVar.s_folderSrc);
            readFolder->start();

            //        cThread* _thread = new cThread(this);
            //        connect(_thread, &cThread::signal_cthread_finished, this, &cMainWindow::p_readSrcFolderFinishSlot);
            //        _thread->setPath(_srcPath);
            //        _thread->setFolder(&c_globalVar.s_folderSrc);
            //        _thread->p_begin();
        }
        else
        {
            QMessageBox( QMessageBox::Information, "Error free space size", _error, QMessageBox::Ok).exec();
        }
    }
}
void cMainWindow::p_readSrcFolderFinishSlot()
{
    QList<cThread*> allthread = this->findChildren<cThread*>();
    foreach (cThread* _tread, allthread) {
        _tread->p_stop();
    }

    listSrc->clear();

    int cptItem = 0;
    for (int i = 0; i < c_globalVar.s_folderSrc.listFile.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_folderSrc.listFile.at(i).path);

        if (not(cptItem % 2))
            item->setBackground(QColor(200, 200, 200));
        else
            item->setBackground(QColor(240, 240, 240));
        listSrc->addItem(item);
        cptItem++;
    }

    qsb_nbre_src_folders->setValue(c_globalVar.s_folderSrc.listDir.size());
    qsb_nbre_src_files->setValue(c_globalVar.s_folderSrc.listFile.size());

    setEnable_Src(true);

    if (c_globalVar.s_folderSrc.folder_dir.size() > 0 and c_globalVar.s_folderDst.folder_dir.size() > 0)
        qpb_compare->setEnabled(true);
    else {
        listComp_Copy->clear();
        listComp_Modify->clear();
        listComp_Delete->clear();

        listComp_Dir_Delete->clear();

        c_globalVar.s_compare.init();

        qpb_compare->setEnabled(false);
    }

    if (waitSrcRead != nullptr) {
        waitSrcRead->hide();
        delete waitSrcRead;
        waitSrcRead = nullptr;
    }
}
void cMainWindow::setEnable_Src(bool _stat)
{
    qpb_selectPathSrc->setEnabled(_stat);
    qle_pathSrc->setEnabled(_stat);
    listSrc->setEnabled(_stat);
    qcb_src_exeptFolders->setEnabled(_stat);
    qsb_nbre_src_folders->setEnabled(_stat);
    qcb_src_exeptFiles->setEnabled(_stat);
    qsb_nbre_src_files->setEnabled(_stat);
}


void cMainWindow::p_selectPathDstSlot()
{
    QString _dstPath = QFileDialog::getExistingDirectory(
        this,
        tr("Select Dst Directory"),
        QDir::currentPath());

    qle_pathDst->setText(_dstPath);

    loadDstList(_dstPath);
}
void cMainWindow::loadDstList(QString _dstPath)
{
    if (_dstPath.size() > 0) {

        QString _error;
        qint64 _freeSize = c_globalVar.get_storage_space_free(_dstPath,_error);

        c_globalVar.s_folderDst.folder_free_space_size = _freeSize;

        if(_freeSize > (1024 * 1024 * 1024)) // 1 Giga octets
        {
            QString _error;
            c_globalVar.get_storage_space_free(_dstPath,_error);

            setEnable_Dst(false);

            waitDstRead = new cWaitWindows(listDst);
            waitDstRead->show();

            cReadFolder* readFolder = new cReadFolder;
            connect(readFolder, &cReadFolder::finished, this, &cMainWindow::p_readDstFolderFinishSlot);
            readFolder->setPath(_dstPath, c_globalVar.b_dst_exept_folders , c_globalVar.b_dst_exept_files);
            readFolder->setFolder(&c_globalVar.s_folderDst);
            readFolder->start();
        }
        else
        {
            QMessageBox( QMessageBox::Information, "Error free space size", _error, QMessageBox::Ok).exec();
        }
    }
}
void cMainWindow::p_readDstFolderFinishSlot()
{
    listDst->clear();

    int cptItem = 0;
    for (int i = 0; i < c_globalVar.s_folderDst.listFile.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_folderDst.listFile.at(i).path);

        if (not(cptItem % 2))
            item->setBackground(QColor(200, 200, 200));
        else
            item->setBackground(QColor(240, 240, 240));
        listDst->addItem(item);
        cptItem++;
    }

    qsb_nbre_dst_folders->setValue(c_globalVar.s_folderDst.listDir.size());
    qsb_nbre_dst_files->setValue(c_globalVar.s_folderDst.listFile.size());

    setEnable_Dst(true);

    if (c_globalVar.s_folderSrc.folder_dir.size() > 0 and c_globalVar.s_folderDst.folder_dir.size() > 0)
        qpb_compare->setEnabled(true);
    else {
        listComp_Copy->clear();
        listComp_Modify->clear();
        listComp_Delete->clear();

        listComp_Dir_Delete->clear();

        c_globalVar.s_compare.init();

        qpb_compare->setEnabled(false);
    }

    if (waitDstRead != nullptr) {
        waitDstRead->hide();
        delete waitDstRead;
        waitDstRead = nullptr;
    }

    if (refresh_auto) {

        p_compareSlot();
    }
}
void cMainWindow::setEnable_Dst(bool _stat)
{
    qpb_selectPathDst->setEnabled(_stat);
    qle_pathDst->setEnabled(_stat);
    listDst->setEnabled(_stat);
    qcb_dst_exeptFolders->setEnabled(_stat);
    qsb_nbre_dst_folders->setEnabled(_stat);
    qcb_dst_exeptFiles->setEnabled(_stat);
    qsb_nbre_dst_files->setEnabled(_stat);
}

void cMainWindow::p_copyInProcessSlot()
{
    qpb_progressBar->setValue(c_globalVar.idxFile);
    qpb_progressBar->setFormat(QString::number(c_globalVar.idxFile_percent) + " %");
}

void cMainWindow::p_copyFinishedSlot()
{
    QString _dstPath = c_globalVar.s_folderDst.folder_dir;

    loadDstList(_dstPath);

    qpb_progressBar->setVisible(false);

    if (not refresh_auto)
        this->setEnabled(true);
}

void cMainWindow::p_compareSlot()
{
    listComp_Copy->clear();
    listComp_Modify->clear();
    listComp_Delete->clear();

    listComp_Dir_Delete->clear();

    waitCompare = new cWaitWindows(listComp_Modify);
    waitCompare->show();

    cCompareFolder* cmpFolder = new cCompareFolder;
    connect(cmpFolder, &cCompareFolder::finished, this, &cMainWindow::p_compareFinishSlot);
    cmpFolder->start();
}
void cMainWindow::p_compareFinishSlot()
{
    for (int i = 0; i < c_globalVar.s_compare.listFileCopy.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_compare.listFileCopy.at(i).path + " (" + QString::number(c_globalVar.s_compare.listFileCopy.at(i).size) + ")");

        item->setBackground(QColor(240, 240, 240));
        listComp_Copy->addItem(item);
    }
    for (int i = 0; i < c_globalVar.s_compare.listFileModify.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_compare.listFileModify.at(i).path + " (" + QString::number(c_globalVar.s_compare.listFileModify.at(i).size) + ")");

        item->setBackground(QColor(240, 240, 240));
        listComp_Modify->addItem(item);
    }
    for (int i = 0; i < c_globalVar.s_compare.listFileDelete.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_compare.listFileDelete.at(i).path + " (" + QString::number(c_globalVar.s_compare.listFileDelete.at(i).size) + ")");

        item->setBackground(QColor(240, 240, 240));
        listComp_Delete->addItem(item);
    }
    for (int i = 0; i < c_globalVar.s_compare.listDirDelete.size(); i++) {

        QListWidgetItem* item = new QListWidgetItem(c_globalVar.s_compare.listDirDelete.at(i).path);

        item->setBackground(QColor(240, 240, 240));
        listComp_Dir_Delete->addItem(item);
    }

    if (c_globalVar.s_compare.listFileCopy.size() > 0)
        qpb_cmpCopy->setEnabled(true);
    else
        qpb_cmpCopy->setEnabled(false);

    if (c_globalVar.s_compare.listFileModify.size() > 0)
        qpb_cmpModify->setEnabled(true);
    else
        qpb_cmpModify->setEnabled(false);

    if (c_globalVar.s_compare.listFileDelete.size() > 0)
        qpb_cmpDelete->setEnabled(true);
    else
        qpb_cmpDelete->setEnabled(false);

    qpb_compare->setText(" Compare ( "
        + QString::number(c_globalVar.s_folderSrc.listFile.size())
        + "/"
        + QString::number(c_globalVar.s_folderDst.listFile.size())
        + " - equal: "
        + QString::number(c_globalVar.s_compare.listFileEqual.size())
        + " ) ");

    qpb_cmpDelete->setText(" Delete ( " + QString::number(c_globalVar.s_compare.listFileDelete.size()) + " ) ");
    qpb_cmpModify->setText(" Modify ( " + QString::number(c_globalVar.s_compare.listFileModify.size()) + " ) ");
    qpb_cmpCopy->setText(" Copy ( " + QString::number(c_globalVar.s_compare.listFileCopy.size()) + " ) ");

    if (c_globalVar.s_compare.listDirDelete.size() > 0)
        qpb_clearDir->setEnabled(true);
    else
        qpb_clearDir->setEnabled(false);

    qpb_clearDir->setText(" clean Dir ( " + QString::number(c_globalVar.s_compare.listDirDelete.size()) + " ) ");

    if (waitCompare != nullptr) {
        waitCompare->hide();
        delete waitCompare;
        waitCompare = nullptr;
    }

    if (refresh_auto)
        this->setEnabled(true);

    refresh_auto = false;

    //    cWdgCompare* wdg_compare = new cWdgCompare();
    //    wdg_compare->show();
}

void cMainWindow::p_cmp_Copy_Slot()
{
    this->setEnabled(false);

    if (c_globalVar.s_compare.listFileCopy.size() > 0) {

        qpb_progressBar->setRange(0, c_globalVar.s_compare.listFileCopy.size());
        qpb_progressBar->setValue(0);

        qpb_progressBar->setVisible(true);

        mainThread->initMainThread(e_action_copy);
        mainThread->startMainThread();

        refresh_auto = true;

    } else
        this->setEnabled(true);
}
void cMainWindow::p_cmp_Modify_Slot()
{
    this->setEnabled(false);

    if (c_globalVar.s_compare.listFileModify.size() > 0) {

        qpb_progressBar->setRange(0, c_globalVar.s_compare.listFileModify.size());
        qpb_progressBar->setValue(0);

        qpb_progressBar->setVisible(true);

        mainThread->initMainThread(e_action_modify);
        mainThread->startMainThread();

        refresh_auto = true;

    } else
        this->setEnabled(true);
}
void cMainWindow::p_cmp_Delete_Slot()
{
    this->setEnabled(false);

    if (c_globalVar.s_compare.listFileDelete.size() > 0) {

        qpb_progressBar->setRange(0, c_globalVar.s_compare.listFileDelete.size());
        qpb_progressBar->setValue(0);

        qpb_progressBar->setVisible(true);

        mainThread->initMainThread(e_action_delete);
        mainThread->startMainThread();

        refresh_auto = true;

    } else
        this->setEnabled(true);
}
void cMainWindow::p_cmp_ClearDir_Slot()
{
    this->setEnabled(false);

    if (c_globalVar.s_compare.listDirDelete.size() > 0) {

        qpb_progressBar->setRange(0, c_globalVar.s_compare.listDirDelete.size());
        qpb_progressBar->setValue(0);

        qpb_progressBar->setVisible(true);

        mainThread->initMainThread(e_action_dir_delete);
        mainThread->startMainThread();

        refresh_auto = true;

    } else
        this->setEnabled(true);
}

void cMainWindow::p_update_Copy_Slot()
{
    listComp_Copy->setCurrentRow(c_globalVar.idxFile);
    //    p_compareFinishSlot();
}
void cMainWindow::p_update_Modify_Slot()
{
    listComp_Modify->setCurrentRow(c_globalVar.idxFile);
    //    p_compareFinishSlot();
}
void cMainWindow::p_update_Delete_Slot()
{
    listComp_Delete->setCurrentRow(c_globalVar.idxFile);
    //    p_compareFinishSlot();
}
void cMainWindow::p_update_Dir_Delete_Slot()
{
    listComp_Dir_Delete->setCurrentRow(c_globalVar.idxFile);
    //     p_compareFinishSlot();
}

void cMainWindow::p_src_check_exept_folders_Slot(bool _check)
{
    c_globalVar.b_src_exept_folders = _check;
    qDebug() << "b_src_exept_folders" << c_globalVar.b_src_exept_folders;

    QString _srcPath = qle_pathSrc->text();
    if(_srcPath.size() > 0)
        loadSrcList(_srcPath);
}
void cMainWindow::p_src_check_exept_files_Slot(bool _check)
{
    c_globalVar.b_src_exept_files = _check;
    qDebug() << "b_src_exept_files" << c_globalVar.b_src_exept_files;

    QString _srcPath = qle_pathSrc->text();
    if(_srcPath.size() > 0)
        loadSrcList(_srcPath);
}
void cMainWindow::p_dst_check_exept_folders_Slot(bool _check)
{
    c_globalVar.b_dst_exept_folders = _check;
    qDebug() << "b_dst_exept_folders" << c_globalVar.b_dst_exept_folders;

    QString _dstPath = qle_pathDst->text();
    if(_dstPath.size() > 0)
        loadDstList(_dstPath);
}
void cMainWindow::p_dst_check_exept_files_Slot(bool _check)
{
    c_globalVar.b_dst_exept_files = _check;
    qDebug() << "b_dst_exept_files" << c_globalVar.b_dst_exept_files;

    QString _dstPath = qle_pathDst->text();
    if(_dstPath.size() > 0)
        loadDstList(_dstPath);
}
