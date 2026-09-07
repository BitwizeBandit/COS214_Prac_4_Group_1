#ifndef FILMINGSTATE_H
#define FILMINGSTATE_H

#include "ShotState.h"

// Only submitForReview() is valid from here.
class FilmingState : public ShotState {
public:
    virtual void submitForReview(Shot* shot) override;
    virtual std::string describe() const override;
};

#endif // FILMINGSTATE_H
