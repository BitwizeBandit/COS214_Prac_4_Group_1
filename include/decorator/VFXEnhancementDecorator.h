#ifndef VFXENHANCEMENTDECORATOR_H
#define VFXENHANCEMENTDECORATOR_H

#include "Decorator.h"

// Adds VFX enhancement work to a component. Consider overriding
// isWaitingOnVFX() too, so a shot wrapped in this decorator shows up
// on the VFX team's iterator by definition, even if the underlying
// Shot's own flag says otherwise.
class VFXEnhancementDecorator : public Decorator {
public:
    explicit VFXEnhancementDecorator(WorkComponent* component);

    virtual void execute() override;
    virtual void print(int indent = 0) const override;
    virtual double computeCost() const override;
    virtual bool isWaitingOnVFX() const override;
};

#endif // VFXENHANCEMENTDECORATOR_H
