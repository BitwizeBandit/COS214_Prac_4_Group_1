#ifndef RUSHPRIORITYDECORATOR_H
#define RUSHPRIORITYDECORATOR_H

#include "Decorator.h"

// Marks a component (typically a Shot) as rush priority.
class RushPriorityDecorator : public Decorator {
public:
    explicit RushPriorityDecorator(WorkComponent* component);

    virtual void execute() override;
    virtual void print(int indent = 0) const override;
    virtual double computeCost() const override;
};

#endif // RUSHPRIORITYDECORATOR_H
