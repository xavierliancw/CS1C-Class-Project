#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgcontactform.h"
#include "dlgshapeadderrect.h"
#include "dlgtestimonialcreate.h"
#include "models/shapeellipse.h"
#include "models/ishape.h"
#include "models/shapecircle.h"
#include "viewmodels/vmcanvas.h"
#include "ui/lcshapelayer.h"
#include <util/goldenconevector.h>
#include <chrono>
#include <QDialog>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QListWidgetItem>

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
    //General UI
    Ui::WINMain *ui;
    void switchScreenToShow(ScreensInWINMain);

    //Pop up UI
    DLGTestimonialCreate *testimonialFormWin;
    DLGContactForm *contactFormWin;
    DLGShapeAdderRect *dlgAddShapeRect;

    //Canvas UI
    QTimer* refreshTimer;
    VMCanvas vm;
    QVector<LCShapeLayer*> layerVwCells;
    VMCanvas initCanvasVM();
    void initCanvasBackBt();
    void initAddRectBt();
    void initAddSquareBt();
    void refreshLayersVw();
    void initLayerSelectionBehavior();
    void redrawWhateverCurrentCanvasIsShowing();

    //Welcome screen UI
    void initStartBt();
    void initTestimonialCreateBt();
    void initContactUsBt();

};

#endif // WINMAIN_H
