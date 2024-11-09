#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow* mainWindow = 0;
DrawArea* drawArea = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setlocale(LC_ALL, "C");
    mainWindow = this;
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearButton_clicked()
{
    drawArea->clear();
}

void MainWindow::on_closeButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_drawButton_clicked()
{
    // Here you can add any code that
    // changes the drawing model (for instance, after
    // adding a number of points by mouse clicks).
    drawArea->onDraw();
}
