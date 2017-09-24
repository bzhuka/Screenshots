#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->imageLabel->setText("");

    setup();
}

void MainWindow::setup() {
//    //Setting up objects
//    Screenshot* sshot = new Screenshot();
//    pSS = sshot;
    pSS = new screenshotWindow(this);

    //Connecting everything
    connect(ui->ssButton, SIGNAL(released()), this, SLOT (handleSSRelease()));
}

void MainWindow::handleSSRelease() {
    hide();
    QThread::msleep(200);
    QScreen* pScreen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        pScreen = window->screen();

    mBasePixmap = pScreen->grabWindow(0);

    pSS->updatePixmap(mBasePixmap);
    pSS->show();
}

void MainWindow::updatePixmap(QPixmap newPixmap) {
    show();
    mBasePixmap = newPixmap;
    ui->imageLabel->setPixmap(mBasePixmap.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

MainWindow::~MainWindow()
{
    delete pSS;
    delete ui;
}
