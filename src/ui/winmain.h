#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgdeletemelater.h"
#include "dlgtestimonialcreate.h"
#include <chrono>
#include <QDialog>
#include <QMainWindow>
#include <QPainter>

#include <util/conevector.h>

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
    virtual void paintEvent(QPaintEvent *event) override;

private:
    Ui::WINMain *ui;
    DLGTestimonialCreate *testimonialFormWin;
    DLGDeleteMeLater *deletemelater;
    ConeVector<IShape*> vect;
};

#endif // WINMAIN_H
