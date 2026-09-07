#include "composite/Shot.h"
#include "state/ShotState.h"
#include "state/StoryboardedState.h"
#include <iostream>

Shot::Shot(const std::string& name, bool needsVFX)
    : name(name), state(new StoryboardedState()), needsVFX(needsVFX) {}

Shot::~Shot() {
    // TODO: delete 'state' (Shot owns it - see design doc S4).
    delete state;
}

void Shot::film() {
    // TODO: delegate to state->film(this).
    state->film(this);
}

void Shot::submitForReview() {
    // TODO: delegate to state->submitForReview(this).
    state->submitForReview(this);
}

void Shot::approve() {
    // TODO: delegate to state->approve(this).
    state->approve(this);
}

void Shot::reject() {
    // TODO: delegate to state->reject(this).
    state->reject(this);
}

void Shot::setState(ShotState* newState) {
    // TODO: delete the old 'state' (see the ownership note in the
    // header), then point 'state' at 'newState'.
    delete state;
    state = newState;
}

void Shot::setNeedsVFX(bool waiting) {
    needsVFX = waiting;
}

void Shot::execute() {
    // TODO: whatever "doing a day's work on this shot" means for your
    // demo - e.g. print its name and current state description.
}

void Shot::print(int indent) const {
    // TODO: also print state->describe() and whether needsVFX is set.
    std::cout << std::string(static_cast<size_t>(indent) * 2, ' ')
              << "Shot: " << name 
              <<" | State: "<< state->describe() << std::endl;
              
}

std::string Shot::getName() const {
    return name;
}

double Shot::computeCost() const {
    // TODO: return this shot's own base cost.
    return 0.0;
}

bool Shot::isWaitingOnVFX() const {
    return needsVFX;
}
