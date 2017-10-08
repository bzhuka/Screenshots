#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QImage>
#include <QPen>
#include <QPixmap>
#include <QPoint>
#include <QRect>

#include <QWidget>

class MainWindow;

class DrawArea : public QWidget
{
    Q_OBJECT
public:
    DrawArea(MainWindow *parent, QPixmap pixmap);
    ~DrawArea();

    void updatePixmap(QPixmap pixmap);
    QPixmap getPixmap();

    QColor getPenColor() {
        return mPen.color();
    }
    void setPenColor(QColor color);
    int getPenWidth() {
        return mPen.width();
    }
    void setPenWidth(int width);

    bool isModified();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    void drawLineTo(QPoint endPoint);
    void resizeImage(QImage* image, QSize newSize);

    MainWindow* pParent;

    QImage mOriginalImage;
    QImage mImage;
    QPen mPen;
    QPoint mLastPoint;

    bool bDrawing;
    bool bModified;
};

#endif // DRAWAREA_H
