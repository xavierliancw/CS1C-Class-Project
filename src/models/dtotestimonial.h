#ifndef DTOTESTIMONIAL_H
#define DTOTESTIMONIAL_H
#include <string>
#include <optional>

/**
 * @brief POCO that represents a customer testimonial.
 *
 */
struct DTOTestimonial
{
public:
    std::string displayName; /**< Display name of the author of this testimonial. */
    std::string txt; /**< The testimonial text. */
    /**
     * The time when this testimonial was created in milliseconds since UNIX time, midnight of 1
     * Jan 1970 GMT.
     */
    int timestamp_unix;
};

#endif // DTOTESTIMONIAL_H
