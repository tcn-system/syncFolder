#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QSpinBox>

#include <QCloseEvent>
#include <QFileDialog>

#include <QListWidget>

#include "GlobalVar.h"
#include "mainThread.h"
#include "syncFolder.h"

#include "thread.h"

#include "wdgCompare.h"

#include "waitWindow.h"

class cMainWindow : public QMainWindow {
    Q_OBJECT

public:
    cMainWindow(QWidget* parent = nullptr);
    ~cMainWindow();

public slots:

    void p_loadProfileSlot(int idx);

    void p_selectPathSrcSlot();
    void p_readSrcFolderFinishSlot();

    void p_selectPathDstSlot();
    void p_readDstFolderFinishSlot();

    void p_cmp_Copy_Slot();
    void p_cmp_Modify_Slot();
    void p_cmp_Delete_Slot();

    void p_cmp_ClearDir_Slot();

    void p_compareSlot();
    void p_compareFinishSlot();

    void p_copyInProcessSlot();
    void p_copyFinishedSlot();

    void p_update_Copy_Slot();
    void p_update_Modify_Slot();
    void p_update_Delete_Slot();

    void p_update_Dir_Delete_Slot();

    void p_src_check_exept_folders_Slot(bool _check);
    void p_src_check_exept_files_Slot(bool _check);
    void p_dst_check_exept_folders_Slot(bool _check);
    void p_dst_check_exept_files_Slot(bool _check);

private:
    void closeEvent(QCloseEvent* ce);

    QComboBox* qcb_loadProfile;

    QPushButton* qpb_selectPathSrc;
    QLineEdit* qle_pathSrc;
    QListWidget* listSrc = nullptr;
    void loadSrcList(QString _srcPath);
    QCheckBox* qcb_src_exeptFolders;
    QSpinBox* qsb_nbre_src_folders;
    QCheckBox* qcb_src_exeptFiles;
    QSpinBox* qsb_nbre_src_files;

    void setEnable_Src(bool _stat);

    QPushButton* qpb_selectPathDst;
    QLineEdit* qle_pathDst;
    QListWidget* listDst = nullptr;
    void loadDstList(QString _dstPath);
    QCheckBox* qcb_dst_exeptFolders;
    QSpinBox* qsb_nbre_dst_folders;
    QCheckBox* qcb_dst_exeptFiles;
    QSpinBox* qsb_nbre_dst_files;

    void setEnable_Dst(bool _stat);

    QListWidget* listComp_Copy = nullptr;
    QPushButton* qpb_cmpCopy;
    QListWidget* listComp_Modify = nullptr;
    QPushButton* qpb_cmpModify;
    QListWidget* listComp_Delete = nullptr;
    QPushButton* qpb_cmpDelete;

    QPushButton* qpb_compare;

    QListWidget* listComp_Dir_Delete = nullptr;
    QPushButton* qpb_clearDir;

    QProgressBar* qpb_progressBar;

    cSyncFolder* syncFolder = nullptr;
    cMainThread* mainThread = nullptr;

    cWaitWindows* waitSrcRead = nullptr;
    cWaitWindows* waitDstRead = nullptr;
    cWaitWindows* waitCompare = nullptr;

    bool refresh_auto;
};

#endif // MAINWINDOW_H_
