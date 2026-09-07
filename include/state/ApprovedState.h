#ifndef APPROVEDSTATE_H
#define APPROVEDSTATE_H

#include "ShotState.h"

// Terminal state - no valid transitions out. All four transition
// methods fall back to ShotState's default "invalid transition"
// behaviour, so nothing needs to be overridden here except describe().
class ApprovedState : public ShotState {
public:
    virtual std::string describe() const override;
};

#endif // APPROVEDSTATE_H
