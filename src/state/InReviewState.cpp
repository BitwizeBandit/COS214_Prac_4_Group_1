#include "state/InReviewState.h"
#include "state/ApprovedState.h"
#include "state/FilmingState.h"
#include "composite/Shot.h"

void InReviewState::approve(Shot* shot) {
    // TODO: shot->setState(new ApprovedState());
    shot->setState(new ApprovedState());
}

void InReviewState::reject(Shot* shot) {
    // TODO: this is the reshoot loop - shot->setState(new FilmingState());
    shot->setState(new FilmingState());

}

std::string InReviewState::describe() const {
    // TODO: return "In Review"
    return "In Review";
}
