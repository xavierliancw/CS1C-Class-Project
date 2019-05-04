#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgcontactform.h"
#include "dlgshapeadderrect.h"
#include "dlgtestimonialcreate.h"
#include "models/shapeellipse.h"
#include "models/ishape.h"
#include "viewmodels/vmcanvas.h"
#include <util/goldenconevector.h>
#include <chrono>
#include <QDialog>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>

namespace Ui {
class WINMain;
}

/**
 * @brief The main window for the entire application.
 *
 */
class WINMain : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief The different screens WINMain can switch between.
     */
    enum ScreensInWINMain {welcome, guest, canvas};

    /**
     * @brief Constructor.
     *
     * @param parent: Parent QWidget pointer.
     */
    explicit WINMain(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     *
     */
    ~WINMain() override;

protected:
    /**
     * @brief Lifecycle event that renders graphics on the window.
     *
     * @param QPaintEvent pointer (unused).
     */
    virtual void paintEvent(QPaintEvent*) override;
    /**
     * @brief Lifecycle event that fires when the window is closed.
     *
     * @param QCloseEvent pointer (unused).
     */
    void closeEvent(QCloseEvent*) override;

private:
    Ui::WINMain *ui;
    DLGTestimonialCreate *testimonialFormWin;
    DLGContactForm *contactFormWin;
    DLGShapeAdderRect *dlgAddShapeRect;
    VMCanvas vm;

    //Canvas functions
    VMCanvas initCanvasVM();
    void redrawWhateverCurrentCanvasIsShowing();

    //UI functions
    void switchScreenToShow(ScreensInWINMain);

    //UI on welcome screen
    void initStartBt();
    void initTestimonialCreateBt();
    void initContactUsBt();

    //UI on canvas screen
    void initAddRectBt();
    void initAddSquareBt();
};

#endif // WINMAIN_H
