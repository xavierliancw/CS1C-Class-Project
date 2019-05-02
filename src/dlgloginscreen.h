#ifndef DLGLOGINSCREEN_H
#define DLGLOGINSCREEN_H

#include <QDialog>
#include <functional>

namespace Ui {
class DLGLoginScreen;
}

class DLGLoginScreen : public QDialog
{
    Q_OBJECT

public:
    explicit DLGLoginScreen(QWidget *parent = nullptr,
                            std::function<void(bool)> authCallback = [](bool){});
    ~DLGLoginScreen();
    bool check();

private slots:
    void on_verifiy_clicked();

private:
    Ui::DLGLoginScreen *ui;
    bool administrator;
    std::function<void(bool)> authCallback;
};

#endif // DLGLOGINSCREEN_H
