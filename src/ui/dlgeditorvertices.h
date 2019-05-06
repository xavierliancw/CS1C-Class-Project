#ifndef DLGEDITORVERTICES_H
#define DLGEDITORVERTICES_H

#include <QDialog>

namespace Ui {
class DLGEditorVertices;
}

class DLGEditorVertices : public QDialog
{
    Q_OBJECT

public:
    explicit DLGEditorVertices(QWidget *parent = nullptr);
    ~DLGEditorVertices();

private:
    Ui::DLGEditorVertices *ui;
};

#endif // DLGEDITORVERTICES_H
