#include "decorator/RushPriorityDecorator.h"
#include <iostream>
#include <string>

RushPriorityDecorator::RushPriorityDecorator(WorkComponent* component)
    : Decorator(component) {}

void RushPriorityDecorator::execute() {

    std::cout << "Rush crew assigned to " << getName() <<std::endl;
    Decorator::execute();
}

void RushPriorityDecorator::print(int indent) const {

    std::cout << "Rush crew assigned to " << getName() <<std::endl;
    Decorator::execute();
}

double RushPriorityDecorator::computeCost() const {
    
    return Decorator::computeCost() + 2000.0;
}
