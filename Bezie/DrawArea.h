#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QColor>
#include "Bezie.h"

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
    QPointF mapToPixels(const R2Point& p) const;
    R2Point mapFromPixels(const QPointF& q) const;

    // The array of points defined by mouse clicks
    R2Point points[MAX_POINTS];
    Qt::MouseButton pointButtons[MAX_POINTS];
    int numPoints;

public:
DrawArea(QWidget *parent = 0);

void initializeMap();

void drawPoints(QPainter*);
void clear();
void onDraw();  // Called when a user presses the "Draw" button

protected:
void paintEvent(QPaintEvent *event);
void mouseReleaseEvent(QMouseEvent* event);
void resizeEvent(QResizeEvent *event);
};

#endif // DRAWAREA_H
