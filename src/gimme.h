#ifndef GIMME_H
#define GIMME_H

#include <QString>

/**
 * @brief Singleton for project constants.
 *
 */
class Gimme
{
    static Gimme* instance; /**< Singleton instance. */
    /**
     * @brief Private constructor (since this is a singleton).
     *
     */
    Gimme();
public:
    /**
     * @brief Accessor function to get the shared instance of this singleton.
     *
     * @return Gimme
     */
    static const Gimme* theShared();
    /**
     * Name of the JSON file that persists testimonials.
     */
    const QString fileNameForTestimonials = "testimonials.json";
    /**
     * Name of the JSON file that persists the graphics canvas.
     */
    const QString fileNameForSavedGraphicsCanvas = "canvas.json";
    /**
     * Name of the JSON file that persists customer inquiries.
     */
    const QString fileNameForSavedCustomerInquiries = "inquiries.json";

    const QString fileNameForSavedShapeReports = "reports.json";
    const QString fileNameForSavedShapeReportsArea = "reportsArea.json";
    const QString fileNameForSavedShapeReportsPerimeter = "reportsPerimeter.json";
};

#endif // GIMME_H
