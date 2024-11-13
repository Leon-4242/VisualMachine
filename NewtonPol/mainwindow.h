#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawarea.h"

extern DrawArea* drawArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_clearButton_clicked();

    void on_drawButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
