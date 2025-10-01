/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTableWidget *table;
    QWidget *panel;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label1;
    QLabel *lblFloor;
    QLabel *label2;
    QLabel *lblHP;
    QLabel *label3;
    QLabel *lblATK;
    QLabel *label4;
    QLabel *lblRolls;
    QFrame *line;
    QPushButton *btnRoll;
    QLabel *label5;
    QLabel *lblD1;
    QComboBox *dir1;
    QLabel *label6;
    QLabel *lblD2;
    QComboBox *dir2;
    QPushButton *btnMove;
    QFrame *line2;
    QLabel *label7;
    QLineEdit *cheatLine;
    QFrame *line3;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QDockWidget *dockLog;
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QTextEdit *logText;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(980, 640);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName("horizontalLayout");
        table = new QTableWidget(centralwidget);
        table->setObjectName("table");

        horizontalLayout->addWidget(table);

        panel = new QWidget(centralwidget);
        panel->setObjectName("panel");
        verticalLayout = new QVBoxLayout(panel);
        verticalLayout->setObjectName("verticalLayout");
        label = new QLabel(panel);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        label1 = new QLabel(panel);
        label1->setObjectName("label1");

        verticalLayout->addWidget(label1);

        lblFloor = new QLabel(panel);
        lblFloor->setObjectName("lblFloor");

        verticalLayout->addWidget(lblFloor);

        label2 = new QLabel(panel);
        label2->setObjectName("label2");

        verticalLayout->addWidget(label2);

        lblHP = new QLabel(panel);
        lblHP->setObjectName("lblHP");

        verticalLayout->addWidget(lblHP);

        label3 = new QLabel(panel);
        label3->setObjectName("label3");

        verticalLayout->addWidget(label3);

        lblATK = new QLabel(panel);
        lblATK->setObjectName("lblATK");

        verticalLayout->addWidget(lblATK);

        label4 = new QLabel(panel);
        label4->setObjectName("label4");

        verticalLayout->addWidget(label4);

        lblRolls = new QLabel(panel);
        lblRolls->setObjectName("lblRolls");

        verticalLayout->addWidget(lblRolls);

        line = new QFrame(panel);
        line->setObjectName("line");

        verticalLayout->addWidget(line);

        btnRoll = new QPushButton(panel);
        btnRoll->setObjectName("btnRoll");

        verticalLayout->addWidget(btnRoll);

        label5 = new QLabel(panel);
        label5->setObjectName("label5");

        verticalLayout->addWidget(label5);

        lblD1 = new QLabel(panel);
        lblD1->setObjectName("lblD1");

        verticalLayout->addWidget(lblD1);

        dir1 = new QComboBox(panel);
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->setObjectName("dir1");

        verticalLayout->addWidget(dir1);

        label6 = new QLabel(panel);
        label6->setObjectName("label6");

        verticalLayout->addWidget(label6);

        lblD2 = new QLabel(panel);
        lblD2->setObjectName("lblD2");

        verticalLayout->addWidget(lblD2);

        dir2 = new QComboBox(panel);
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->setObjectName("dir2");

        verticalLayout->addWidget(dir2);

        btnMove = new QPushButton(panel);
        btnMove->setObjectName("btnMove");

        verticalLayout->addWidget(btnMove);

        line2 = new QFrame(panel);
        line2->setObjectName("line2");

        verticalLayout->addWidget(line2);

        label7 = new QLabel(panel);
        label7->setObjectName("label7");

        verticalLayout->addWidget(label7);

        cheatLine = new QLineEdit(panel);
        cheatLine->setObjectName("cheatLine");

        verticalLayout->addWidget(cheatLine);

        line3 = new QFrame(panel);
        line3->setObjectName("line3");

        verticalLayout->addWidget(line3);

        btnSave = new QPushButton(panel);
        btnSave->setObjectName("btnSave");

        verticalLayout->addWidget(btnSave);

        btnLoad = new QPushButton(panel);
        btnLoad->setObjectName("btnLoad");

        verticalLayout->addWidget(btnLoad);


        horizontalLayout->addWidget(panel);

        MainWindow->setCentralWidget(centralwidget);
        dockLog = new QDockWidget(MainWindow);
        dockLog->setObjectName("dockLog");
        widget = new QWidget();
        widget->setObjectName("widget");
        vboxLayout = new QVBoxLayout(widget);
        vboxLayout->setObjectName("vboxLayout");
        logText = new QTextEdit(widget);
        logText->setObjectName("logText");
        logText->setReadOnly(true);

        vboxLayout->addWidget(logText);

        dockLog->setWidget(widget);
        MainWindow->addDockWidget(Qt::DockWidgetArea::BottomDockWidgetArea, dockLog);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AngelDungeon", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Estad\303\255sticas", nullptr));
        label1->setText(QCoreApplication::translate("MainWindow", "Piso:", nullptr));
        lblFloor->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label2->setText(QCoreApplication::translate("MainWindow", "HP:", nullptr));
        lblHP->setText(QCoreApplication::translate("MainWindow", "3/3", nullptr));
        label3->setText(QCoreApplication::translate("MainWindow", "ATK:", nullptr));
        lblATK->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        label4->setText(QCoreApplication::translate("MainWindow", "Tiradas restantes:", nullptr));
        lblRolls->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        btnRoll->setText(QCoreApplication::translate("MainWindow", "Tirar dados", nullptr));
        label5->setText(QCoreApplication::translate("MainWindow", "Dado 1", nullptr));
        lblD1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        dir1->setItemText(0, QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        dir1->setItemText(1, QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        dir1->setItemText(2, QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        dir1->setItemText(3, QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));

        label6->setText(QCoreApplication::translate("MainWindow", "Dado 2", nullptr));
        lblD2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        dir2->setItemText(0, QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        dir2->setItemText(1, QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        dir2->setItemText(2, QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        dir2->setItemText(3, QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));

        btnMove->setText(QCoreApplication::translate("MainWindow", "Mover", nullptr));
        label7->setText(QCoreApplication::translate("MainWindow", "Consola (cheats):", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        dockLog->setWindowTitle(QCoreApplication::translate("MainWindow", "Registro", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
