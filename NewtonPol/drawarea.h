#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QMainWindow>
#include <QWidget>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QPainter>
#include <vector>
#include "R2Graph.h"

class DrawArea : public QWidget
{
    Q_OBJECT

    // Mathematical coordinate system
    double xmin;
    double xmax;
    double ymin;
    double ymax;

    std::vector<R2Point> nodes;
    std::vector<int> mouseButtons;

    bool drawPolynom;
    std::vector<double> newtonPolNodes;
    std::vector<double> newtonPolCoeff;

    // For dragging a node
    int dragNode;

public:
    explicit DrawArea(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* e);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

    QPointF mapToPixels(const R2Point& p) const {
        double x = width()*(p.x - xmin)/(xmax - xmin);
        double y = height()*(ymax - p.y)/(ymax - ymin);
        return QPointF(x, y);
    }

    R2Point mapFromPixels(const QPointF& q) const {
        int w = width();
        int h = height();
        double x = 0.;
        if (w > 0) {
            x = xmin + (xmax - xmin)*q.x()/double(w);
        }
        double y = 0.;
        if (h > 0) {
            y = ymax - (ymax - ymin)*q.y()/double(h);
        }
        return R2Point(x, y);
    }

    // Drawing methods
    void drawGrid(QPainter* painter);
    void drawNodes(QPainter* painter);
    void drawFunction(QPainter* painter);

    double f(double x) const;

    int searchNode(const R2Point& p) const;

    void onClear();
    void onDraw();
    void computeInterpol();

signals:

public slots:
};

#endif // DRAWAREA_H
