#ifndef DLGCONTACTFORM_H
#define DLGCONTACTFORM_H

#include <QDialog>

namespace Ui {class DLGContactForm;}

class DLGContactForm : public QDialog
{
    Q_OBJECT

public:
    explicit DLGContactForm(QWidget *parent = nullptr);
    ~DLGContactForm();

private:
    Ui::DLGContactForm *ui;
};

#endif // DLGCONTACTFORM_H

