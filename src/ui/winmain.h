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
    GoldenConeVector<IShape*> vect; /**< TODO: Move this later */

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
};

#endif // WINMAIN_H
