#include "decorator/VFXEnhancementDecorator.h"
#include <iostream>

VFXEnhancementDecorator::VFXEnhancementDecorator(WorkComponent* component)
    : Decorator(component) {}

void VFXEnhancementDecorator::execute() {
    
    Decorator::execute();
    std::cout << "Sending "<< getName() << " to VFX pipeline"<< std::endl;
}

void VFXEnhancementDecorator::print(int indent) const {
    std::cout << std::string(indent * 2, ' ') << "[VFX]" << std::endl;
    Decorator::print(indent);
}

double VFXEnhancementDecorator::computeCost() const {
    return Decorator::computeCost() + 3000.0;
}

bool VFXEnhancementDecorator::isWaitingOnVFX() const {
    return true;
}
