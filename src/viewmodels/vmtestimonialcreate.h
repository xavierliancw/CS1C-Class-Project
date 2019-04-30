#ifndef VMTESTIMONIALCREATE_H
#define VMTESTIMONIALCREATE_H

#include <QString>
#include <chrono>
#include <functional>

class VMTestimonialCreate
{
    std::function<void(bool)> onSubmitButtonEnabledUpdateLambda;
    std::function<void(bool)> onShowSuccessModeLambda;
public:
    const QString prompt1Txt = "Name";
    const QString prompt2Txt = "Your Testimonial";
    const QString saveBtTxt = "Submit";
    const QString successMsg = "Thank you for your feedback!";
    const QString successDoneBtTxt = "Done";

    enum Mode {composingTest, submittedTest};

    VMTestimonialCreate(std::function<void(bool)> onSubmitButtonEnabledUpdate,
                        std::function<void(bool)> onShowSuccessMode);
    ~VMTestimonialCreate();

    void submitTestimonial(const QString displayName, const QString testimonialTxt);
    void updateInputState(const QString displayName, const QString testimonialTxt);
};

#endif // VMTESTIMONIALCREATE_H
