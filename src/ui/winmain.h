#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgcontactform.h"
#include "dlgshapeadderrect.h"
#include "dlgtestimonialcreate.h"
#include "dlgloginscreen.h"
#include "dlgshapeselector.h"
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

private:
    Ui::WINMain *ui; /**< WINMain's UI pointer. */
    DLGTestimonialCreate *testimonialFormWin; /**< Pointer to the testimonial creation dialogue. */
    DLGContactForm *contactFormWin; /**< Pointer to the contact form dialogue. */
    DLGLoginScreen *loginFormWin; /** < Dialog that authenticates modelers. */
    VMCanvas vm; /**< View model for the canvas that contains business logic and UI definitions. */
    DLGShapeAdderRect *dlgAddShapeRect; /** < Dialog that creates rectangles. */

    /**
     * @brief Initializes the button behavior that launches the canvas view.
     *
     */
    void initStartBt();
    /**
     * @brief Initializes the button behavior that summons the testimonial creation dialogue.
     *
     */
    void initTestimonialCreateBt();
    /**
     * @brief Initializes the button that summons the contact form dialogue.
     *
     */
    void initContactUsBt();
    /**
     * @brief Initializes the view model that contains the canvas business logic.
     *
     */
    VMCanvas initVM();
    /**
     * @brief Initializes the edit button which calls the login screen to change
     * the screen to the canvas.
     */
    void initGuestAuthenticateBt();
    /**
     * @brief Initializes the back button on the guest view to switch back to the
     * main welcome page.
     */
    void initGuestBackBt();
    /**
     * @brief Initializes the back button on the canvas that goes back to the welcome page
     */
    void initCanvasBackBt();
};

#endif // WINMAIN_H
