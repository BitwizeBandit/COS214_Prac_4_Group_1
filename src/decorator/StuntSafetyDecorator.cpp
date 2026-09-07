#include "decorator/StuntSafetyDecorator.h"
#include <iostream>

StuntSafetyDecorator::StuntSafetyDecorator(WorkComponent* component)
    : Decorator(component) {}

void StuntSafetyDecorator::execute() {
    
    std::cout << "Running stunt safety check for " << getName() << std::endl;
    Decorator::execute();
}

void StuntSafetyDecorator::print(int indent) const {
    std::cout << std::string(indent*2, ' ') << "[STUNT SAFETY]" << std::endl;
    Decorator::print(indent);
}

double StuntSafetyDecorator::computeCost() const {
    
    return Decorator::computeCost() + 500.0;
}
