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

    std::vector<IShape*> vect;

    for (IShape* aShape: shapes)
    {
        vect.push_back(aShape);
    }
    CustomSorts<IShape*> tempVect(vect);
    if (ui->radioID->isChecked())
    {
        tempVect.insertionSort([](IShape* one, IShape* two)
        {
            return one->id < two->id;
        });
    }
    else if (ui->radioArea->isChecked())
    {
        tempVect.insertionSort([](IShape* one, IShape* two)
        {
            return one->area() < two->area();
        });
    }
    else if (ui->radioPerimeter->isChecked())
    {
        tempVect.insertionSort([](IShape* one, IShape* two)
        {
            return one->perimeter() < two->perimeter();
        });
    }
    else
    {
        return;
    }

    //Serialize shapes to JSON and display
    QJsonArray jsonArrayOfShapesToSave;
    for (int x = 0; x < tempVect.v_copyVector.size(); ++x)
    {
        QJsonObject shapeJson = JSONShape::toJSON(tempVect.v_copyVector[x]);
        shapeJson["Perimeter"] = tempVect.v_copyVector[x]->perimeter();
        shapeJson["Area"] = tempVect.v_copyVector[x]->area();
        jsonArrayOfShapesToSave.push_back(shapeJson);
    }
    QJsonDocument doc;
    doc.setArray(jsonArrayOfShapesToSave);
    ui->textVw->setPlainText(doc.toJson());
}
