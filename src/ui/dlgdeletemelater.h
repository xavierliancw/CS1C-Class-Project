#ifndef DLGDELETEMELATER_H
#define DLGDELETEMELATER_H

#include <QDialog>
#include <QPainter>
#include <vector>
#include <models/ishape.h>
#include <models/shaperect.h>

namespace Ui {
class DLGDeleteMeLater;
}

class DLGDeleteMeLater : public QDialog
{
    Q_OBJECT

public:
    explicit DLGDeleteMeLater(QWidget *parent = nullptr);
    ~DLGDeleteMeLater();

    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::DLGDeleteMeLater *ui;

    std::vector<IShape*> vect;
};

#endif // DLGDELETEMELATER_H
