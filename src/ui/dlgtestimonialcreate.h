#ifndef DLGTESTIMONIALCREATE_H
#define DLGTESTIMONIALCREATE_H

#include <viewmodels/vmtestimonialcreate.h>
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
    VMTestimonialCreate* vm;
    VMTestimonialCreate* initializedVM();
};

#endif // DLGTESTIMONIALCREATE_H
