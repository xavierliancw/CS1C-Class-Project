#ifndef DLGLOGINSCREEN_H
#define DLGLOGINSCREEN_H

#include <QWidget>

namespace Ui {
class DLGLoginScreen;
}

class DLGLoginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit DLGLoginScreen(QWidget *parent = nullptr);
    ~DLGLoginScreen();
    bool check();

private slots:
    void on_verifiy_clicked();

private:
    Ui::DLGLoginScreen *ui;
    bool administrator;
};

#endif // DLGLOGINSCREEN_H
