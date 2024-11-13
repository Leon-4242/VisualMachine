#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QColor>
#include <vector>
#include "../../HSE_less_MSU/4_task/Bezie.h"

class DrawArea: public QWidget {
    Q_OBJECT
private:
    QColor bgColor; // Background color
    int xSize;      // Window width
    int ySize;      // Window height

    // Mathematical coordinate system in window
    double xmin, xmax, ymin, ymax;
    double xCoeff, yCoeff;

    // Correspondence betwwen pixel and mathematical coord. systems
    QPointF mapToPixels(const Bezie::Point& p) const;
    Bezie::Point mapFromPixels(const QPointF& q) const;

    // The array of points defined by mouse clicks
    std::vector<Bezie::Point> points;
    std::vector<Qt::MouseButton> pointButtons;
    bool DRAW;
    int move;

public:
DrawArea(QWidget *parent = 0);

void initializeMap();

    void drawCoordSystem(QPainter*);
    void drawPoints(QPainter*);
    void clear();
    void onDraw();  // Called when a user presses the "Draw" button
    void drawBezie(QPainter*);
    int searchNode(const Bezie::Point& p) const;

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // DRAWAREA_H
