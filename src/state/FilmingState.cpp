#include "state/FilmingState.h"
#include "state/InReviewState.h"
#include "composite/Shot.h"

void FilmingState::submitForReview(Shot* shot) {
    
    shot->setState(new InReviewState());
}

std::string FilmingState::describe() const {
    
    return "Filming";
}
