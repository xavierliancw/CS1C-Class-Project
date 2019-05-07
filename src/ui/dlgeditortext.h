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

class DLGEditorText : public QDialog
{
    Q_OBJECT

public:
    explicit DLGEditorText(QWidget *parent,
                           ShapeText* txtToEdit,
                           std::function<void(ShapeText*)> newGeneratedTxtCallback);
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
