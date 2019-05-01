#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class SecDialog;
}

class DLGContactForm : public QDialog
{
    Q_OBJECT

public:
    explicit DLGContactForm(QWidget *parent = nullptr);
    ~DLGContactForm();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
