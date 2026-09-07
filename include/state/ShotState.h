#ifndef SHOTSTATE_H
#define SHOTSTATE_H

#include <string>

class Shot;

// State participant. Each concrete state overrides ONLY the
// transition(s) that are valid FROM that state. The default bodies
// (see ShotState.cpp) handle the "invalid transition" case so
// concrete states don't all have to repeat that logic.
class ShotState {
public:
    virtual ~ShotState() {}

    virtual void film(Shot* shot);
    virtual void submitForReview(Shot* shot);
    virtual void approve(Shot* shot);
    virtual void reject(Shot* shot);

    virtual std::string describe() const = 0;
};

#endif // SHOTSTATE_H
