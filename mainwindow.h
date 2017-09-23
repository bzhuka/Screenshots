#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "screenshot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleSSRelease();

private:
    void setup();
    void hideWindow();
    void showWindow();
    void updatePixmap();

    Ui::MainWindow *ui;

    QPixmap mBasePixmap;
    QLabel* pScreenshotLabel;

    Screenshot* pSS;
};

#endif // MAINWINDOW_H
