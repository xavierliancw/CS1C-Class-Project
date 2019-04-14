#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgtestimonialcreate.h"

#include <QDialog>
#include <QMainWindow>

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

    DLGTestimonialCreate *testimonialFormWin;
};

#endif // WINMAIN_H
