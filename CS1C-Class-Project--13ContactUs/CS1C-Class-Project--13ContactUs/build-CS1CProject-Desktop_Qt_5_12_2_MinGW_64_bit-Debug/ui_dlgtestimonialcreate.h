/********************************************************************************
** Form generated from reading UI file 'dlgtestimonialcreate.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLGTESTIMONIALCREATE_H
#define UI_DLGTESTIMONIALCREATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLGTestimonialCreate
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *pgTestimonialForm;
    QGridLayout *gridLayout_2;
    QPushButton *saveBt;
    QDialogButtonBox *dialogBts;
    QPlainTextEdit *bodyTE;
    QLabel *prompt1Lbl;
    QLineEdit *topTE;
    QLabel *prompt0Lbl;
    QWidget *pgSuccess;
    QGridLayout *gridLayout_3;
    QLabel *successLbl;
    QPushButton *successFinishBt;

    void setupUi(QDialog *DLGTestimonialCreate)
    {
        if (DLGTestimonialCreate->objectName().isEmpty())
            DLGTestimonialCreate->setObjectName(QString::fromUtf8("DLGTestimonialCreate"));
        DLGTestimonialCreate->resize(490, 494);
        gridLayout = new QGridLayout(DLGTestimonialCreate);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stackedWidget = new QStackedWidget(DLGTestimonialCreate);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pgTestimonialForm = new QWidget();
        pgTestimonialForm->setObjectName(QString::fromUtf8("pgTestimonialForm"));
        gridLayout_2 = new QGridLayout(pgTestimonialForm);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        saveBt = new QPushButton(pgTestimonialForm);
        saveBt->setObjectName(QString::fromUtf8("saveBt"));

        gridLayout_2->addWidget(saveBt, 4, 0, 1, 1);

        dialogBts = new QDialogButtonBox(pgTestimonialForm);
        dialogBts->setObjectName(QString::fromUtf8("dialogBts"));
        dialogBts->setOrientation(Qt::Horizontal);
        dialogBts->setStandardButtons(QDialogButtonBox::Close);

        gridLayout_2->addWidget(dialogBts, 4, 1, 1, 1);

        bodyTE = new QPlainTextEdit(pgTestimonialForm);
        bodyTE->setObjectName(QString::fromUtf8("bodyTE"));

        gridLayout_2->addWidget(bodyTE, 3, 0, 1, 2);

        prompt1Lbl = new QLabel(pgTestimonialForm);
        prompt1Lbl->setObjectName(QString::fromUtf8("prompt1Lbl"));

        gridLayout_2->addWidget(prompt1Lbl, 2, 0, 1, 2);

        topTE = new QLineEdit(pgTestimonialForm);
        topTE->setObjectName(QString::fromUtf8("topTE"));

        gridLayout_2->addWidget(topTE, 1, 0, 1, 2);

        prompt0Lbl = new QLabel(pgTestimonialForm);
        prompt0Lbl->setObjectName(QString::fromUtf8("prompt0Lbl"));

        gridLayout_2->addWidget(prompt0Lbl, 0, 0, 1, 2);

        stackedWidget->addWidget(pgTestimonialForm);
        pgSuccess = new QWidget();
        pgSuccess->setObjectName(QString::fromUtf8("pgSuccess"));
        gridLayout_3 = new QGridLayout(pgSuccess);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        successLbl = new QLabel(pgSuccess);
        successLbl->setObjectName(QString::fromUtf8("successLbl"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(successLbl->sizePolicy().hasHeightForWidth());
        successLbl->setSizePolicy(sizePolicy);
        successLbl->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(successLbl, 0, 0, 1, 1);

        successFinishBt = new QPushButton(pgSuccess);
        successFinishBt->setObjectName(QString::fromUtf8("successFinishBt"));

        gridLayout_3->addWidget(successFinishBt, 1, 0, 1, 1);

        stackedWidget->addWidget(pgSuccess);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 1);


        retranslateUi(DLGTestimonialCreate);
        QObject::connect(dialogBts, SIGNAL(accepted()), DLGTestimonialCreate, SLOT(accept()));
        QObject::connect(dialogBts, SIGNAL(rejected()), DLGTestimonialCreate, SLOT(reject()));

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(DLGTestimonialCreate);
    } // setupUi

    void retranslateUi(QDialog *DLGTestimonialCreate)
    {
        DLGTestimonialCreate->setWindowTitle(QApplication::translate("DLGTestimonialCreate", "Dialog", nullptr));
        saveBt->setText(QApplication::translate("DLGTestimonialCreate", "PushButton", nullptr));
        prompt1Lbl->setText(QApplication::translate("DLGTestimonialCreate", "TextLabel", nullptr));
        prompt0Lbl->setText(QApplication::translate("DLGTestimonialCreate", "TextLabel", nullptr));
        successLbl->setText(QApplication::translate("DLGTestimonialCreate", "TextLabel", nullptr));
        successFinishBt->setText(QApplication::translate("DLGTestimonialCreate", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLGTestimonialCreate: public Ui_DLGTestimonialCreate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLGTESTIMONIALCREATE_H
