#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>

class cWaitWindows : public QWidget {
    Q_OBJECT

public:
    cWaitWindows(QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int i_pos;

    QSize sizeParent;
};

#endif // MAINWINDOW_H
