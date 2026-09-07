#include "state/StoryboardedState.h"
#include "state/FilmingState.h"
#include "composite/Shot.h"

void StoryboardedState::film(Shot* shot) {
    // TODO: shot->setState(new FilmingState());
    shot->setState(new FilmingState());
}

std::string StoryboardedState::describe() const {
    // TODO: return "Storyboarded"
    return "Storyboarded";
}
