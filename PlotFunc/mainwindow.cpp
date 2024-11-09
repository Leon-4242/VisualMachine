#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale.h>

// Global variables
MainWindow* mainWindow = 0;
DrawArea* drawArea = 0;

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setlocale(LC_ALL, "C");
    mainWindow = this;
    ui->setupUi(this);

    showCoordRange(
        drawArea->getXMin(), drawArea->getXMax(),
        drawArea->getYMin(), drawArea->getYMax()
    );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_xmin_editingFinished()
{

}

void MainWindow::on_xmax_editingFinished()
{

}

void MainWindow::on_ymin_editingFinished()
{

}

void MainWindow::on_clearButton_clicked()
{
    drawArea->clear();
}

void MainWindow::on_drawButton_clicked()
{
    setCoordinates();
    // Here you can add any code that
    // changes the drawing model (for instance, after
    // adding a number of points by mouse clicks).
    drawArea->onDraw();
}

void MainWindow::on_closeButton_clicked()
{
    QApplication::quit();
}

void MainWindow::setCoordinates() {
    double xmin = ui->xmin->text().toDouble();
    double xmax = ui->xmax->text().toDouble();
    double ymin = ui->ymin->text().toDouble();
    double ymax = ui->ymax->text().toDouble();
    if (xmax <= xmin || ymax <= ymin)
        return;

    // drawArea->setCoordinates(xmin, xmax, ymin);
    // We try to save the relative position of center
    double yCenter = (0. - ymin)/(ymax - ymin);
    double aspect = (double) drawArea->height() / (double) drawArea->width();
    double dx = xmax - xmin;
    double dy = dx*aspect;
    ymin = 0. - dy*yCenter;
    ymax = ymin + dy;

    QString txt;
    // txt.sprintf("%.1f", ymin);
    txt = QString::number(ymin, 'f', 1);
    ui->ymin->setText(txt);

    // txt.sprintf("%.1f", ymax);
    txt = QString::number(ymax, 'f', 1);
    ui->ymax->setText(txt);

    drawArea->setCoordinates(xmin, xmax, ymin, ymax);
    // drawArea->update();
}

void MainWindow::showCoordRange(
    double xmin, double xmax,
    double ymin, double ymax
) {
    QString txt;
    // txt.sprintf("%.1f", xmin);
    txt = QString::number(xmin, 'f', 1);
    ui->xmin->setText(txt);

    // txt.sprintf("%.1f", xmax);
    txt = QString::number(xmax, 'f', 1);
    ui->xmax->setText(txt);

    // txt.sprintf("%.1f", ymin);
    txt = QString::number(ymin, 'f', 1);
    ui->ymin->setText(txt);

    // txt.sprintf("%.1f", ymax);
    txt = QString::number(ymax, 'f', 1);
    ui->ymax->setText(txt);
}

