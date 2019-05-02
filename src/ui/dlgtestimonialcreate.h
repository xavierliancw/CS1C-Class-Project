#ifndef DLGTESTIMONIALCREATE_H
#define DLGTESTIMONIALCREATE_H

#include <viewmodels/vmtestimonialcreate.h>
#include <QDialog>

namespace Ui {
class DLGTestimonialCreate;
}

/**
 * @brief Dialogue window for leaving testimonials.
 *
 */
class DLGTestimonialCreate : public QDialog
{
    Q_OBJECT

public:
    /**
     * @brief Constructor.
     *
     * @param parent: Parent QWidget.
     */
    explicit DLGTestimonialCreate(QWidget *parent = nullptr);
    /**
     * @brief Destructor.
     *
     */
    ~DLGTestimonialCreate();

private:
    Ui::DLGTestimonialCreate *ui; /**< DLGTestimonialCreate's UI pointer. */
    VMTestimonialCreate* vm; /**< View model for testimonial creation. */
    /**
     * @brief Initializes the view model, giving it appropriate hooks and dependencies to obtain
     * the starting state.
     *
     * @return VMTestimonialCreate: An initialized view model.
     */
    VMTestimonialCreate* initializedVM();
};

#endif // DLGTESTIMONIALCREATE_H
