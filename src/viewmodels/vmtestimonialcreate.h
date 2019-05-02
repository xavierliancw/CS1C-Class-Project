#ifndef VMTESTIMONIALCREATE_H
#define VMTESTIMONIALCREATE_H

#include <QString>
#include <chrono>
#include <functional>

/**
 * @brief View model for the UI that lets users create testimonials.
 *
 */
class VMTestimonialCreate
{
    /**
     * @brief Lambda that gets called to determine if the testimonial submit button should be
     * enabled or not.
     *
     * @param bool: True if button should be enabled, false otherwise.
     * @return std::function<void >
     */
    std::function<void(bool)> onSubmitButtonEnabledUpdateLambda;
    /**
     * @brief Lambda that gets called to determine if the success screen should be displayed or
     * not.
     *
     * @param bool: True if the success screen should be showing, false otherwise.
     * @return std::function<void >
     */
    std::function<void(bool)> onShowSuccessModeLambda;
public:
    const QString prompt1Txt = "Name"; /**< Prompt for the author's display name. */
    const QString prompt2Txt = "Your Testimonial"; /**< Prompt for testimonial text. */
    const QString saveBtTxt = "Submit"; /**< Text that the submit button should display. */
    const QString successMsg = "Thank you for your feedback!"; /**< Success message to display. */
    const QString successDoneBtTxt = "Done"; /**< Text that the done button should display. */

    /**
     * @brief Enum for the different states this UI has.
     *
     */
    enum Mode {composingTest, submittedTest};

    /**
     * @brief Constructor.
     *
     * @param onSubmitButtonEnabledUpdate: Lambda with boolean that dictates the state of the
     * submit button (enable when true, disable when false).
     * @param onShowSuccessMode: Lambda with boolean that dictates when the success state should
     * be triggered (show success when true, don't show success when false).
     */
    VMTestimonialCreate(std::function<void(bool)> onSubmitButtonEnabledUpdate,
                        std::function<void(bool)> onShowSuccessMode);
    /**
     * @brief Destructor.
     *
     */
    ~VMTestimonialCreate();

    /**
     * @brief Saves a testimonial to wherever testimonials get stored.
     *
     * @param displayName: The display name of the testimonial author.
     * @param testimonialTxt: The text of the testimonial.
     */
    void submitTestimonial(const QString displayName, const QString testimonialTxt);
    /**
     * @brief Inputs for the state machine that controls the primary business logic of this UI.
     * This should be called whenever the text changes in either the display name or testimonial
     * text text fields.
     *
     * @param displayName: The text that's currently in the display name text field.
     * @param testimonialTxt: The text that's currently in the text field for the testimonial text.
     */
    void updateInputState(const QString displayName, const QString testimonialTxt);
};

#endif // VMTESTIMONIALCREATE_H
