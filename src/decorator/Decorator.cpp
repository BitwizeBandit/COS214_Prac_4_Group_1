#include "decorator/Decorator.h"

Decorator::Decorator(WorkComponent* component) : component(component) {}

Decorator::~Decorator() {
    delete component;
}

void Decorator::execute() {
    component->execute();
}

void Decorator::print(int indent) const {
    component->print(indent);
}

std::string Decorator::getName() const {
    return component->getName();
}

double Decorator::computeCost() const {
    return component->computeCost();
}

bool Decorator::isWaitingOnVFX() const {
    return component->isWaitingOnVFX();
}
