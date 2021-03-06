#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //MAINLAYOUT
    mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignCenter);

    imageLabel = new QLabel();
    imageLabel->setText("");

    //FIRST ITEM
    //Formatting the image, and making sure the image scales
    imageLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    imageLabel->setAlignment(Qt::AlignCenter);
    const QRect screenGeometry = QApplication::desktop()->screenGeometry(this);
    screenSize = QSize(screenGeometry.width(), screenGeometry.height());
    imageLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);
    mainLayout->addWidget(imageLabel);

    mBasePixmap = QPixmap(screenGeometry.width() / 8, screenGeometry.height() / 8);
    //SECOND ITEM
    //Buttons
    buttonsWidget = new QWidget();
    buttonsLayout = new QHBoxLayout(buttonsWidget);

    ssButton = new QPushButton();
    ssButton->setText("Screenshot");
    buttonsLayout->addWidget(ssButton);

    editButton = new QPushButton();
    editButton->setText("Edit");
    buttonsLayout->addWidget(editButton);

    saveButton = new QPushButton();
    saveButton->setText("Save");
    buttonsLayout->addWidget(saveButton);

    buttonsLayout->addStretch();
    mainLayout->addWidget(buttonsWidget);

    drawArea = new DrawArea(this, mBasePixmap);
    drawArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    drawArea->setMinimumSize(screenSize.width() / 8, screenSize.height() / 8);
    mainLayout->addWidget(drawArea);
    drawArea->hide();

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
    connect(editButton, SIGNAL(released()), this, SLOT(handleEditButton()));
    connect(saveButton, SIGNAL(released()), this, SLOT (handleSaveRelease()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("&Pen Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    doneAct = new QAction(tr("&Done Editing..."), this);
    connect(doneAct, SIGNAL(triggered()), this, SLOT(doneEditing()));
}

void MainWindow::handleSaveRelease() {
    const QString format = "png";
    QString initialPath = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation);
    if (initialPath.isEmpty())
        initialPath = QDir::currentPath();
    initialPath += tr("/untitled.") + format;

    QFileDialog fileDialog(this, tr("Save As"), initialPath);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setDirectory(initialPath);
    QStringList mimeTypes;
    foreach (const QByteArray &bf, QImageWriter::supportedMimeTypes())
        mimeTypes.append(QLatin1String(bf));
    fileDialog.setMimeTypeFilters(mimeTypes);
    fileDialog.selectMimeTypeFilter("image/" + format);
    fileDialog.setDefaultSuffix(format);
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    const QString fileName = fileDialog.selectedFiles().first();
    if (!mBasePixmap.save(fileName)) {
        QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(fileName)));
    }
}

void MainWindow::handleEditButton() {
    //resize(mBasePixmap.size());
    //refreshEditingLayout();
    menuBar()->addAction(penColorAct);
    menuBar()->addAction(penWidthAct);
    menuBar()->addAction(doneAct);
    //mainLayout->removeWidget(imageLabel);
    imageLabel->hide();
    buttonsWidget->hide();
    drawArea->updatePixmap(mBasePixmap);
    drawArea->show();

    move(0,0);
    defaultSize = this->size();
    resize(screenSize);
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

void MainWindow::penColor() {
    QColor newColor = QColorDialog::getColor(drawArea->getPenColor());
        if (newColor.isValid())
            drawArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInt(this, tr("Scribble"),
                                        tr("Select pen width:"),
                                        drawArea->getPenWidth(),
                                        1, 50, 1, &ok);
    if (ok)
        drawArea->setPenWidth(newWidth);
}

void MainWindow::doneEditing() {
    menuBar()->clear();
    drawArea->hide();
    imageLabel->show();
    buttonsWidget->show();

    updatePixmap(drawArea->getPixmap());

    resize(defaultSize);
}

MainWindow::~MainWindow()
{
//    if (drawArea)
//        delete drawArea;
//    if (imageLabel)
//        delete imageLabel;
//    if (mainLayout)
//        delete mainLayout;
//    if (ssButton)
//        delete ssButton;
//    if (saveButton)
//        delete saveButton;
//    if (central)
//        delete central;
//    if (ui)
//        delete ui;
}
