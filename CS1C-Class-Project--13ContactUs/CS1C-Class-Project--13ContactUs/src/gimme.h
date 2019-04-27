#ifndef GIMME_H
#define GIMME_H

#include <QString>

class Gimme
{
    static Gimme* instance;
    Gimme();
public:
    static Gimme* sharedInstance();
    const QString theFileNameForTestimonials = "testimonials.json";
};

#endif // GIMME_H
