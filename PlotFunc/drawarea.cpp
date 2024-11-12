#include <QtGui>
#include <QPainterPath>
#include "drawarea.h"
#include "mainwindow.h"

double f(double x);

double f(double x) {
    return 4.*sin(2.*x)/(1. + 0.2*x*x);
}

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
    plotFunction(&painter, &f);
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

QPointF DrawArea::mapToPixels(const R2Point &p) const {
    return QPointF(
        (p.x - xmin)*xCoeff,
        (ymax - p.y)*yCoeff
    );
}

R2Point DrawArea::mapFromPixels(const QPointF& p) const {
    return R2Point(
        xmin + (p.x()/xCoeff),
        ymax - (p.y()/yCoeff)
    );
}

void DrawArea::setCoordinates(
    double xMin, double xMax,
    double yMin, double yMax
) {
    if (xMax <= xMin || yMax <= yMin)   // Incorrect parameters
        return;
    xmin = xMin; xmax = xMax;
    ymin = yMin; ymax = yMax;
    initializeMap();
    update();
}

void DrawArea::onDraw() {
    update();   // Redraw the picture in window
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
        p0 = mapToPixels(R2Point(ix, ymin));
        p1 = mapToPixels(R2Point(ix, ymax));
        qp->drawLine(p0, p1);
        ++ix;
    }

    int iy = int(ymin);
    while (iy <= int(ymax)) {
        if (iy == 0) {
            ++iy;
            continue;
        }
        p0 = mapToPixels(R2Point(xmin, iy));
        p1 = mapToPixels(R2Point(xmax, iy));
        qp->drawLine(p0, p1);
        ++iy;
    }

    qp->setPen(black);
    p0 = mapToPixels(R2Point(xmin, 0.));
    p1 = mapToPixels(R2Point(xmax, 0.));
    qp->drawLine(p0, p1);

    p0 = mapToPixels(R2Point(0., ymin));
    p1 = mapToPixels(R2Point(0., ymax));
    qp->drawLine(p0, p1);
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event) {
    if (numPoints >= MAX_POINTS)
        return;

    pointButtons[numPoints] = event->button();
    R2Point p = mapFromPixels(event->pos());
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

void DrawArea::plotFunction(
    QPainter* painter, double (*f)(double)
) {
    QPen greenPen(Qt::darkGreen);
    greenPen.setWidth(2);
    painter->setPen(greenPen);
    painter->setBrush(Qt::NoBrush);

    QPainterPath path;

    // double dx = 0.01;
    // Compute dx that corresponds to 1 pixel
    R2Point h0, h1;
    h0 = mapFromPixels(QPointF(0., 0.));
    h1 = mapFromPixels(QPointF(1., 0.));
    double dx = h1.x - h0.x;

    R2Point p(xmin, (*f)(xmin));
    path.moveTo(mapToPixels(p));
    while (p.x < xmax) {
        p.x += dx;
        p.y = (*f)(p.x);
        path.lineTo(mapToPixels(p));
    }
    painter->drawPath(path);
}

void DrawArea::clear() {
    numPoints = 0;
    update();
}
