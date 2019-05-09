#include "dlgshapereport.h"
#include "ui_dlgshapereport.h"
#include <QtDebug>

DLGShapeReport::DLGShapeReport(QWidget *parent, QVector<IShape*> shapes) :
    QDialog(parent),
    ui(new Ui::DLGShapeReport),
    shapes(shapes)
{
    ui->setupUi(this);

    QWidget::setWindowTitle("Shape Report");

    connect(ui->btClose, &QPushButton::clicked, ui->btClose, [this]()
    {
        this->close();
    });
    ui->btExport->setVisible(false);

    connect(ui->radioID, &QRadioButton::clicked, ui->radioID, [this]()
    {
        this->triggerSort();
    });
    connect(ui->radioArea, &QRadioButton::clicked, ui->radioArea, [this]()
    {
        this->triggerSort();
    });
    connect(ui->radioPerimeter, &QRadioButton::clicked, ui->radioPerimeter, [this]()
    {
        this->triggerSort();
    });
    triggerSort();
}

DLGShapeReport::~DLGShapeReport()
{
    delete ui;
}

void DLGShapeReport::triggerSort()
{
    ui->textVw->setPlainText("");

    qDebug() << "Put sort in here";
    if (ui->radioID->isChecked())
    {
        //TODO
    }
    else if (ui->radioArea->isChecked())
    {
        //TODO
    }
    else if (ui->radioPerimeter->isChecked())
    {
        //TODO
    }
    else
    {
        return;
    }
    //Serialize shapes to JSON and display
    QJsonArray jsonArrayOfShapesToSave;
    for (int x = 0; x < shapes.size(); ++x)
    {
        QJsonObject shapeJson = JSONShape::toJSON(shapes[x]);
        shapeJson["Perimeter"] = shapes[x]->perimeter();
        shapeJson["Area"] = shapes[x]->area();
        jsonArrayOfShapesToSave.push_back(shapeJson);
    }
    QJsonDocument doc;
    doc.setArray(jsonArrayOfShapesToSave);
    ui->textVw->setPlainText(doc.toJson());
}
