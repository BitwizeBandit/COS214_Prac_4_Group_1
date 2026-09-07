#ifndef STUNTSAFETYDECORATOR_H
#define STUNTSAFETYDECORATOR_H

#include "Decorator.h"

// Adds a mandatory stunt safety check to a component (typically a
// Shot involving a stunt).
class StuntSafetyDecorator : public Decorator {
public:
    explicit StuntSafetyDecorator(WorkComponent* component);

    virtual void execute() override;
    virtual void print(int indent = 0) const override;
    virtual double computeCost() const override;
};

#endif // STUNTSAFETYDECORATOR_H
