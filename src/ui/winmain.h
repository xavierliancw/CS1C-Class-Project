#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgdeletemelater.h"
#include "dlgtestimonialcreate.h"

#include <QDialog>
#include <QMainWindow>
#include <QPainter>
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

private:
    Ui::WINMain *ui;
    SecDialog *secdialog;
    DLGTestimonialCreate *testimonialFormWin;
    DLGDeleteMeLater *deletemelater;
};

#endif // WINMAIN_H
