#ifndef DECORATOR_H
#define DECORATOR_H

#include "WorkComponent.h"

// Decorator participant. Wraps exactly one WorkComponent, which may
// itself be a Shot, a ProductionUnit, or ANOTHER Decorator - that's
// what makes decorators stackable.
class Decorator : public WorkComponent {
public:
    explicit Decorator(WorkComponent* component);

    // Ownership: deletes 'component' (see design doc S4) - deleting
    // the outermost decorator in a stack cascades through the chain.
    virtual ~Decorator();

    // Default behaviour: delegate straight through. Concrete
    // decorators override these, add their own bit, and then call
    // through to keep the chain going (see Ch.12's
    // StateDecorator/BehaviourDecorator::print() for the shape of
    // this).
    virtual void execute() override;
    virtual void print(int indent = 0) const override;
    virtual std::string getName() const override;
    virtual double computeCost() const override;
    virtual bool isWaitingOnVFX() const override;

protected:
    WorkComponent* component;
};

#endif // DECORATOR_H
