#include <QtGui>
#include <QPainterPath>
#include "drawarea.h"
#include "mainwindow.h"

DrawArea::DrawArea(QWidget *parent):
    QWidget(parent),
    bgColor(Qt::lightGray),
    xSize(0),
    ySize(0),
    xmin(-8.),
    xmax(8.),
    ymin(-6.),
    ymax(6.),
    xCoeff(50.),        // == 800./(xmax-xmin)
    yCoeff(50.),        // == 600./(ymax-ymin)
    numPoints(0)
{
    setAttribute(Qt::WA_StaticContents); // for optimizing painting events
    drawArea = this;
}

void DrawArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.fillRect(0, 0, width(), height(), bgColor);

    painter.setRenderHint(QPainter::Antialiasing);
    drawPoints(&painter);

    event->accept();
}

void DrawArea::resizeEvent(QResizeEvent* event) {
    int w = width();
    int h = height();
    if (
        w != 0 && h != 0 && (
            xSize == 0 || ySize == 0 ||
            xSize != width() || ySize != height()
            )
        ) {
        xSize = w;
        ySize = h;
        initializeMap();
        mainWindow->showCoordRange(
            xmin, xmax, ymin, ymax
            );
        event->accept();
    }
}
