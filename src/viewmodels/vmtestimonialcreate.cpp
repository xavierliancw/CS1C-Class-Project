#include "vmtestimonialcreate.h"
#include <models/dtotestimonial.h>
#include <models/jsontestimonial.h>
#include <services/svcjson.h>
#include "gimme.h"
#include <chrono>

VMTestimonialCreate::VMTestimonialCreate(std::function<void(bool)> onSubmitButtonEnabledUpdate,
                                         std::function<void(bool)> onShowSuccessMode)
{
    onSubmitButtonEnabledUpdateLambda = onSubmitButtonEnabledUpdate;
    onSubmitButtonEnabledUpdate(false);

    onShowSuccessModeLambda = onShowSuccessMode;
    onShowSuccessModeLambda(false);
}

VMTestimonialCreate::~VMTestimonialCreate()
{}

void VMTestimonialCreate::submitTestimonial(const QString displayName,
                                            const QString testimonialTxt)
{
    //Validate inputs
    if (displayName.isEmpty())
    {
        if (onSubmitButtonEnabledUpdateLambda != nullptr)
        {
            onSubmitButtonEnabledUpdateLambda(false);
        }
        return;
    }
    if (testimonialTxt.isEmpty())
    {
        if (onSubmitButtonEnabledUpdateLambda != nullptr)
        {
            onSubmitButtonEnabledUpdateLambda(false);
        }
        return;
    }
    //Create the DTO
    DTOTestimonial newTest;
    newTest.txt = testimonialTxt.toUtf8().constData();
    newTest.displayName = displayName.toUtf8().constData();
    newTest.timestamp_unix = static_cast<int>(
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()
                    ).count()
                );

    //Serialize into JSON
    QJsonObject json = JSONTestimonial::toJSON(newTest);

    //Retrive testimonials from storage if there are any
    QJsonArray existingTests;
    try
    {
        existingTests = SVCJson::getInstance()->readJsonArrayFile(
                    Gimme::theShared()->fileNameForTestimonials
                    );
    }
    catch (SVCJson::JsonFileSystemError fileErr)
    {
        //Don't worry about it because there are no testimonials in storage
    }
    //Add the new testimonial
    existingTests.append(json);

    //Save it
    SVCJson::getInstance()->persistJSONToLocalFileSystem(
                existingTests, Gimme::theShared()->fileNameForTestimonials
                );
    onShowSuccessModeLambda(true);
    return;
}

void VMTestimonialCreate::updateInputState(const QString displayName, const QString testimonialTxt)
{
    if (onSubmitButtonEnabledUpdateLambda != nullptr)
    {
        onSubmitButtonEnabledUpdateLambda(!displayName.isEmpty() && !testimonialTxt.isEmpty());
    }
}
