#ifndef INREVIEWSTATE_H
#define INREVIEWSTATE_H

#include "ShotState.h"

// Both approve() and reject() are valid from here - this is the
// branch point for the reshoot loop.
class InReviewState : public ShotState {
public:
    virtual void approve(Shot* shot) override;
    virtual void reject(Shot* shot) override;
    virtual std::string describe() const override;
};

#endif // INREVIEWSTATE_H
