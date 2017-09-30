#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QApplication>
#include <QBoxLayout>
#include <QColorDialog>
#include <QDesktopWidget>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QGuiApplication>
#include <QImageWriter>
#include <QInputDialog>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QSpinBox>
#include <QStandardPaths>
#include <QStringList>
#include <QThread>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>
#include <QWindow>

#include "screenshotwindow.h"
#include "drawarea.h"

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
    void handleSaveRelease();
    void handleEditButton();
    void handleSSRelease();

    void penColor();
    void penWidth();

private:
    void setup();
    void hideWindow();
    void showWindow();
    void openSSWindow();
    void updateScreenShotLabel();

    Ui::MainWindow *ui;

    DrawArea* drawArea;

    QPixmap mBasePixmap;
    QLabel* imageLabel;
    QPushButton* ssButton;
    QPushButton* editButton;
    QPushButton* saveButton;
    QVBoxLayout* mainLayout;
    QWidget* buttonsWidget;
    QHBoxLayout* buttonsLayout;
    QHBoxLayout* editingButtonsLayout;
    QSpinBox* penSizeBox;
    QWidget* central;

    QAction* penColorAct;
    QAction* penWidthAct;

    QSize screenSize;

    screenshotWindow* pSS;
};

#endif // MAINWINDOW_H
