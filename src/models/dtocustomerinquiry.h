#ifndef DTOCUSTOMERINQUIRY_H
#define DTOCUSTOMERINQUIRY_H

#include <string>

/**
 * @brief POCO that represents a customer inquiry.
 *
 */
struct DTOCustomerInquiry
{
public:
    std::string custEmail; /**< Customer email. */
    std::string inquiryTxt; /**< The inquiry text. */
    /**
     * The time when this testimonial was created in milliseconds since UNIX time, midnight of 1
     * Jan 1970 GMT.
     */
    int timestamp_unix;
};

#endif // DTOCUSTOMERINQUIRY_H
