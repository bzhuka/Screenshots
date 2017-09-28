#ifndef SCREENSHOTWINDOW_H
#define SCREENSHOTWINDOW_H

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QRect>
#include <QWidget>
#include <iostream>
#include "math.h"

class MainWindow;

class screenshotWindow: public QWidget
{
public:
    screenshotWindow(MainWindow* parent);
    void updatePixmap(QPixmap);

    //Events
    void paintEvent(QPaintEvent*);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);

private:
    //void updateRectangle();

    bool started;

    MainWindow* pParent;
    QPoint mPoint1;
    QPoint mPoint2;
    QPixmap mPixmap;
    QRect mRect;
};

#endif // SCREENSHOTWINDOW_H
