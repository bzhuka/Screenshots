#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QThread>
#include <QTimer>
#include <QWidget>
#include <QWindow>

#include "screenshotwindow.h"

class screenshotWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updatePixmap(QPixmap newPixmap);

public slots:

private slots:
    void handleSSRelease();

private:
    void setup();
    void hideWindow();
    void showWindow();
    void openSSWindow();

    Ui::MainWindow *ui;

    QPixmap mBasePixmap;
    QLabel* pScreenshotLabel;

    screenshotWindow* pSS;
};

#endif // MAINWINDOW_H
