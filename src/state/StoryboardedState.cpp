#include "state/StoryboardedState.h"
#include "state/FilmingState.h"
#include "composite/Shot.h"

void StoryboardedState::film(Shot* shot) {
    
    shot->setState(new FilmingState());
}

std::string StoryboardedState::describe() const {
    
    return "Storyboarded";
}
