#include "decorator/VFXEnhancementDecorator.h"
#include <iostream>

VFXEnhancementDecorator::VFXEnhancementDecorator(WorkComponent* component)
    : Decorator(component) {}

void VFXEnhancementDecorator::execute() {
    // TODO: run/print the VFX enhancement step, then Decorator::execute().
    Decorator::execute();
}

void VFXEnhancementDecorator::print(int indent) const {
    // TODO: print a "[VFX]" marker before delegating.
    Decorator::print(indent);
}

double VFXEnhancementDecorator::computeCost() const {
    // TODO: add a VFX fee on top of Decorator::computeCost().
    return Decorator::computeCost();
}

bool VFXEnhancementDecorator::isWaitingOnVFX() const {
    // TODO: decide - always true while this decorator is attached, or
    // delegate to Decorator::isWaitingOnVFX()? Document your choice.
    return true;
}
