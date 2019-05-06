#ifndef DLGCONTACTFORM_H
#define DLGCONTACTFORM_H

#include <QDialog>
#include <models/dtocustomerinquiry.h>
#include <models/jsoncustomerinquiry.h>
#include <chrono>
#include <QJsonArray>
#include "services/svcjson.h"
#include "gimme.h"

namespace Ui {class DLGContactForm;}

class DLGContactForm : public QDialog
{
    Q_OBJECT

public:
    explicit DLGContactForm(QWidget *parent = nullptr);
    ~DLGContactForm();

private:
    Ui::DLGContactForm *ui;

    void sendCustomerInquiry();
    void showSuccessScreen();
};

#endif // DLGCONTACTFORM_H

