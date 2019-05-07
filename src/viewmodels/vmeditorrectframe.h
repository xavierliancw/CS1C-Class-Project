#ifndef VMEDITORRECTFRAME_H
#define VMEDITORRECTFRAME_H

#include <QDebug>
#include <QFrame>
#include <functional>
#include "models/shapesquare.h"
#include "models/shapecircle.h"

/**
 * @brief View model for the dialog that edits shapes that use QRects to render.
 *
 */
class VMEditorRectFrame
{
public:
    /**
     * @brief Constructor.
     *
     * @param vmDidSetSubmitBtEnabled: Controls if submit button is enabled or not.
     * @param vmDidSetFourthPromptHidden: Controls if fourth prompt is hidden or not.
     * @param vmDidGenerateNewShape: Callback for when this dialog generates a new shape.
     * @param vmDidWantRawX: Gives this VM a way to grab input for the X coord.
     * @param vmDidWantRawY: Gives this VM a way to grab input for the Y coord.
     * @param vmDidWantRawW: Gives this VM a way to grab input for the width;
     * @param vmDidWantRawH: Gives this VM a way to grab input for the height;
     * @param vmDidInitNewState: Controls when general UI gets updated.
     */
    VMEditorRectFrame(std::function<void(bool)> vmDidSetSubmitBtEnabled,
                      std::function<void(bool)> vmDidSetFourthPromptHidden,
                      std::function<void(IShape*)> vmDidGenerateNewShape,
                      std::function<QString()> vmDidWantRawX,
                      std::function<QString()> vmDidWantRawY,
                      std::function<QString()> vmDidWantRawW,
                      std::function<QString()> vmDidWantRawH,
                      std::function<void()> vmDidInitNewState);
    /**
     * @brief Destructor.
     *
     */
    ~VMEditorRectFrame();

    /**
     * @brief Call this whenver a text field changes so the VM can update its state.
     *
     */
    void performActionsOnInputEdit();

    /**
     * @brief Gets the title text for the current mode.
     *
     * @return QString
     */
    QString getTxtLblTitle() const;
    /**
     * @brief Grabs the cancel button text.
     *
     * @return QString
     */
    QString getTxtBtCancel() const;
    /**
     * @brief Grabs the submit button text for the current mode.
     *
     * @return QString
     */
    QString getTxtBtSubmit() const;
    /**
     * @brief Gets the text for prompt 1.
     *
     * @return QString
     */
    QString getTxtPrompt1() const;
    /**
     * @brief Gets the text for prompt 2.
     *
     * @return QString
     */
    QString getTxtPrompt2() const;
    /**
     * @brief Gets the text for prompt 3.
     *
     * @return QString
     */
    QString getTxtPrompt3() const;
    /**
     * @brief Gets the text for prompt 4.
     *
     * @return QString
     */
    QString getTxtPrompt4() const;

    /**
     * @brief Initializes the VM's state machine.
     *
     * @param shapeTypeToGenerate
     */
    void setModeWithDependency(IShape::ShapeType shapeTypeToGenerate);
    /**
     * @brief Initializes the VM's state machine.
     *
     * @param shapeToEdit
     */
    void setModeWithDependency(IShape* shapeToEdit);
    /**
     * @brief Call this when the submit button is pressed.
     *
     */
    void performActionsWhenDoneEditing();

    /**
     * @brief Obtains what the VM is currently holding for the input X value.
     * @return  QString
     */
    QString getRawX() const;
    /**
     * @brief Obtains what the VM is currently holding for the input Y value.
     * @return  QString
     */
    QString getRawY() const;
    /**
     * @brief Obtains what the VM is currently holding for the input width value.
     * @return  QString
     */
    QString getRawW() const;
    /**
     * @brief Obtains what the VM is currently holding for the input height value.
     * @return  QString
     */
    QString getRawH() const;

private:
    enum Mode {newRectangle, editRectangle,
               newSquare, editSquare,
               newEllipse, editEllipse,
               newCircle, editCicle,
               noMode};
    Mode currentUIMode = noMode;
    QString rawX = "";
    QString rawY = "";
    QString rawW = "";
    QString rawH = "";
    QRect* finalizedFrame = nullptr;
    IShape* shapeCurrentlyBeingEdited = nullptr;

    std::function<void(bool)> vmDidSetSubmitBtEnabled;
    std::function<void(bool)> vmDidSetFourthPromptHidden;
    std::function<void(IShape*)> vmDidGenerateNewShape;
    std::function<QString()> vmDidWantRawX;
    std::function<QString()> vmDidWantRawY;
    std::function<QString()> vmDidWantRawW;
    std::function<QString()> vmDidWantRawH;
    std::function<void()> vmDidInitNewState;

    void applyState(Mode stateToApply, bool justInitialized);
    void reset();
};

#endif // VMEDITORRECTFRAME_H
