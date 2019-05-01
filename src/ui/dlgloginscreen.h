#ifndef DLGLOGINSCREEN_H
#define DLGLOGINSCREEN_H

#include <QDialog>

namespace Ui {
class DLGLoginScreen;
}

class DLGLoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit DLGLoginScreen(QWidget *parent = nullptr);
    ~DLGLoginScreen();

private:
    Ui::DLGLoginScreen *ui;
};

#endif // DLGLOGINSCREEN_H
