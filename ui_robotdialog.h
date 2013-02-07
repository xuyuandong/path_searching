/********************************************************************************
** Form generated from reading ui file 'robotdialog.ui'
**
** Created: Thu Nov 8 10:56:51 2007
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ROBOTDIALOG_H
#define UI_ROBOTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_RobotDialog
{
public:
    QWidget *widget;
    QVBoxLayout *vboxLayout;
    QLabel *mapView;
    QHBoxLayout *hboxLayout;
    QPushButton *MapButton;
    QPushButton *NextButton;
    QSpacerItem *spacerItem;
    QPushButton *QuitButton;

    void setupUi(QDialog *RobotDialog)
    {
    if (RobotDialog->objectName().isEmpty())
        RobotDialog->setObjectName(QString::fromUtf8("RobotDialog"));
    RobotDialog->setWindowModality(Qt::NonModal);
    RobotDialog->setEnabled(true);
    RobotDialog->setFixedSize(699, 409);
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
 //   sizePolicy.setHorizontalStretch(0);
 //   sizePolicy.setVerticalStretch(0);
 //   sizePolicy.setHeightForWidth(RobotDialog->sizePolicy().hasHeightForWidth());
    RobotDialog->setSizePolicy(sizePolicy);
    RobotDialog->setWindowIcon(QIcon(QString::fromUtf8("icon/robot.png")));
    RobotDialog->setSizeGripEnabled(false);
    RobotDialog->setModal(false);
    widget = new QWidget(RobotDialog);
    widget->setObjectName(QString::fromUtf8("widget"));
    widget->setGeometry(QRect(20, 20, 661, 371));
    vboxLayout = new QVBoxLayout(widget);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    mapView = new QLabel(widget);
    mapView->setObjectName(QString::fromUtf8("mapView"));
    mapView->setCursor(QCursor(Qt::CrossCursor));
    mapView->setAcceptDrops(false);
    mapView->setFrameShape(QFrame::StyledPanel);
    mapView->setScaledContents(true);
    mapView->setAlignment(Qt::AlignCenter);

    vboxLayout->addWidget(mapView);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    MapButton = new QPushButton(widget);
    MapButton->setObjectName(QString::fromUtf8("MapButton"));

    hboxLayout->addWidget(MapButton);

    NextButton = new QPushButton(widget);
    NextButton->setObjectName(QString::fromUtf8("NextButton"));

    hboxLayout->addWidget(NextButton);

    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout->addItem(spacerItem);

    QuitButton = new QPushButton(widget);
    QuitButton->setObjectName(QString::fromUtf8("QuitButton"));

    hboxLayout->addWidget(QuitButton);


    vboxLayout->addLayout(hboxLayout);


    retranslateUi(RobotDialog);
    QObject::connect(QuitButton, SIGNAL(clicked()), RobotDialog, SLOT(accept()));

    QMetaObject::connectSlotsByName(RobotDialog);
    } // setupUi

    void retranslateUi(QDialog *RobotDialog)
    {
    RobotDialog->setWindowTitle(QApplication::translate("RobotDialog", "Robot Demo", 0, QApplication::UnicodeUTF8));
    mapView->setText(QString());
    MapButton->setText(QApplication::translate("RobotDialog", "&Map", 0, QApplication::UnicodeUTF8));
    NextButton->setText(QApplication::translate("RobotDialog", "&Next", 0, QApplication::UnicodeUTF8));
    QuitButton->setText(QApplication::translate("RobotDialog", "&Quit", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(RobotDialog);
    } // retranslateUi

};

namespace Ui {
    class RobotDialog: public Ui_RobotDialog {};
} // namespace Ui

#endif // UI_ROBOTDIALOG_H
