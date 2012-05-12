/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri May 11 19:51:02 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "imagewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_Save;
    QAction *actionAbout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab_render;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QSpinBox *preview_spinBox;
    QCheckBox *save_checkBox;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QSpinBox *sample_spinBox;
    QFrame *line;
    QLabel *label_3;
    QFormLayout *formLayout;
    QLabel *label_4;
    QSpinBox *x_spinBox;
    QLabel *label_5;
    QSpinBox *y_spinBox;
    QFrame *line_3;
    QPushButton *startButton;
    QSpacerItem *verticalSpacer;
    QWidget *tab_camera;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *dof_groupBox;
    QFormLayout *formLayout_2;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *radius_doubleSpinBox;
    QDoubleSpinBox *distance_doubleSpinBox;
    QSpacerItem *verticalSpacer_2;
    ImageWidget *graphicsView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu_Help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(603, 467);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QString::fromUtf8("action_Open"));
        action_Save = new QAction(MainWindow);
        action_Save->setObjectName(QString::fromUtf8("action_Save"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tab_render = new QWidget();
        tab_render->setObjectName(QString::fromUtf8("tab_render"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tab_render->sizePolicy().hasHeightForWidth());
        tab_render->setSizePolicy(sizePolicy1);
        verticalLayout_3 = new QVBoxLayout(tab_render);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(tab_render);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        preview_spinBox = new QSpinBox(tab_render);
        preview_spinBox->setObjectName(QString::fromUtf8("preview_spinBox"));
        preview_spinBox->setValue(1);

        verticalLayout->addWidget(preview_spinBox);

        save_checkBox = new QCheckBox(tab_render);
        save_checkBox->setObjectName(QString::fromUtf8("save_checkBox"));
        save_checkBox->setChecked(true);
        save_checkBox->setTristate(false);

        verticalLayout->addWidget(save_checkBox);


        verticalLayout_3->addLayout(verticalLayout);

        line_2 = new QFrame(tab_render);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(tab_render);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        sample_spinBox = new QSpinBox(tab_render);
        sample_spinBox->setObjectName(QString::fromUtf8("sample_spinBox"));
        sample_spinBox->setValue(10);

        verticalLayout_2->addWidget(sample_spinBox);


        verticalLayout_3->addLayout(verticalLayout_2);

        line = new QFrame(tab_render);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line);

        label_3 = new QLabel(tab_render);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_4 = new QLabel(tab_render);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_4);

        x_spinBox = new QSpinBox(tab_render);
        x_spinBox->setObjectName(QString::fromUtf8("x_spinBox"));
        x_spinBox->setMaximum(9999);
        x_spinBox->setValue(500);

        formLayout->setWidget(0, QFormLayout::FieldRole, x_spinBox);

        label_5 = new QLabel(tab_render);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_5);

        y_spinBox = new QSpinBox(tab_render);
        y_spinBox->setObjectName(QString::fromUtf8("y_spinBox"));
        y_spinBox->setMaximum(9999);
        y_spinBox->setValue(500);

        formLayout->setWidget(1, QFormLayout::FieldRole, y_spinBox);


        verticalLayout_3->addLayout(formLayout);

        line_3 = new QFrame(tab_render);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_3->addWidget(line_3);

        startButton = new QPushButton(tab_render);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy2);
        startButton->setLayoutDirection(Qt::LeftToRight);

        verticalLayout_3->addWidget(startButton);

        verticalSpacer = new QSpacerItem(20, 53, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget->addTab(tab_render, QString());
        tab_camera = new QWidget();
        tab_camera->setObjectName(QString::fromUtf8("tab_camera"));
        verticalLayout_4 = new QVBoxLayout(tab_camera);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        dof_groupBox = new QGroupBox(tab_camera);
        dof_groupBox->setObjectName(QString::fromUtf8("dof_groupBox"));
        dof_groupBox->setCheckable(true);
        dof_groupBox->setChecked(false);
        formLayout_2 = new QFormLayout(dof_groupBox);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_6 = new QLabel(dof_groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_6);

        label_7 = new QLabel(dof_groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_7);

        radius_doubleSpinBox = new QDoubleSpinBox(dof_groupBox);
        radius_doubleSpinBox->setObjectName(QString::fromUtf8("radius_doubleSpinBox"));
        radius_doubleSpinBox->setValue(0.05);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, radius_doubleSpinBox);

        distance_doubleSpinBox = new QDoubleSpinBox(dof_groupBox);
        distance_doubleSpinBox->setObjectName(QString::fromUtf8("distance_doubleSpinBox"));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, distance_doubleSpinBox);


        verticalLayout_4->addWidget(dof_groupBox);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_2);

        tabWidget->addTab(tab_camera, QString());
        splitter->addWidget(tabWidget);
        graphicsView = new ImageWidget(splitter);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy3);
        graphicsView->setSizeIncrement(QSize(0, 0));
        graphicsView->setBaseSize(QSize(0, 0));
        splitter->addWidget(graphicsView);

        horizontalLayout->addWidget(splitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 603, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menuFile->addAction(action_Open);
        menuFile->addAction(action_Save);
        menu_Help->addAction(actionAbout);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "PhotonFail", 0, QApplication::UnicodeUTF8));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", 0, QApplication::UnicodeUTF8));
        action_Open->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_Save->setText(QApplication::translate("MainWindow", "&Save", 0, QApplication::UnicodeUTF8));
        action_Save->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Preview Update Rate", 0, QApplication::UnicodeUTF8));
        save_checkBox->setText(QApplication::translate("MainWindow", "Save previews", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Samples", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Resolution", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "X", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Y", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_render), QApplication::translate("MainWindow", "Render", 0, QApplication::UnicodeUTF8));
        dof_groupBox->setTitle(QApplication::translate("MainWindow", "DoF", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Distance:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Lens Radius:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_camera), QApplication::translate("MainWindow", "Camera", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
