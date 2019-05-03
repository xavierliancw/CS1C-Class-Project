#include "gimme.h"

Gimme* Gimme::instance = nullptr;

Gimme::Gimme()
{}

const Gimme *Gimme::theShared()
{
    if (instance == nullptr)
    {
        instance = new Gimme();
    }
    return instance;
}
