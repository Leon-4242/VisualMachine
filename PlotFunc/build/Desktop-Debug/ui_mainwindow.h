/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>
#include <drawarea.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    DrawArea *drawArea;
    QGridLayout *vertLayout;
    QLineEdit *ymin;
    QLabel *xmaxLabel;
    QLabel *xminLabel;
    QPushButton *clearButton;
    QLineEdit *xmax;
    QLabel *yminLabel;
    QPushButton *closeButton;
    QLabel *ymaxLabel;
    QPushButton *drawButton;
    QLineEdit *xmin;
    QLabel *ymax;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1097, 654);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        drawArea = new DrawArea(centralWidget);
        drawArea->setObjectName(QString::fromUtf8("drawArea"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(drawArea->sizePolicy().hasHeightForWidth());
        drawArea->setSizePolicy(sizePolicy);
        drawArea->setMinimumSize(QSize(640, 480));
        drawArea->setBaseSize(QSize(800, 600));

        gridLayout->addWidget(drawArea, 0, 0, 1, 1);

        vertLayout = new QGridLayout();
        vertLayout->setSpacing(6);
        vertLayout->setObjectName(QString::fromUtf8("vertLayout"));
        vertLayout->setSizeConstraint(QLayout::SetMaximumSize);
        ymin = new QLineEdit(centralWidget);
        ymin->setObjectName(QString::fromUtf8("ymin"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ymin->sizePolicy().hasHeightForWidth());
        ymin->setSizePolicy(sizePolicy1);
        ymin->setMinimumSize(QSize(80, 0));
        ymin->setMaximumSize(QSize(100, 16777215));

        vertLayout->addWidget(ymin, 1, 1, 1, 1);

        xmaxLabel = new QLabel(centralWidget);
        xmaxLabel->setObjectName(QString::fromUtf8("xmaxLabel"));

        vertLayout->addWidget(xmaxLabel, 0, 2, 1, 1);

        xminLabel = new QLabel(centralWidget);
        xminLabel->setObjectName(QString::fromUtf8("xminLabel"));

        vertLayout->addWidget(xminLabel, 0, 0, 1, 1);

        clearButton = new QPushButton(centralWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        vertLayout->addWidget(clearButton, 2, 1, 1, 1);

        xmax = new QLineEdit(centralWidget);
        xmax->setObjectName(QString::fromUtf8("xmax"));
        sizePolicy1.setHeightForWidth(xmax->sizePolicy().hasHeightForWidth());
        xmax->setSizePolicy(sizePolicy1);
        xmax->setMinimumSize(QSize(80, 0));
        xmax->setMaximumSize(QSize(100, 16777215));

        vertLayout->addWidget(xmax, 0, 3, 1, 1);

        yminLabel = new QLabel(centralWidget);
        yminLabel->setObjectName(QString::fromUtf8("yminLabel"));

        vertLayout->addWidget(yminLabel, 1, 0, 1, 1);

        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        vertLayout->addWidget(closeButton, 3, 3, 1, 1);

        ymaxLabel = new QLabel(centralWidget);
        ymaxLabel->setObjectName(QString::fromUtf8("ymaxLabel"));

        vertLayout->addWidget(ymaxLabel, 1, 2, 1, 1);

        drawButton = new QPushButton(centralWidget);
        drawButton->setObjectName(QString::fromUtf8("drawButton"));

        vertLayout->addWidget(drawButton, 2, 3, 1, 1);

        xmin = new QLineEdit(centralWidget);
        xmin->setObjectName(QString::fromUtf8("xmin"));
        sizePolicy1.setHeightForWidth(xmin->sizePolicy().hasHeightForWidth());
        xmin->setSizePolicy(sizePolicy1);
        xmin->setMinimumSize(QSize(80, 0));
        xmin->setMaximumSize(QSize(100, 16777215));

        vertLayout->addWidget(xmin, 0, 1, 1, 1);

        ymax = new QLabel(centralWidget);
        ymax->setObjectName(QString::fromUtf8("ymax"));
        ymax->setMinimumSize(QSize(80, 0));
        ymax->setMaximumSize(QSize(100, 16777215));
        ymax->setFrameShape(QFrame::Panel);

        vertLayout->addWidget(ymax, 1, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        vertLayout->addItem(verticalSpacer, 4, 3, 1, 1);


        gridLayout->addLayout(vertLayout, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Plot Function", nullptr));
        xmaxLabel->setText(QCoreApplication::translate("MainWindow", "xmax:", nullptr));
        xminLabel->setText(QCoreApplication::translate("MainWindow", "xmin:", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        yminLabel->setText(QCoreApplication::translate("MainWindow", "ymin:", nullptr));
        closeButton->setText(QCoreApplication::translate("MainWindow", "Close", nullptr));
        ymaxLabel->setText(QCoreApplication::translate("MainWindow", "ymax:", nullptr));
        drawButton->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        ymax->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
