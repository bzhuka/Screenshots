#include "screenshot.h"

Screenshot::Screenshot()
{
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::Widget | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setParent(0); // Create TopLevel-Widget
    setStyleSheet("background-color: rgba(255, 255, 255, 200);");
    resize( QApplication::desktop()->size() );

}

void Screenshot::takeScreenshot() {
    show();
    QScreen* pScreen = QGuiApplication::primaryScreen();
    if (const QWindow *window = windowHandle())
        pScreen = window->screen();

    mOriginalPixmap = pScreen->grabWindow(0);
}

QPixmap Screenshot::getPixmap() {
    return mOriginalPixmap;
}
