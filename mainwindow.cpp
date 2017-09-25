#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    imageLabel = new QLabel();
    imageLabel->setText("");

    //FIRST ITEM
    //Formatting the image, and making sure the image scales
    imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel->setAlignment(Qt::AlignCenter);
    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    imageLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);
    mainLayout->addWidget(imageLabel);

    //SECOND ITEM
    //Buttons
    buttonsLayout = new QHBoxLayout;

    ssButton = new QPushButton();
    ssButton->setText("Screenshot");
    buttonsLayout->addWidget(ssButton);

    saveButton = new QPushButton();
    saveButton->setText("Save");
    buttonsLayout->addWidget(saveButton);

    buttonsLayout->addStretch();
    mainLayout->addLayout(buttonsLayout);

    central = new QWidget;
    central->setLayout(mainLayout);
    setCentralWidget(central);

    setup();
}

void MainWindow::resizeEvent(QResizeEvent *) {
    QSize scaledSize = mBasePixmap.size();
    scaledSize.scale(imageLabel->size(), Qt::KeepAspectRatio);
    if (!imageLabel->pixmap() || scaledSize != imageLabel->pixmap()->size())
        updateScreenShotLabel();
}

void MainWindow::setup() {
//    //Setting up objects
//    Screenshot* sshot = new Screenshot();
//    pSS = sshot;
    pSS = new screenshotWindow(this);

    //Connecting everything
    connect(ssButton, SIGNAL(released()), this, SLOT (handleSSRelease()));
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
    imageLabel->setPixmap(mBasePixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void MainWindow::updateScreenShotLabel() {
    imageLabel->setPixmap(mBasePixmap.scaled(imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

MainWindow::~MainWindow()
{
    delete imageLabel;
    delete mainLayout;
    delete ssButton;
    delete saveButton;
    delete central;
    delete ui;
}
