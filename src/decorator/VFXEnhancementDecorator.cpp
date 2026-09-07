#include "decorator/StuntSafetyDecorator.h"
#include <iostream>

StuntSafetyDecorator::StuntSafetyDecorator(WorkComponent* component)
    : Decorator(component) {}

void StuntSafetyDecorator::execute() {
    // TODO: run/print the safety check, then Decorator::execute().
    Decorator::execute();
}

void StuntSafetyDecorator::print(int indent) const {
    // TODO: print a "[STUNT SAFETY]" marker before delegating.
    Decorator::print(indent);
}

double StuntSafetyDecorator::computeCost() const {
    // TODO: add a safety-check fee on top of Decorator::computeCost().
    return Decorator::computeCost();
}
