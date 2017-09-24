#ifndef SCREENSHOTWINDOW_H
#define SCREENSHOTWINDOW_H

#include "mainwindow.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPixmap>
#include <QWidget>

class MainWindow;

class screenshotWindow: public QWidget
{
public:
    screenshotWindow(MainWindow* parent);
    void updatePixmap(QPixmap);

    //Events
    void paintEvent(QPaintEvent*);
    void mouseDoubleClickEvent(QMouseEvent* event);

private:
    MainWindow* pParent;

    QPixmap mPixmap;
};

#endif // SCREENSHOTWINDOW_H
