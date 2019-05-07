#ifndef DLGCONTACTFORM_H
#define DLGCONTACTFORM_H

#include <QDialog>
#include <models/dtocustomerinquiry.h>
#include <models/jsoncustomerinquiry.h>
#include <chrono>
#include <QJsonArray>
#include "services/svcjson.h"
#include "gimme.h"

namespace Ui {class DLGContactForm;}
/**
 * @brief The DLGContactForm class inherits from QDialog has all data and function members relating to the
 * Contact Form and button. It also has logic corresponding to the JSON storing to save the email and questions.
 */
class DLGContactForm : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief DLGContactForm is the consturctor which instantiates the Contact Form which brings up the window
     * and forces the user to input something for the submit button to work.
     * @param parent: A pointer that is used for the parent class needed for instantiation.
     */
    explicit DLGContactForm(QWidget *parent = nullptr);
    /**
      * @brief ~DLGContactForm is the destructor that deletes the ui for the DLGContactForm window.
      */
    ~DLGContactForm();

private:
    /**
     * @brief ui: The data member used to create the new DLGContactForm
     */
    Ui::DLGContactForm *ui;
    /**
     * @brief sendCustomerInquiry: the function that saves the data the user inputs in the email and question text areas.
     */
    void sendCustomerInquiry();
    /**
     * @brief showSuccessScreen: This function shows a success screen after the data entered in by the user is
     * correctly saved into the JSON file.
     */
    void showSuccessScreen();
    /**
     * @brief updateSubmitButton: This function connects the submit button's state to the line edit and text edit
     * representing the email and questions of the user.
     */
    void updateSubmitButton();
};

#endif // DLGCONTACTFORM_H

