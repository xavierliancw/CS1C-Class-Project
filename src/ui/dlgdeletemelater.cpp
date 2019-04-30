#include "dlgdeletemelater.h"
#include "ui_dlgdeletemelater.h"
#include <QDebug>

DLGDeleteMeLater::DLGDeleteMeLater(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DLGDeleteMeLater)
{
    ui->setupUi(this);

    connect(ui->eatMeBt, &QPushButton::clicked, ui->eatMeBt, [this]()
    {
        ShapeRect* rectang = new ShapeRect(0, 2 * static_cast<int>(vect.size()), 10, 50, 100);
        for (unsigned long x = 0; x < vect.size(); ++x)
        {
            if (ShapeRect* castRect = dynamic_cast<ShapeRect*>(vect[x]))
            {
                castRect->frame.setY(castRect->frame.y() + 10);
                castRect = nullptr;
            }
        }
        vect.push_back(rectang);
        this->update();
        this->ui->waluigi->update();
    });

    connect(ui->vomit, &QPushButton::clicked, ui->vomit, [this]()
    {
        if (!vect.empty())
        {
            IShape *popBack = vect.back();
            delete popBack;
            popBack = nullptr;
            vect.pop_back();

            this->update();
            this->ui->waluigi->update();
        }
    });
}

DLGDeleteMeLater::~DLGDeleteMeLater()
{
    for (unsigned long x = 0; x < vect.size(); ++x)
    {
        delete vect[x];
        vect[x] = nullptr;
    }
    delete ui;
}

void DLGDeleteMeLater::paintEvent(QPaintEvent *event)
{
    QPainter painter(ui->waluigi);

    painter.fillRect(ui->waluigi->rect(), Qt::GlobalColor::black);

    painter.setBackground(QBrush(Qt::GlobalColor::white));

    for (unsigned long x = vect.size(); x > 0; --x)
    {
        vect[x - 1]->draw(painter);
    }
}
