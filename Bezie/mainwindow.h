#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DrawArea;

extern DrawArea* drawArea;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:

    private slots:
        void on_clearButton_clicked();
        void on_drawButton_clicked();
        void on_closeButton_clicked();
    private:
        Ui::MainWindow *ui;
};

extern MainWindow* mainWindow;
#endif // MAINWINDOW_H
