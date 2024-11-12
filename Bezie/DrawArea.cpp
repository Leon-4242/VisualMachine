#include <QtGui>
#include <QPainterPath>
#include "DrawArea.h"
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

    drawCoordSystem(&painter);
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
        event->accept();
    }
}

void DrawArea::clear() {
    numPoints = 0;
    update();
}

void DrawArea::onDraw() {
    update();   // Redraw the picture in window
}


void DrawArea::mouseReleaseEvent(QMouseEvent* event) {
    if (numPoints >= MAX_POINTS)
        return;

    pointButtons[numPoints] = event->button();
    Bezie::Point p = mapFromPixels(event->pos());
    points[numPoints] = p;
    ++numPoints;

    event->accept();
    update();
}

void DrawArea::drawPoints(QPainter* painter) {
    QPen bluePen(Qt::blue);
    bluePen.setWidth(2);

    QPen redPen(Qt::red);
    redPen.setWidth(2);

    QPen magentaPen(Qt::magenta);
    magentaPen.setWidth(2);

    QPointF dx(8., 0.);
    QPointF dy(0., 8.);
    for (int i = 0; i < numPoints; ++i) {
        if (pointButtons[i] == Qt::LeftButton)
            painter->setPen(bluePen);
        else if (pointButtons[i] == Qt::RightButton)
            painter->setPen(redPen);
        else // Qt::MiddleButton
            painter->setPen(magentaPen);

        QPointF t = mapToPixels(points[i]);
        painter->drawLine(t-dx, t+dx);
        painter->drawLine(t-dy, t+dy);
    }
}

QPointF DrawArea::mapToPixels(const Bezie::Point &p) const {
    return QPointF(
        (p.X() - xmin)*xCoeff,
        (ymax - p.Y())*yCoeff
        );
}

Bezie::Point DrawArea::mapFromPixels(const QPointF& p) const {
    return Bezie::Point(
        xmin + (p.x()/xCoeff),
        ymax - (p.y()/yCoeff)
        );
}

void DrawArea::initializeMap() {
    int w = width();
    if (w == 0)
        return;

    int h = height();
    if (h == 0)
        return;

    // We try to save the relative position of center
    double yCenter = (0. - ymin)/(ymax - ymin);

    double aspect = double(h)/double(w);
    double dx = xmax - xmin;
    double dy = dx*aspect;
    ymin = 0. - dy*yCenter;
    ymax = ymin + dy;

    xCoeff = double(w)/dx;
    yCoeff = double(h)/dy;
}


void DrawArea::drawCoordSystem(QPainter* qp) {
    int w = width();
    int h = height();
    if (w == 0 || h == 0)
        return;

    QColor lightGray(220, 220, 220);
    QColor gray(128, 128, 128);
    QColor black(0, 0, 0);

    qp->setBrush(QBrush(lightGray));
    qp->drawRect(0, 0, w, h);

    qp->setPen(gray);

    QPointF p0, p1;
    int ix = int(xmin);
    while (ix <= int(xmax)) {
        if (ix == 0) {
            ++ix;
            continue;
        }
        p0 = mapToPixels(Bezie::Point(ix, ymin));
        p1 = mapToPixels(Bezie::Point(ix, ymax));
        qp->drawLine(p0, p1);
        ++ix;
    }

    int iy = int(ymin);
    while (iy <= int(ymax)) {
        if (iy == 0) {
            ++iy;
            continue;
        }
        p0 = mapToPixels(Bezie::Point(xmin, iy));
        p1 = mapToPixels(Bezie::Point(xmax, iy));
        qp->drawLine(p0, p1);
        ++iy;
    }

    qp->setPen(black);
    p0 = mapToPixels(Bezie::Point(xmin, 0.));
    p1 = mapToPixels(Bezie::Point(xmax, 0.));
    qp->drawLine(p0, p1);

    p0 = mapToPixels(Bezie::Point(0., ymin));
    p1 = mapToPixels(Bezie::Point(0., ymax));
    qp->drawLine(p0, p1);
}

void DrawArea::drawBezie(QPainter* painter) {
    QPen greenPen(Qt::darkGreen);
    greenPen.setWidth(2);
    painter->setPen(greenPen);
    painter->setBrush(Qt::NoBrush);

    QPainterPath path;

    double dt = 1e-11;
    double t = 0.;
    Bezie::Point p = Bezie::BezieLine(points, 0, numPoints-1, t);
    path.moveTo(mapToPixels(p));
    while (t < 1.) {
        t += dt;
        p = Bezie::BezieLine(points, 0, numPoints-1, t);
        path.lineTo(mapToPixels(p));
    }
    painter->drawPath(path);
}

