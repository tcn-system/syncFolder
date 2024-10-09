#ifndef TCN_STYLE_H_
#define TCN_STYLE_H_

#include <QApplication>
#include <QColor>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QtCore/QCoreApplication>

enum eQPb_check {
    e_qpb_uncheck,
    e_qpb_check,
};

enum eProfileColor {
    e_profile_none,
    e_profile_background,
    e_profile_border,
    e_profile_text,
};

enum eProfileChoose {
    e_profile_choose_none,
    e_profile_choose_standard,
    e_profile_choose_dark,
};

class cTcnStyle {

public:
    cTcnStyle(QApplication* _app, eProfileChoose _choose_profile = e_profile_choose_none);
    ~cTcnStyle();

    bool load_tcnStyle();
    QString _to_rgba(QColor _color);
    QColor _profile_color[10];

    int _f_font_size;
    QString _f_font_family;

    QColor _c__white;
    QColor _c__black;
    QColor _c__green;
    QColor _c__red;
    QColor _c__blue;
    QColor _c__transparent;

    QColor _c_tcn_white;
    QColor _c_tcn_black;
    QColor _c_tcn_dark;

    QColor _c_tcn_blue;
    QColor _c_tcn_dark_blue;
    QColor _c_tcn_light_blue;

    QColor _c_tcn_grey;
    QColor _c_tcn_light_grey;

    QColor _c_tcn_green;
    QColor _c_tcn_dark_green;
    QColor _c_tcn_light_green;

    QColor _c_tcn_red;
    QColor _c_tcn_dark_red;
    QColor _c_tcn_light_red;

    QColor _c_tcn_orange;
    QColor _c_tcn_purple;
    QColor _c_tcn_purple_a127;

    QString styleSheet_QApplication();

    QString styleSheet_QMainWindow();
    QString styleSheet_QWidget();
    QString styleSheet_QLineEdit();
    QString styleSheet_QGroupBox();
    QString styleSheet_QSplitter();

    QString styleSheet_QPushButton(eQPb_check _eQpb = e_qpb_uncheck);
    QString styleSheet_QDoubleSpinBox();
    QString styleSheet_QSpinBox();
    QString styleSheet_QDateTimeEdit();
    QString styleSheet_QScrollBar();
    QString styleSheet_QPlainTextEdit();

    QString styleSheet_QTabWidget();
    QString styleSheet_QTabBar();
    QString styleSheet_QCheckBox();
    QString styleSheet_QComboBox();
    QString styleSheet_QProgressBar();

    QString styleSheet_QTableWidget();
    QString styleSheet_QListWidget();

    QString styleSheet_CustomWidget();

private:
    QApplication* app;
};

extern cTcnStyle* c_tcnStyle;

#endif // TCN_STYLE_H_
