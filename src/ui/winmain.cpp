#include "winmain.h"
#include "ui_winmain.h"

#include <models/dtotestimonial.h>
#include <models/jsontestimonial.h>

#include <services/svcjson.h>
#include <chrono>
#include<QJsonArray>
#include <QDebug>

WINMain::WINMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WINMain)
{
    ui->setupUi(this);

    //TODO DELETE THIS SECTION
    DTOTestimonial test;
    test.txt = "This app is kewl";
    test.displayName = "Xavier";
    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
                );
    test.timestamp_unix = static_cast<int>(ms.count());

    DTOTestimonial test2;
    test2.txt = "yeet. this app is lit.";
    test2.displayName = "Chamaran McGee";
    test2.timestamp_unix = 236079312;

    QJsonArray jsonAr;
    jsonAr.append(JSONTestimonial::toJSON(test));
    jsonAr.append(JSONTestimonial::toJSON(test2));

    SVCJson::getInstance()->persistJSONToLocalFileSystem(jsonAr, "test.json");

    QJsonArray ar = SVCJson::getInstance()->readJsonArrayFile("test.json");
    std::vector<DTOTestimonial*> testimonials;

    for (int x = 0; x < ar.count(); ++x)
    {
        testimonials.push_back(JSONTestimonial::fromJSON(ar.at(x).toObject()));
    }
    qDebug() << QString::fromStdString(testimonials.at(0)->txt);
    //END TODO
}

WINMain::~WINMain()
{
    delete ui;
}
