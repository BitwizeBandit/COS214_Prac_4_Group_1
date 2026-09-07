#ifndef STORYBOARDEDSTATE_H
#define STORYBOARDEDSTATE_H

#include "ShotState.h"

// Only film() is valid from here.
class StoryboardedState : public ShotState {
public:
    virtual void film(Shot* shot) override;
    virtual std::string describe() const override;
};

#endif // STORYBOARDEDSTATE_H
