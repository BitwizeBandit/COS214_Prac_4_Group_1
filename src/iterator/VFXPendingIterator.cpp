#include "iterator/VFXPendingIterator.h"
#include "composite/ProductionUnit.h"

VFXPendingIterator::VFXPendingIterator(ProductionUnit* root)
    : root(root), current(nullptr) {}

void VFXPendingIterator::first() {
    // TODO: reset frameStack to just {root, 0}, set current to
    // nullptr, then call advanceToNextMatch() to land on the first
    // matching component (if any).
}

void VFXPendingIterator::next() {
    // TODO: call advanceToNextMatch() again to move past 'current'
    // and land on the next match.
}

void VFXPendingIterator::advanceToNextMatch() {
    // TODO: pop/push frames on frameStack to walk the live tree
    // depth-first (reading unit->children fresh each time: we do NOt cache a copy anywhere), 
    // checking each WorkComponent's isWaitingOnVFX(). 
    // Stop as soon as you find a match and store it in 'current'; if you run out of tree, set current to nullptr.
}

bool VFXPendingIterator::isDone() const {
    // TODO: return current == nullptr
    return true;
}

WorkComponent* VFXPendingIterator::currentItem() const {
    return current;
}
