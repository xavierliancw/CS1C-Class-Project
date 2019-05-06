#ifndef LCEDITVERTEX_H
#define LCEDITVERTEX_H

#include <QWidget>

namespace Ui {
class LCEditVertex;
}

class LCEditVertex : public QWidget
{
    Q_OBJECT

public:
    explicit LCEditVertex(QWidget *parent = nullptr);
    ~LCEditVertex();

private:
    Ui::LCEditVertex *ui;
};

#endif // LCEDITVERTEX_H
