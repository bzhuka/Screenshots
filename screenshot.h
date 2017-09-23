#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QApplication>
#include <QDesktopWidget>
#include <QGuiApplication>
#include <QLabel>
#include <QScreen>
#include <QTimer>
#include <QWidget>
#include <QWindow>

class Screenshot: public QWidget
{
    Q_OBJECT

public:
    Screenshot();
    void takeScreenshot();
    QPixmap getPixmap();

private:
    QPixmap mOriginalPixmap;
    QLabel* pScreenshotLabel;
};

#endif // SCREENSHOT_H
