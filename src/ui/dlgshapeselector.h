#ifndef DLGSHAPESELECTOR_H
#define DLGSHAPESELECTOR_H

#include <QDialog>

namespace Ui {
class DLGShapeSelector;
}

class DLGShapeSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DLGShapeSelector(QWidget *parent = nullptr);
    ~DLGShapeSelector();

private slots:
    void on_pushButton_clicked();

private:
    Ui::DLGShapeSelector *ui;
};

#endif // DLGSHAPESELECTOR_H
