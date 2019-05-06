#ifndef DLGLOGINSCREEN_H
#define DLGLOGINSCREEN_H

#include <QDialog>
#include <functional>

namespace Ui {
class DLGLoginScreen;
}

/**
 * @brief The DLGLoginScreen class: This is a class that inherits from the QDialog class and creates the login
 * screen used to authenticate a modeler so he or she can begin to add shapes.
 */
class DLGLoginScreen : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief The constructor takes a pointer to Qwidget and a function pointer to transfer the login state
     * around the program and instantitates the DLGLoginScreen ui based on the parameters passed in.
     * @param parent: The QWidget pointer is used to instantiate the screnn by casting the QWidget to a QDialog
     * @param authSuccessCallback: function pointer that is used to instantiate the canvas page if the information
     * is correctly inputed.
     * **/
    explicit DLGLoginScreen(QWidget *parent = nullptr,
                            std::function<void()> authSuccessCallback = [](){});
    /**
      * @brief The desturctor deletes the ui when it goes out of scope, so that no memory leaks take place.
      */
    ~DLGLoginScreen();

private slots:
    /**
      * @brief The function gets called when the verify button in the DLGLogin ui is clicked. It checks the
      * text written in the text boxes provided for the username and password, and if they are corrrect, it
      * calls the function necessary for showing the canvas screen where adding and deleting shapes is preformed.
      */
    void on_verifiy_clicked();

private:
    Ui::DLGLoginScreen *ui;
    std::function<void()> authCallback;
};

#endif // DLGLOGINSCREEN_H
