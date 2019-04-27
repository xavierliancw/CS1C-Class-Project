#include "gimme.h"

Gimme* Gimme::instance = nullptr;

Gimme::Gimme()
{}

Gimme* Gimme::sharedInstance()
{
    if (instance == nullptr)
    {
        instance = new Gimme();
    }
    return instance;
}
