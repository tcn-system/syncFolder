#include "waitWindow.h"

#include <QAction>
#include <QCoreApplication>
#include <QMouseEvent>
#include <QPainter>
#include <QTime>
#include <QTimer>

cWaitWindows::cWaitWindows(QWidget* parent)
    : QWidget(parent, Qt::FramelessWindowHint | Qt::WindowSystemMenuHint)
{
    sizeParent = parent->size();

    setAttribute(Qt::WA_TranslucentBackground);

    QString style = "background:rgba(240,240,240,1);";
    setStyleSheet(style);

    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&cWaitWindows::update));
    i_pos = 0;
    timer->start(100);
}

void cWaitWindows::paintEvent(QPaintEvent*)
{
    Qt::PenStyle style = Qt::SolidLine;
    Qt::PenCapStyle cap = Qt::FlatCap;
    Qt::PenJoinStyle join = Qt::MiterJoin;

    QColor _blueColor(20, 140, 210, 255);

    int side = 200; // qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    painter.setPen(QPen(_blueColor, 4, style, cap, join));
    painter.setBrush(palette().window());
    painter.drawEllipse(QPoint(0, 0), 98, 98);

    painter.setPen(Qt::NoPen);
    painter.setBrush(_blueColor);

    painter.save();
    painter.rotate(6.0 * i_pos);
    painter.drawRoundedRect(0, 0, 70, 70, 35, 35);
    painter.restore();

    i_pos++;
    if (i_pos >= 60)
        i_pos++;
}

QSize cWaitWindows::sizeHint() const
{
    return sizeParent; // QSize(200, 200);
}
