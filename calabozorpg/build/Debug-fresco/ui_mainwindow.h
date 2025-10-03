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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *hLayout;
    QTableWidget *table;
    QVBoxLayout *vRight;
    QGridLayout *gridStats;
    QLabel *labelFloor;
    QLabel *lblFloor;
    QLabel *labelHP;
    QLabel *lblHP;
    QLabel *labelATK;
    QLabel *lblATK;
    QLabel *labelRolls;
    QLabel *lblRolls;
    QLabel *labelD1;
    QLabel *lblD1;
    QLabel *labelD2;
    QLabel *lblD2;
    QHBoxLayout *hDirs;
    QComboBox *dir1;
    QComboBox *dir2;
    QHBoxLayout *hButtons;
    QPushButton *btnRoll;
    QPushButton *btnMove;
    QHBoxLayout *hSaveLoad;
    QPushButton *btnSave;
    QPushButton *btnLoad;
    QLineEdit *cheatLine;
    QTextEdit *logText;
    QSpacerItem *vspacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        hLayout = new QHBoxLayout(centralwidget);
        hLayout->setObjectName("hLayout");
        table = new QTableWidget(centralwidget);
        table->setObjectName("table");

        hLayout->addWidget(table);

        vRight = new QVBoxLayout();
        vRight->setObjectName("vRight");
        gridStats = new QGridLayout();
        gridStats->setObjectName("gridStats");
        labelFloor = new QLabel(centralwidget);
        labelFloor->setObjectName("labelFloor");

        gridStats->addWidget(labelFloor, 0, 0, 1, 1);

        lblFloor = new QLabel(centralwidget);
        lblFloor->setObjectName("lblFloor");

        gridStats->addWidget(lblFloor, 0, 1, 1, 1);

        labelHP = new QLabel(centralwidget);
        labelHP->setObjectName("labelHP");

        gridStats->addWidget(labelHP, 1, 0, 1, 1);

        lblHP = new QLabel(centralwidget);
        lblHP->setObjectName("lblHP");

        gridStats->addWidget(lblHP, 1, 1, 1, 1);

        labelATK = new QLabel(centralwidget);
        labelATK->setObjectName("labelATK");

        gridStats->addWidget(labelATK, 2, 0, 1, 1);

        lblATK = new QLabel(centralwidget);
        lblATK->setObjectName("lblATK");

        gridStats->addWidget(lblATK, 2, 1, 1, 1);

        labelRolls = new QLabel(centralwidget);
        labelRolls->setObjectName("labelRolls");

        gridStats->addWidget(labelRolls, 3, 0, 1, 1);

        lblRolls = new QLabel(centralwidget);
        lblRolls->setObjectName("lblRolls");

        gridStats->addWidget(lblRolls, 3, 1, 1, 1);

        labelD1 = new QLabel(centralwidget);
        labelD1->setObjectName("labelD1");

        gridStats->addWidget(labelD1, 4, 0, 1, 1);

        lblD1 = new QLabel(centralwidget);
        lblD1->setObjectName("lblD1");

        gridStats->addWidget(lblD1, 4, 1, 1, 1);

        labelD2 = new QLabel(centralwidget);
        labelD2->setObjectName("labelD2");

        gridStats->addWidget(labelD2, 5, 0, 1, 1);

        lblD2 = new QLabel(centralwidget);
        lblD2->setObjectName("lblD2");

        gridStats->addWidget(lblD2, 5, 1, 1, 1);


        vRight->addLayout(gridStats);

        hDirs = new QHBoxLayout();
        hDirs->setObjectName("hDirs");
        dir1 = new QComboBox(centralwidget);
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->addItem(QString());
        dir1->setObjectName("dir1");

        hDirs->addWidget(dir1);

        dir2 = new QComboBox(centralwidget);
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->addItem(QString());
        dir2->setObjectName("dir2");

        hDirs->addWidget(dir2);


        vRight->addLayout(hDirs);

        hButtons = new QHBoxLayout();
        hButtons->setObjectName("hButtons");
        btnRoll = new QPushButton(centralwidget);
        btnRoll->setObjectName("btnRoll");

        hButtons->addWidget(btnRoll);

        btnMove = new QPushButton(centralwidget);
        btnMove->setObjectName("btnMove");

        hButtons->addWidget(btnMove);


        vRight->addLayout(hButtons);

        hSaveLoad = new QHBoxLayout();
        hSaveLoad->setObjectName("hSaveLoad");
        btnSave = new QPushButton(centralwidget);
        btnSave->setObjectName("btnSave");

        hSaveLoad->addWidget(btnSave);

        btnLoad = new QPushButton(centralwidget);
        btnLoad->setObjectName("btnLoad");

        hSaveLoad->addWidget(btnLoad);


        vRight->addLayout(hSaveLoad);

        cheatLine = new QLineEdit(centralwidget);
        cheatLine->setObjectName("cheatLine");

        vRight->addWidget(cheatLine);

        logText = new QTextEdit(centralwidget);
        logText->setObjectName("logText");

        vRight->addWidget(logText);

        vspacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        vRight->addItem(vspacer);


        hLayout->addLayout(vRight);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "AngelDungeon - Base", nullptr));
        labelFloor->setText(QCoreApplication::translate("MainWindow", "Piso:", nullptr));
        lblFloor->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelHP->setText(QCoreApplication::translate("MainWindow", "HP:", nullptr));
        lblHP->setText(QCoreApplication::translate("MainWindow", "3/3", nullptr));
        labelATK->setText(QCoreApplication::translate("MainWindow", "ATK:", nullptr));
        lblATK->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        labelRolls->setText(QCoreApplication::translate("MainWindow", "Tiradas:", nullptr));
        lblRolls->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        labelD1->setText(QCoreApplication::translate("MainWindow", "D1:", nullptr));
        lblD1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        labelD2->setText(QCoreApplication::translate("MainWindow", "D2:", nullptr));
        lblD2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        dir1->setItemText(0, QCoreApplication::translate("MainWindow", "Up", nullptr));
        dir1->setItemText(1, QCoreApplication::translate("MainWindow", "Down", nullptr));
        dir1->setItemText(2, QCoreApplication::translate("MainWindow", "Left", nullptr));
        dir1->setItemText(3, QCoreApplication::translate("MainWindow", "Right", nullptr));

        dir2->setItemText(0, QCoreApplication::translate("MainWindow", "Up", nullptr));
        dir2->setItemText(1, QCoreApplication::translate("MainWindow", "Down", nullptr));
        dir2->setItemText(2, QCoreApplication::translate("MainWindow", "Left", nullptr));
        dir2->setItemText(3, QCoreApplication::translate("MainWindow", "Right", nullptr));

        btnRoll->setText(QCoreApplication::translate("MainWindow", "Tirar Dados", nullptr));
        btnMove->setText(QCoreApplication::translate("MainWindow", "Mover", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        btnLoad->setText(QCoreApplication::translate("MainWindow", "Cargar", nullptr));
        cheatLine->setPlaceholderText(QCoreApplication::translate("MainWindow", "Cheat: reveal", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
