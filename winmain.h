#ifndef WINMAIN_H
#define WINMAIN_H

#include <QMainWindow>

namespace Ui {
class WINMain;
}

class WINMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit WINMain(QWidget *parent = nullptr);
    ~WINMain();

private:
    Ui::WINMain *ui;
};

#endif // WINMAIN_H
