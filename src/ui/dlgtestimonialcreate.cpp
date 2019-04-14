#include "dlgtestimonialcreate.h"
#include "ui_dlgtestimonialcreate.h"

DLGTestimonialCreate::DLGTestimonialCreate(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGTestimonialCreate)
{
    ui->setupUi(this);
}

DLGTestimonialCreate::~DLGTestimonialCreate()
{
    delete ui;
}
