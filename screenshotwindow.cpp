#include "screenshotwindow.h"

#include "mainwindow.h"

screenshotWindow::screenshotWindow(MainWindow* parent = NULL)
{
    started = false;
    pParent = parent;
    resize(QApplication::desktop()->size());
    setAutoFillBackground(false);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
}

void screenshotWindow::updatePixmap(QPixmap pixmap) {
    mPixmap = pixmap;
}

//void screenshotWindow::updateRectangle() {

//}

void screenshotWindow::paintEvent(QPaintEvent *)
{
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(100,100,100, 127));

        painter.drawRect(0, 0, width(),  height());
        if (started) {
            QPainter painter(this);

            int x, y, w, h;
            if (mPoint1.x() < mPoint2.x()) {
                x = mPoint1.x();
            } else {
                x = mPoint2.x();
            }
            if (mPoint1.y() < mPoint2.y()) {
                y = mPoint1.y();
            } else{
                y = mPoint2.y();
            }
            w = std::abs(mPoint1.x() - mPoint2.x());
            h = std::abs(mPoint1.y() - mPoint2.y());
            QRect rect1(x, y, w, h);
            painter.drawPixmap(rect1, mPixmap, rect1);
            mRect = rect1;

            QPen pen(Qt::red, 2);
            painter.setPen(pen);
            painter.drawRect(rect1);
        }
}

void screenshotWindow::mouseDoubleClickEvent(QMouseEvent* event)
{
    pParent->updatePixmap(mPixmap);
    hide();
}

void screenshotWindow::mousePressEvent(QMouseEvent* event)
{
    started = true;
    mPoint1 = event->pos();
}

void screenshotWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (mPoint1 != mPoint2) {
        QPixmap cropped = mPixmap.copy(mRect);
        pParent->updatePixmap(cropped);
        hide();
    }
    mPoint1 = QPoint(0,0);
    mPoint2 = QPoint(0,0);
    started = false;
}

void screenshotWindow::mouseMoveEvent(QMouseEvent* event)
{
    mPoint2 = event->pos();
    update();
}
