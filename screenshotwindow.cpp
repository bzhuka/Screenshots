#include "screenshotwindow.h"

screenshotWindow::screenshotWindow(MainWindow* parent = NULL)
{
    pParent = parent;
    resize(QApplication::desktop()->size());
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void screenshotWindow::updatePixmap(QPixmap pixmap) {
    mPixmap = pixmap;
}

void screenshotWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(100,100,100, 127));

    painter.drawRect(0, 0, width(),  height());
}

void screenshotWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    pParent->updatePixmap(mPixmap);
    hide();
}
