#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgcontactform.h"
#include "dlgtestimonialcreate.h"
#include "models/shapeellipse.h"
#include "models/ishape.h"
#include <util/goldenconevector.h>
#include <chrono>
#include <QDialog>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>

namespace Ui {
class WINMain;
}

class WINMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WINMain(QWidget *parent = nullptr);
    ~WINMain() override;

protected:
    virtual void paintEvent(QPaintEvent*) override;

private:
    Ui::WINMain *ui;
    DLGTestimonialCreate *testimonialFormWin;
    DLGContactForm *contactFormWin;
    GoldenConeVector<IShape*> vect;

    void initStartBt();
    void initTestimonialCreateBt();
    void initContactUsBt();
};

#endif // WINMAIN_H
