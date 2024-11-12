#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <locale.h>

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
    drawArea->drawBezie();
    drawArea->onDraw();
}


