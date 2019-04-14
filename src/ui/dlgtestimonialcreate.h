#ifndef DLGTESTIMONIALCREATE_H
#define DLGTESTIMONIALCREATE_H

#include <QDialog>

namespace Ui {
class DLGTestimonialCreate;
}

class DLGTestimonialCreate : public QDialog
{
    Q_OBJECT

public:
    explicit DLGTestimonialCreate(QWidget *parent = nullptr);
    ~DLGTestimonialCreate();

private:
    Ui::DLGTestimonialCreate *ui;
};

#endif // DLGTESTIMONIALCREATE_H
