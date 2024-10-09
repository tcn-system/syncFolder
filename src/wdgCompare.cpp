
#include "wdgCompare.h"

#include "tcnStyle.h"

#include "GlobalVar.h"

cWdgCompare::cWdgCompare(QWidget* parent)
    : QWidget(parent)
{
    pathFolder = c_globalVar.s_folderSrc.folder_dir + " - vs - " + c_globalVar.s_folderDst.folder_dir;

    QString _style = "";

    _style += "QGroupBox {";
    _style += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_grey) + ";";
    _style += "border: 4px solid " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_dark_blue) + ";";
    _style += "border-radius: 10px;";
    _style += "margin-top: 6px;";
    _style += "padding-top: 10px;";
    _style += "padding-bottom: 10px;";
    _style += "font-weight: 500;";
    _style += "}\n";

    _style += "QGroupBox:title {";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "subcontrol-origin: margin;";
    _style += "left: 7px;";
    _style += "padding: 0px 5px 0px 5px;";
    _style += "}\n";

    QString _styleLabel = "";

    _styleLabel += "QLabel {";
    _styleLabel += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_grey) + ";";
    _styleLabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_dark) + ";";
    _styleLabel += "}\n";

    QVBoxLayout* main_layout = new QVBoxLayout;

    group_box = new QGroupBox;
    {
        group_box->setTitle(pathFolder);

        group_box->setStyleSheet(_style);

        QHBoxLayout* file_layout = new QHBoxLayout;

        ql_dirDetected = new QLabel;
        ql_dirDetected->setText(" dir src : " + QString::number(c_globalVar.s_folderSrc.listDir.size()));
        ql_dirDetected->setStyleSheet(_styleLabel);
        file_layout->addWidget(ql_dirDetected);

        ql_dirExcluded = new QLabel;
        ql_dirExcluded->setText(" file src : " + QString::number(c_globalVar.s_folderSrc.listFile.size()));
        ql_dirExcluded->setStyleSheet(_styleLabel);
        file_layout->addWidget(ql_dirExcluded);

        ql_fileDetected = new QLabel;
        ql_fileDetected->setText(" dir dst : " + QString::number(c_globalVar.s_folderDst.listDir.size()));
        ql_fileDetected->setStyleSheet(_styleLabel);
        file_layout->addWidget(ql_fileDetected);

        ql_fileExcluded = new QLabel;
        ql_fileExcluded->setText(" file dst : " + QString::number(c_globalVar.s_folderDst.listFile.size()));
        ql_fileExcluded->setStyleSheet(_styleLabel);
        file_layout->addWidget(ql_fileExcluded);

        group_box->setLayout(file_layout);
    }

    main_layout->addWidget(group_box);

    l_listFile.clear();

    createListCompare();

    trierListCompare();

    QGridLayout* grid_layout = new QGridLayout;
    // QVBoxLayout* grid_layout = new QVBoxLayout;

    for (int i = 0; i < l_listFile.size(); i++) {

        switch (l_listFile.at(i).e_stat) {
        case e_stat_file_none:
            break;
        case e_stat_file_equal: {
            cWdgInfoFile* _infofile = new cWdgInfoFile(l_listFile.at(i)._pathSrc, c_tcnStyle->_c_tcn_light_green);
            grid_layout->addWidget(_infofile, i, 0, 1, 2);
        } break;
        case e_stat_file_modify: {
            cWdgInfoFile* _infofile = new cWdgInfoFile(l_listFile.at(i)._pathSrc, l_listFile.at(i)._pathDst, c_tcnStyle->_c_tcn_light_grey);
            grid_layout->addWidget(_infofile, i, 0, 1, 2);
        } break;
        case e_stat_file_copy: {
            cWdgInfoFile* _infofile = new cWdgInfoFile(l_listFile.at(i)._pathSrc, c_tcnStyle->_c_tcn_light_blue);
            grid_layout->addWidget(_infofile, i, 0, 1, 1);
        } break;
        case e_stat_file_delete: {
            cWdgInfoFile* _infofile = new cWdgInfoFile(l_listFile.at(i)._pathDst, c_tcnStyle->_c_tcn_light_red);
            grid_layout->addWidget(_infofile, i, 1, 1, 1);
        } break;
        }

        //        grid_layout->addWidget(_infofile);
    }

    QWidget* _widget = new QWidget;
    _widget->setLayout(grid_layout);

    QScrollBar* _scrollBarH = new QScrollBar;
    QScrollBar* _scrollBarV = new QScrollBar;

    QScrollArea* _scrollArea = new QScrollArea;
    {
        _scrollArea->setBackgroundRole(QPalette::Dark);
        _scrollArea->setWidgetResizable(true);
        _scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _scrollArea->setHorizontalScrollBar(_scrollBarH);
        _scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        _scrollArea->setVerticalScrollBar(_scrollBarV);
        _scrollArea->setWidget(_widget);
    }
    main_layout->addWidget(_scrollArea);

    setLayout(main_layout);
}

void cWdgCompare::createListCompare()
{
    sListFileCompare _fileCompare;

    for (int i_src = 0; i_src < c_globalVar.s_folderSrc.listFile.size(); i_src++) {

        bool existe = false;

        QFile _fileSrc(c_globalVar.s_folderSrc.listFile.at(i_src).path_full);

        _fileCompare.init();

        _fileCompare._pathSrc = c_globalVar.s_folderSrc.listFile.at(i_src).path_full;
        _fileCompare._sizeSrc = _fileSrc.size();

        _fileCompare._path = c_globalVar.s_folderSrc.listFile.at(i_src).path;

        for (int i_dst = 0; i_dst < c_globalVar.s_folderDst.listFile.size(); i_dst++) {

            if (not c_globalVar.s_folderSrc.listFile.at(i_src).path.compare(c_globalVar.s_folderDst.listFile.at(i_dst).path)) {

                existe = true;

                QFile _fileDst(c_globalVar.s_folderDst.listFile.at(i_dst).path_full);

                _fileCompare._pathDst = c_globalVar.s_folderDst.listFile.at(i_dst).path_full;
                _fileCompare._sizeDst = _fileDst.size();

                if (_fileSrc.size() != _fileDst.size()) {
                    _fileCompare.e_stat = e_stat_file_modify;
                } else {
                    _fileCompare.e_stat = e_stat_file_equal;
                }

                i_dst = c_globalVar.s_folderDst.listFile.size();
            }
        }
        if (not existe) {

            _fileCompare.e_stat = e_stat_file_copy;
        }

        l_listFile.push_back(_fileCompare);
    }

    for (int i_dst = 0; i_dst < c_globalVar.s_folderDst.listFile.size(); i_dst++) {

        bool existe = false;

        QFile _fileDst(c_globalVar.s_folderDst.listFile.at(i_dst).path_full);

        _fileCompare.init();

        _fileCompare._pathDst = c_globalVar.s_folderDst.listFile.at(i_dst).path_full;
        _fileCompare._sizeDst = _fileDst.size();

        _fileCompare._path = c_globalVar.s_folderDst.listFile.at(i_dst).path;

        for (int i_src = 0; i_src < c_globalVar.s_folderSrc.listFile.size(); i_src++) {

            if (not c_globalVar.s_folderSrc.listFile.at(i_src).path.compare(c_globalVar.s_folderDst.listFile.at(i_dst).path)) {

                existe = true;

                i_src = c_globalVar.s_folderSrc.listFile.size();
            }
        }
        if (not existe) {

            _fileCompare.e_stat = e_stat_file_delete;

            l_listFile.push_back(_fileCompare);
        }
    }
}

void cWdgCompare::trierListCompare()
{
    for (int i = 0; i < l_listFile.size(); i++) {
    }
}

cWdgInfoFile::cWdgInfoFile(QString _pathFile, QColor _background_color, QWidget* parent)
    : QWidget(parent)
{
    QFile _file(_pathFile);
    QFileInfo _fileInfo(_pathFile);

    QString _style = "";

    _style += "QGroupBox {";
    _style += "background-color: " + c_tcnStyle->_to_rgba(_background_color) + ";";
    _style += "border: 4px solid " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "margin-top: 6px;";
    _style += "padding-top: 10px;";
    _style += "padding-bottom: 10px;";
    _style += "font-weight: 500;";
    _style += "}\n";

    _style += "QGroupBox:title {";
    _style += "subcontrol-origin: margin;";
    _style += "left: 7px;";
    _style += "padding: 0px 5px 0px 5px;";
    _style += "}\n";

    QString _styleLabel = "";

    _styleLabel += "QLabel {";
    _styleLabel += "background-color: " + c_tcnStyle->_to_rgba(_background_color) + ";";
    _styleLabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_dark) + ";";
    _styleLabel += "}\n";

    QString _styleLine = "";

    _styleLine += "QLineEdit {";
    _styleLine += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_grey) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _styleLine += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    //    _style += "border-radius: 10px;";
    _styleLine += "min-height: 1.5em;";
    _styleLine += "margin: 2px 2px 2px 10px;";
    _styleLine += "padding: 2px 2px 2px 10px;";
    //    _style += "font-weight: 500;";
    _styleLine += "}\n";

    QVBoxLayout* main_layout = new QVBoxLayout;

    QGroupBox* group_box = new QGroupBox;
    {
        group_box->setTitle(_pathFile);

        group_box->setStyleSheet(_style);

        QHBoxLayout* file_layout = new QHBoxLayout;

        QLineEdit* ql_size = new QLineEdit;
        ql_size->setText(" size : " + QString::number(_file.size()));
        ql_size->setStyleSheet(_styleLine);
        file_layout->addWidget(ql_size);

        QLineEdit* ql_suffix = new QLineEdit;
        ql_suffix->setText(" ext : " + _fileInfo.suffix());
        ql_suffix->setStyleSheet(_styleLine);
        file_layout->addWidget(ql_suffix);

        QLineEdit* ql_baseName = new QLineEdit;
        ql_baseName->setText(" base : " + _fileInfo.baseName());
        ql_baseName->setStyleSheet(_styleLine);
        file_layout->addWidget(ql_baseName);

        group_box->setLayout(file_layout);
    }

    main_layout->addWidget(group_box);

    setLayout(main_layout);
}

cWdgInfoFile::cWdgInfoFile(QString _pathFileSrc, QString _pathFileDst, QColor _background_color, QWidget* parent)
    : QWidget(parent)
{
    QFile _fileSrc(_pathFileSrc);
    QFileInfo _fileInfoSrc(_pathFileSrc);

    QFile _fileDst(_pathFileDst);
    QFileInfo _fileInfoDst(_pathFileDst);

    QString _style = "";

    _style += "QGroupBox {";
    _style += "background-color: " + c_tcnStyle->_to_rgba(_background_color) + ";";
    _style += "border: 4px solid " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    _style += "border-radius: 10px;";
    _style += "margin-top: 6px;";
    _style += "padding-top: 10px;";
    _style += "padding-bottom: 10px;";
    _style += "font-weight: 500;";
    _style += "}\n";

    _style += "QGroupBox:title {";
    _style += "subcontrol-origin: margin;";
    _style += "left: 7px;";
    _style += "padding: 0px 5px 0px 5px;";
    _style += "}\n";

    QString _styleLabel = "";

    _styleLabel += "QLabel {";
    _styleLabel += "background-color: " + c_tcnStyle->_to_rgba(_background_color) + ";";
    _styleLabel += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_dark) + ";";
    _styleLabel += "}\n";

    QString _styleLine = "";

    _styleLine += "QLineEdit {";
    _styleLine += "background-color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_light_grey) + ";";
    //    _style += "border: 4px solid " + _to_rgba(_c_tcn_black) + ";";
    _styleLine += "color: " + c_tcnStyle->_to_rgba(c_tcnStyle->_c_tcn_black) + ";";
    //    _style += "border-radius: 10px;";
    _styleLine += "min-height: 1.5em;";
    _styleLine += "margin: 2px 2px 2px 10px;";
    _styleLine += "padding: 2px 2px 2px 10px;";
    //    _style += "font-weight: 500;";
    _styleLine += "}\n";

    QVBoxLayout* main_layout = new QVBoxLayout;

    QGroupBox* group_box = new QGroupBox;
    {
        group_box->setTitle(_pathFileSrc + " - " + _pathFileDst);

        group_box->setStyleSheet(_style);

        QVBoxLayout* file_layout = new QVBoxLayout;

        QHBoxLayout* file_src_layout = new QHBoxLayout;
        {
            QLineEdit* ql_size = new QLineEdit;
            ql_size->setText(" size : " + QString::number(_fileSrc.size()));
            ql_size->setStyleSheet(_styleLine);
            file_src_layout->addWidget(ql_size);

            QLineEdit* ql_suffix = new QLineEdit;
            ql_suffix->setText(" ext : " + _fileInfoSrc.suffix());
            ql_suffix->setStyleSheet(_styleLine);
            file_src_layout->addWidget(ql_suffix);

            QLineEdit* ql_baseName = new QLineEdit;
            ql_baseName->setText(" base : " + _fileInfoSrc.baseName());
            ql_baseName->setStyleSheet(_styleLine);
            file_src_layout->addWidget(ql_baseName);
        }
        file_layout->addLayout(file_src_layout);

        QHBoxLayout* file_dst_layout = new QHBoxLayout;
        {
            QLineEdit* ql_size = new QLineEdit;
            ql_size->setText(" size : " + QString::number(_fileDst.size()));
            ql_size->setStyleSheet(_styleLine);
            file_dst_layout->addWidget(ql_size);

            QLineEdit* ql_suffix = new QLineEdit;
            ql_suffix->setText(" ext : " + _fileInfoDst.suffix());
            ql_suffix->setStyleSheet(_styleLine);
            file_dst_layout->addWidget(ql_suffix);

            QLineEdit* ql_baseName = new QLineEdit;
            ql_baseName->setText(" base : " + _fileInfoDst.baseName());
            ql_baseName->setStyleSheet(_styleLine);
            file_dst_layout->addWidget(ql_baseName);
        }
        file_layout->addLayout(file_dst_layout);

        group_box->setLayout(file_layout);
    }

    main_layout->addWidget(group_box);

    setLayout(main_layout);
}
