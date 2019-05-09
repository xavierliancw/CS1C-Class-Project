#ifndef WINMAIN_H
#define WINMAIN_H

#include "dlgshapereport.h"
#include "dlgcontactform.h"
#include "dlgeditorrectframe.h"
#include "dlgtestimonialcreate.h"
#include "dlgloginscreen.h"
#include "dlgshapeselector.h"
#include "models/shapeellipse.h"
#include "models/ishape.h"
#include "models/shapecircle.h"
#include "viewmodels/vmcanvas.h"
#include "ui/dlgeditorvertices.h"
#include "ui/lcshapelayer.h"
#include "ui/dlgeditortext.h"
#include "models/jsontestimonial.h"
#include <util/goldenconevector.h>
#include <chrono>
#include <QDialog>
#include <QMainWindow>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QListWidgetItem>
#include <QDropEvent>
#include <QColorDialog>
#include <QMovie>
#include <QStackedLayout>
#include <QDesktopWidget>

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

    /**
         * @brief Look for Qt events
         * @param object : GUI element that's generating a Qt event
         * @param event : Qt event that's happening
         * @return Returns false always
         *
         * Drag and drop functionality within the itinerary is implemented
         * in this method.
         */
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    //General UI
    Ui::WINMain *ui;
    void switchScreenToShow(ScreensInWINMain);

    //Welcome screen UI
    QMovie* movie;
    QVector<QString> testimonials;
    void refreshTestimonials();

    //Pop up UI
    DLGContactForm *contactFormWin;
    DLGEditorRectFrame *dlgRectEditor;
    DLGLoginScreen *dlgLogin;

    //Canvas UI
    QTimer* refreshTimer;
    VMCanvas vm;
    QVector<LCShapeLayer*> layerVwCells;
    int rowNumberFromPickUpEvent;
    VMCanvas initCanvasVM();
    void initCanvasBackBt();
    void refreshLayersVw();
    void initLayerSelectionBehavior();
    void redrawWhateverCurrentCanvasIsShowing();
    void summonDlgThatEdits(IShape*);
    void updatePropertyInspectorFor(const IShape*);
    void initPropertyInspector();
    void initVertexEditor();
    void initRectEditor();
    void initTxtEditor();
    void updatePropInspectorVisibility();
    void initReportGenBt();

    //Welcome screen UI
    void initStartBt();
    void initTestimonialCreateBt();
    void initContactUsBt();
    VMCanvas initVM();
    void initGuestAuthenticateBt();
    void initGuestBackBt();
};

#endif // WINMAIN_H
