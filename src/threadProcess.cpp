#include "threadProcess.h"
#include <QtCore/qdebug.h>

#include "GlobalVar.h"
//#include "Tools.h"

cProcess::cProcess(QThread* qt_th, eTypeAction _typeAction)
    : QObject(nullptr)
{
    moveToThread(qt_th);
    setChunkSize(DEFAULT_CHUNK_SIZE);

    if (_typeAction == e_action_delete)
        QObject::connect(qt_th, &QThread::started, this, &cProcess::p_processDelete);
    else
        QObject::connect(qt_th, &QThread::started, this, &cProcess::p_processCopy);
    QObject::connect(this, &cProcess::p_emitFinished, qt_th, &QThread::quit);
    QObject::connect(this, &cProcess::p_emitFinished, this, &cProcess::deleteLater);
    QObject::connect(qt_th, &QThread::finished, qt_th, &QThread::deleteLater);
}

cProcess::~cProcess()
{
}

void cProcess::p_processDelete()
{
    if (qs_dst.isEmpty()) {
        qWarning() << QStringLiteral("destination paths are empty!");
        emit p_emitFinished(false);
        return;
    }

    QFile qf_dstFile(qs_dst);
    QFileInfo qfi_f_dst(qs_dst);

    qf_dstFile.remove();

    QDir _dir(qfi_f_dst.absoluteDir());

    if (_dir.exists()) {
        if (_dir.isEmpty()) {
            _dir.removeRecursively();
        }
    }

    emit p_emitFinished(true);
}
void cProcess::p_processCopy()
{
    qint64 i_written = 0;
    qint64 i_totalSrc = 0;

    // loop here
    if (qs_src.isEmpty() || qs_dst.isEmpty()) {
        qWarning() << QStringLiteral("source or destination paths are empty!");
        emit p_emitFinished(false);
        return;
    }
    QFileInfo qfi_f_src(qs_src);
    i_totalSrc = qfi_f_src.size();

    // qInfo() << QStringLiteral("%1 bytes should be write in total").arg(i_totalSrc);

    QFile qf_srcFile(qs_src);
    QFile qf_dstFile(qs_dst);

    QFileInfo qfi_f_dst(qs_dst);
    QDir _dir(qfi_f_dst.absoluteDir());

    if (not _dir.exists()) {
        if (not _dir.mkpath("."))
            qWarning() << QStringLiteral("destination directory error make!");
    }

    if (QFile::exists(qs_dst)) {

        QFile::remove(qs_dst);
    }

    if (!qf_srcFile.open(QFileDevice::ReadOnly)) {
        qWarning() << QStringLiteral("SRC failed to open %1 (error:%2)").arg(qs_src, qf_srcFile.errorString());
        return;
    }

    if (!qf_dstFile.open(QFileDevice::WriteOnly)) {
        qWarning() << QStringLiteral("DST failed to open %1 (error:%2)").arg(qs_dst, qf_dstFile.errorString());
        return;
    }

    qint64 fSize = qf_srcFile.size();
    while (fSize) {
        const auto data = qf_srcFile.read(chunkSize());
        const auto _written = qf_dstFile.write(data);
        if (data.size() == _written) {
            i_written += _written;
            fSize -= data.size();
            emit p_emitInProgress(i_written, i_totalSrc);
        } else {
            qWarning() << QStringLiteral("failed to write to %1 (error:%2)").arg(qf_dstFile.fileName()).arg(qf_dstFile.errorString());
            fSize = 0;
            break; // skip this operation
        }
    }

    qf_srcFile.close();
    qf_dstFile.close();

    if (!qf_dstFile.open(QFileDevice::Append)) {
        qWarning() << QStringLiteral("DST failed to open %1 (error:%2)").arg(qs_dst, qf_dstFile.errorString());
        return;
    }
    //    if (!qf_dstFile.setFileTime(qfi_f_src.birthTime(), QFileDevice::FileBirthTime)) {
    //        qDebug() << "Failed to modify - Birth time!";
    //    }
    if (!qf_dstFile.setFileTime(qfi_f_src.lastModified(), QFileDevice::FileModificationTime)) {
        qDebug() << "Failed to modify - Modification time!";
    }
    qf_dstFile.close();

    if (i_totalSrc == i_written)
        emit p_emitFinished(true);
    else
        emit p_emitFinished(false);
}

cThreadProcess::cThreadProcess(QWidget* qw_parent)
    : QWidget(qw_parent)
{
    QVBoxLayout* main_window = new QVBoxLayout();
    {
        ql_editProgressBar = new QLabel;
        ql_editProgressBar->adjustSize();
        ql_editProgressBar->setText("none");
        main_window->addWidget(ql_editProgressBar);

        qpb_progressBar = new QProgressBar;
        qpb_progressBar->setMaximum(100);
        qpb_progressBar->setMinimum(0);
        qpb_progressBar->setValue(0);
        qpb_progressBar->setTextVisible(true);
        qpb_progressBar->setFormat("0 %");
        qpb_progressBar->setAlignment(Qt::AlignCenter);
        // qpb_progressBar[i]->adjustSize();
        main_window->addWidget(qpb_progressBar);
    }
    setLayout(main_window);
}
cThreadProcess::~cThreadProcess()
{
}

bool cThreadProcess::p_copy(QString qs_name, QString qs_srcPath, QString qs_destPath)
{
    qt_thread = new QThread;
    m_process = new cProcess(qt_thread, e_action_copy);
    connect(m_process, &cProcess::p_emitFinished, this, &cThreadProcess::p_receptFinishedSlot);
    connect(m_process, &cProcess::p_emitInProgress, this, &cThreadProcess::p_receptInProcessSlot);

    ql_editProgressBar->setText("File: " + qs_name);
    m_process->setSourcePaths(qs_srcPath);
    m_process->setDestinationPaths(qs_destPath);

    qt_thread->start();

    return true;
}

bool cThreadProcess::p_delete(QString qs_name, QString qs_srcPath, QString qs_destPath)
{
    qt_thread = new QThread;
    m_process = new cProcess(qt_thread, e_action_delete);
    connect(m_process, &cProcess::p_emitFinished, this, &cThreadProcess::p_receptFinishedSlot);
    connect(m_process, &cProcess::p_emitInProgress, this, &cThreadProcess::p_receptInProcessSlot);

    ql_editProgressBar->setText("File: " + qs_name);
    m_process->setSourcePaths(qs_srcPath);
    m_process->setDestinationPaths(qs_destPath);

    qt_thread->start();

    return true;
}

void cThreadProcess::p_receptInProcessSlot(qint64 i_idx, qint64 i_total)
{
    qpb_progressBar->setValue((i_idx * 100) / i_total);
    qpb_progressBar->setFormat(QString::number((i_idx * 100) / i_total) + " % ( " + QString::number(i_total / 1000000.0) + " Mo )");
}
void cThreadProcess::p_receptFinishedSlot(bool b_success)
{
    if (m_process != nullptr) {
        // delete m_process;
        m_process = nullptr;
    }
    if (qt_thread != nullptr) {
        qt_thread->exit();
        // delete qt_thread;
        qt_thread = nullptr;
    }

    emit p_emitFinished(b_success);
}
