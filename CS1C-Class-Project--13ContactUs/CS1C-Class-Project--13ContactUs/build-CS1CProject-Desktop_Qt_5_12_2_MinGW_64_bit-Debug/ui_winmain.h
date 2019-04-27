/********************************************************************************
** Form generated from reading UI file 'winmain.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINMAIN_H
#define UI_WINMAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WINMain
{
public:
    QWidget *centralWidget;
    QPushButton *contact_us;
    QPushButton *TEMPBt;

    void setupUi(QMainWindow *WINMain)
    {
        if (WINMain->objectName().isEmpty())
            WINMain->setObjectName(QString::fromUtf8("WINMain"));
        WINMain->resize(800, 480);
        centralWidget = new QWidget(WINMain);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        contact_us = new QPushButton(centralWidget);
        contact_us->setObjectName(QString::fromUtf8("contact_us"));
        contact_us->setGeometry(QRect(310, 130, 191, 81));
        TEMPBt = new QPushButton(centralWidget);
        TEMPBt->setObjectName(QString::fromUtf8("TEMPBt"));
        TEMPBt->setGeometry(QRect(250, 250, 301, 32));
        WINMain->setCentralWidget(centralWidget);

        retranslateUi(WINMain);
        QObject::connect(contact_us, SIGNAL(clicked()), contact_us, SLOT(click()));

        QMetaObject::connectSlotsByName(WINMain);
    } // setupUi

    void retranslateUi(QMainWindow *WINMain)
    {
        WINMain->setWindowTitle(QApplication::translate("WINMain", "WINMain", nullptr));
        contact_us->setText(QApplication::translate("WINMain", "Contact Us", nullptr));
        TEMPBt->setText(QApplication::translate("WINMain", "Leave Feedback", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WINMain: public Ui_WINMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINMAIN_H
