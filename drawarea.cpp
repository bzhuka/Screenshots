#include "drawarea.h"
#include "mainwindow.h"

DrawArea::DrawArea(MainWindow *parent, QPixmap pixmap) : pParent(parent)
{
    setAttribute(Qt::WA_StaticContents);

    mImage = pixmap.toImage();
    mOriginalImage = mImage;

    bDrawing = false;
    bModified = false;

    mPen = QPen();
    mPen.setWidth(1);
    mPen.setColor(Qt::black);
    mPen.setCapStyle(Qt::RoundCap);
    mPen.setStyle(Qt::SolidLine);
    mPen.setJoinStyle(Qt::RoundJoin);

    update();
}

DrawArea::~DrawArea() {
    pParent = nullptr;
}

void DrawArea::setPenColor(QColor color) {
    mPen.setColor(color);
}

void DrawArea::setPenWidth(int width) {
    mPen.setWidth(width);
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        mLastPoint = event->pos();
        bDrawing = true;
    }
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    if (bDrawing)
        drawLineTo(event->pos());
}

void DrawArea::mouseReleaseEvent(QMouseEvent *event) {
    if (bDrawing && (event->button() & Qt::LeftButton)) {
        drawLineTo((event->pos()));
        bDrawing = false;
    }
}

void DrawArea::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, mImage, dirtyRect);
}

void DrawArea::drawLineTo(QPoint endPoint) {
    QPainter painter(&mImage);
    painter.setPen(mPen);
    painter.drawLine(mLastPoint, endPoint);
    bModified = true;

    int radius = (mPen.width() / 2) + 2;
    update();
    //update(QRect(mLastPoint, endPoint).normalized().adjusted(-radius, -radius, +radius, +radius));
    mLastPoint = endPoint;
}
