#include "state/FilmingState.h"
#include "state/InReviewState.h"
#include "composite/Shot.h"

void FilmingState::submitForReview(Shot* shot) {
    // TODO: shot->setState(new InReviewState());
    shot->setState(new InReviewState());
}

std::string FilmingState::describe() const {
    // TODO: return "Filming"
    return "Filming";
}
