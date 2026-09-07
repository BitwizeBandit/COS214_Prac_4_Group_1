#include "state/InReviewState.h"
#include "state/ApprovedState.h"
#include "state/FilmingState.h"
#include "composite/Shot.h"

void InReviewState::approve(Shot* shot) {
  
    shot->setState(new ApprovedState());
}

void InReviewState::reject(Shot* shot) {
 
    shot->setState(new FilmingState());

}

std::string InReviewState::describe() const {
    
    return "In Review";
}
