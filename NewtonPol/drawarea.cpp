#include <QPainter>
#include <QPainterPath>
#include "drawarea.h"
#include "newton.h"

DrawArea::DrawArea(QWidget *parent):
    QWidget(parent),
    xmin(-8.),
    xmax(8.),
    ymin(-6.),
    ymax(6.),
    nodes(),
    mouseButtons(),
    drawPolynom(false),
    newtonPolCoeff(),
    dragNode(-1)
{
    setMouseTracking(true);
}

double DrawArea::f(double t) const {
    // return sin(8*x) * 4./(1 + 0.1*x*x);
    size_t n = newtonPolNodes.size() - 1;
    return newtonPolValue(
        newtonPolNodes, newtonPolCoeff, n, t
    );
}

void DrawArea::paintEvent(QPaintEvent* /* e */) {
    QPainter painter(this);
    painter.fillRect(
        QRect(0, 0, width(), height()),
        QBrush(Qt::lightGray)
    );
    drawGrid(&painter);
    drawNodes(&painter);
    if (drawPolynom)
        drawFunction(&painter);
}

void DrawArea::drawGrid(QPainter *painter) {
    QPen grayPen(Qt::gray, 1);
    QPen blackPen(Qt::black, 2);

    // Draw grid
    double x = round(xmin);
    painter->setPen(grayPen);
    while (x <= xmax) {
        painter->drawLine(
            mapToPixels(R2Point(x, ymin)),
            mapToPixels(R2Point(x, ymax))
        );
        x += 1.;
    }
    double y = round(ymin);
    while (y <= ymax) {
        painter->drawLine(
            mapToPixels(R2Point(xmin, y)),
            mapToPixels(R2Point(xmax, y))
        );
        y += 1.;
    }

    // Draw coordinate axes
    painter->setPen(blackPen);
    painter->drawLine(  // X-axis
        mapToPixels(R2Point(xmin, 0.)),
        mapToPixels(R2Point(xmax, 0.))
    );
    painter->drawLine(  // Y-axis
        mapToPixels(R2Point(0., ymin)),
        mapToPixels(R2Point(0., ymax))
    );
}

void DrawArea::resizeEvent(QResizeEvent* /* event */) {
    int w = width();
    int h = height();
    if (w > 0 && h > 0) {
        double aspect = double(h)/double(w);
        double dy = (xmax - xmin)*aspect;
        ymin = (-dy/2.);
        ymax = dy/2.;
    }
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event) {
    QPointF q = event->pos();
    R2Point p = mapFromPixels(q);
    if (dragNode >= 0) {
        dragNode = (-1);
        setCursor(Qt::ArrowCursor);
    } else {
        // Add a new node
        nodes.push_back(p);
        mouseButtons.push_back(event->button());
        update();
    }
}

void DrawArea::drawNodes(QPainter* painter) {
    R2Vector dx(0.2, 0.);
    R2Vector dy(0., 0.2);
    QPen redPen(Qt::red, 2);
    QPen bluePen(Qt::blue, 2);
    QPen greenPen(Qt::darkGreen, 2);

    for (size_t i = 0; i < nodes.size(); ++i) {
        if (mouseButtons[i] == Qt::RightButton) {
            painter->setPen(greenPen);
        } else if (mouseButtons[i] == Qt::MiddleButton) {
            painter->setPen(bluePen);
        } else {
            painter->setPen(redPen);
        }
        R2Point p = nodes[i];
        painter->drawLine(
            mapToPixels(p - dx),
            mapToPixels(p + dx)
        );
        painter->drawLine(
            mapToPixels(p - dy),
            mapToPixels(p + dy)
        );
    }
}

void DrawArea::onClear() {
    nodes.clear();
    mouseButtons.clear();
    drawPolynom = false;
    dragNode = (-1);
    update();
}

void DrawArea::drawFunction(QPainter* painter) {
    // Set line smoothing
    painter->setRenderHints(QPainter::Antialiasing);

    QPen bluePen(Qt::blue, 2);
    painter->setPen(bluePen);

    QPainterPath path;
    double dx = 0.01;
    R2Point p(xmin, f(xmin));
    path.moveTo(mapToPixels(p));
    while (p.x <= xmax - dx) {
        p.x += dx;
        p.y = f(p.x);
        path.lineTo(mapToPixels(p));
    }
    painter->drawPath(path);
}

void DrawArea::onDraw() {
    if (nodes.size() == 0)
        return;
    computeInterpol();
    drawPolynom = true;
    update();
}

void DrawArea::computeInterpol() {
    newtonPolNodes.resize(nodes.size());
    std::vector<double> y(nodes.size());
    for (size_t i = 0; i < nodes.size(); ++i) {
        newtonPolNodes[i] = nodes[i].x;
        y[i] = nodes[i].y;
    }
    computeNewtonPol(newtonPolNodes, y, newtonPolCoeff);
}

int DrawArea::searchNode(const R2Point& p) const {
    const double SEARCH_DIST = 0.1;
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (p.distance(nodes[i]) <= SEARCH_DIST)
            return int(i);
    }
    return (-1);
}

void DrawArea::mousePressEvent(QMouseEvent *event) {
    QPointF p = event->pos();
    R2Point t = mapFromPixels(p);
    int idx = searchNode(t);
    if (idx < 0)
        return;
    dragNode = idx;
    setCursor(Qt::ClosedHandCursor);
}

void DrawArea::mouseMoveEvent(QMouseEvent *event) {
    QPointF p = event->pos();
    R2Point t = mapFromPixels(p);
    if (dragNode >= 0) {
        Q_ASSERT(dragNode < int(nodes.size()));
        nodes[dragNode] = t;
        if (drawPolynom) {
            computeInterpol();
        }
        update();
    } else {
        int idx = searchNode(t);
        if (idx < 0) {
            setCursor(Qt::ArrowCursor);
        } else {
            setCursor(Qt::OpenHandCursor);
        }
    }
}

