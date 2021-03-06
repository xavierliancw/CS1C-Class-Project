#ifndef DLGEDITORTEXT_H
#define DLGEDITORTEXT_H

#include <QDialog>
#include "models/shapetext.h"
#include <functional>
#include <QFontDialog>
#include <QIntValidator>

namespace Ui {
class DLGEditorText;
}

/**
 * @brief Dialog that edits text.
 *
 */
class DLGEditorText : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent: Parent pointer.
     * @param txtToEdit: Text shape to edit if specified.
     * @param newGeneratedTxtCallback: Dynamically allocated new text shape if txtToEdit is null.
     */
    explicit DLGEditorText(QWidget *parent,
                           ShapeText* txtToEdit,
                           std::function<void(ShapeText*)> newGeneratedTxtCallback);
    /**
     * @brief Destructor.
     *
     */
    ~DLGEditorText();

private:
    Ui::DLGEditorText *ui;
    ShapeText *existingTxtBeingEdited;
    std::function<void(ShapeText*)> newGeneratedTxtCallback;

    QFont fontToApply;
    QIntValidator *intValidator;

    void updateSubmitBt();
};

#endif // DLGEDITORTEXT_H
