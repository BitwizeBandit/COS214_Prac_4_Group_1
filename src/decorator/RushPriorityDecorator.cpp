#include "decorator/RushPriorityDecorator.h"
#include <iostream>
#include <string>

RushPriorityDecorator::RushPriorityDecorator(WorkComponent* component)
    : Decorator(component) {}

void RushPriorityDecorator::execute() {
    // TODO: add rush-specific behaviour (e.g. print a "bumped to the
    // front of the schedule" message), then call Decorator::execute()
    // so the chain keeps going.
    Decorator::execute();
}

void RushPriorityDecorator::print(int indent) const {
    // TODO: print a "[RUSH]" marker before delegating.
    Decorator::print(indent);
}

double RushPriorityDecorator::computeCost() const {
    // TODO: add a rush fee on top of Decorator::computeCost().
    return Decorator::computeCost();
}
