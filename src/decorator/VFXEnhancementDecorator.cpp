#include "decorator/VFXEnhancementDecorator.h"
#include <iostream>
#include <string>

VFXEnhancementDecorator::VFXEnhancementDecorator(WorkComponent* component)
    : Decorator(component) {}

void VFXEnhancementDecorator::execute() {
    
    std::cout << "Sending "<< getName() << " to VFX pipeline"<< std::endl;
    Decorator::execute();

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
