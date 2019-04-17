#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgtestimonialcreate.h"

#include <QDialog>
#include <QMainWindow>
#include "secdialog.h"

namespace Ui {
class WINMain;
}

class WINMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WINMain(QWidget *parent = nullptr);
    ~WINMain();

private slots:
    void on_pushButton_clicked();

private:
    Ui::WINMain *ui;
    SecDialog *secdialog;
    DLGTestimonialCreate *testimonialFormWin;
};

#endif // WINMAIN_H
