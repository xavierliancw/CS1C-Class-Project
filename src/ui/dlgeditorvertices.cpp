#include "dlgeditorvertices.h"
#include "ui_dlgeditorvertices.h"

DLGEditorVertices::DLGEditorVertices(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGEditorVertices)
{
    ui->setupUi(this);
}

DLGEditorVertices::~DLGEditorVertices()
{
    delete ui;
}
