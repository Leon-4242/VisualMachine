#include "mainwindow.h"
#include "ui_mainwindow.h"

DrawArea* drawArea = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawArea = ui->drawArea;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clearButton_clicked()
{
    drawArea->onClear();
}

void MainWindow::on_drawButton_clicked()
{
    drawArea->onDraw();
}
