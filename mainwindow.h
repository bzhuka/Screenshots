#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QBoxLayout>
#include <QDesktopWidget>
#include <QFile>
#include <QGuiApplication>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
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

    void resizeEvent(QResizeEvent *);
    void updatePixmap(QPixmap newPixmap);

public slots:

private slots:
    void handleSSRelease();

private:
    void setup();
    void hideWindow();
    void showWindow();
    void openSSWindow();
    void updateScreenShotLabel();

    Ui::MainWindow *ui;

    QPixmap mBasePixmap;
    QLabel* imageLabel;
    QPushButton* ssButton;
    QPushButton* saveButton;
    QVBoxLayout* mainLayout;
    QHBoxLayout* buttonsLayout;
    QWidget* central;

    screenshotWindow* pSS;
};

#endif // MAINWINDOW_H
