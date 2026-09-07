#include "composite/Shot.h"
#include "state/ShotState.h"
#include "state/StoryboardedState.h"
#include <iostream>

// a new Shot always starts life as Storyboarded: 
// this is the one place the initial state is chosen, matching our lifecycle described
// Storyboarded -> Filming -> In Review -> Approved
Shot::Shot(const std::string& name, bool needsVFX): name(name), state(new StoryboardedState()), needsVFX(needsVFX) {}

Shot::~Shot() {// Ownership: Shot owns whichever ShotState is current at the moment its destroyed 

    delete state;
}

// Each lifecycle action is a one line delegation to whichever ShotState object is current
void Shot::film() {
    
    state->film(this);
}

void Shot::submitForReview() 
{
    state->submitForReview(this);
}

void Shot::approve() 
{
    state->approve(this);
}

void Shot::reject() 
{
    state->reject(this);
}

// Called BY a ShotState subclass(State) bcs Shot acts as Context for State pattern
void Shot::setState(ShotState* newState) 
{
    // deleting the old 'state', then point 'state' at 'newState'
    delete state;
    state = newState;

}

void Shot::setNeedsVFX(bool waiting) {
    needsVFX = waiting;
}

// This call itself
// never changes state; only film(), submitForReview(), approve(), reject() do that, 
// via whichever concrete ShotState is current
void Shot::execute() {
    
    std::cout << "Working on shot \"" << name << "\" (" << state->describe() << ")";
    if (needsVFX) {
        std::cout << " [awaiting VFX]";
    }
    std::cout << std::endl;
}

void Shot::print(int indent) const {
    
    std::cout << std::string(static_cast<size_t>(indent) * 2, ' ') << "Shot: " << name << " [" << state->describe() << "]";

    if (needsVFX) {
        std::cout << " (VFX pending)";
    }
    std::cout << std::endl;
    
}

std::string Shot::getName() const {
    return name;
}

double Shot::computeCost() const {
    
    // is a reasonable starting point that still lets ProductionUnit::computeCost() sum meaningfully up the tree
    return 500.0;
}

bool Shot::isWaitingOnVFX() const {
    return needsVFX;
}
