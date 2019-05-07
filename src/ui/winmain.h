#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgcontactform.h"
#include "dlgshapeadderrect.h"
#include "dlgtestimonialcreate.h"
#include "dlgshapeaddtri.h"
#include "models/shapeellipse.h"
#include "models/ishape.h"
#include "models/triangle.h"
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
    VMCanvas vm; /**< View model for the canvas that contains business logic and UI definitions. */
    DLGShapeAdderRect *dlgAddShapeRect; /** < Dialog that creates rectangles. */
    DLGShapeAdderTri *dlgAddShapeTri; /** < Dialog that creates triangles. */

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
};

#endif // WINMAIN_H
