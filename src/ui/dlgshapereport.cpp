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

    std::vector<IShape*> tempVect;
    for (IShape* aShape: shapes)
    {
        tempVect.push_back(aShape);
    }
    if (ui->radioID->isChecked())
    {
        insertionSort(tempVect, [](IShape* one, IShape* two)
        {
            return one->id < two->id;
        });
    }
    else if (ui->radioArea->isChecked())
    {
        insertionSort(tempVect, [](IShape* one, IShape* two)
        {
            return one->area() < two->area();
        });
    }
    else if (ui->radioPerimeter->isChecked())
    {
        insertionSort(tempVect, [](IShape* one, IShape* two)
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
    for (int x = 0; x < tempVect.size(); ++x)
    {
        QJsonObject shapeJson = JSONShape::toJSON(tempVect[x]);
        shapeJson["Perimeter"] = tempVect[x]->perimeter();
        shapeJson["Area"] = tempVect[x]->area();
        jsonArrayOfShapesToSave.push_back(shapeJson);
    }
    QJsonDocument doc;
    doc.setArray(jsonArrayOfShapesToSave);
    ui->textVw->setPlainText(doc.toJson());
}

void DLGShapeReport::insertionSort(std::vector<IShape*> &sortThese,
                                   std::function<bool(IShape*, IShape*)> comparatorWhereFirstComesBeforeSecondPrm)
{
    //There's gotta be something to sort
    if (sortThese.size() < 1) {return;}

    IShape* holder;  //Holds onto an element being moved
    int cursor = 0;  //Cursor for element that's going to be shifted
    int shifter = 0; //Shifts elements until the correct spot for holder is found
    int finder = 0;  //Finds place to insert into

    //Loop until sorted
    while (cursor < sortThese.size())
    {
        //Pick up the cursor element
        holder = sortThese[cursor];

        //Look for spot to insert into
        finder = cursor - 1;
        while (finder > -1 && comparatorWhereFirstComesBeforeSecondPrm(holder, sortThese[finder]))
        {
            --finder;
        }
        //Now that a spot has been found, shift everything over to make room for the cursor element
        shifter = cursor - 1;
        while (shifter > finder)
        {
            sortThese[shifter + 1] = sortThese[shifter];
            --shifter;
        }
        //Insert into the found spot
        sortThese[finder + 1] = holder;

        //Advance for next loop
        ++cursor;
    }
}
