// Concrete Iterator
#include "iterator/VFXPendingIterator.h"
#include "composite/ProductionUnit.h"

VFXPendingIterator::VFXPendingIterator(ProductionUnit* root) : root(root), current(nullptr) {}

void VFXPendingIterator::first() 
{
    // reseting frameStack to just {root, 0}, set current to nullptr, then call advanceToNextMatch() to land on the first
    // matching component (if any)

    frameStack.clear();
    if (root != nullptr) 
    {
        frameStack.push_back(std::make_pair(root, static_cast<std::size_t>(0)));
    }
    current = nullptr;
    advanceToNextMatch();
}

void VFXPendingIterator::next() {
    // call advanceToNextMatch() again to move past 'current' and land on the next match

    advanceToNextMatch();
}

void VFXPendingIterator::advanceToNextMatch() {
    //  pop/push frames on frameStack to walk the live tree
    // depth-first (reading unit->children fresh each time: we do NOt cache a copy anywhere), 
    // checking each WorkComponent's isWaitingOnVFX()
    // Stop as soon as we find a match and store it in 'current'; if we run out of tree, set current to nullptr

        while (!frameStack.empty()) {
        ProductionUnit* unit = frameStack.back().first;
        std::size_t idx = frameStack.back().second;

        if (idx >= unit->children.size()) {
            frameStack.pop_back(); // backtrack: this unit is exhausted
            continue;
        }

        WorkComponent* child = unit->children[idx];
        // Advance this frame's cursor by direct index assignment  BEFORE any push_back below, push_back can reallocate
        // frameStack's storage, which would invalidate a held
        // reference. Writing by index sidesteps that entirely
        frameStack.back().second = idx + 1;

        ProductionUnit* nested = dynamic_cast<ProductionUnit*>(child);
        if (nested != nullptr) {
            // Depth first: explore this nested unit's children before this frame's remaining siblings
            frameStack.push_back(std::make_pair(nested, static_cast<std::size_t>(0)));
        }

        if (child->isWaitingOnVFX()) {
            current = child;
            return;
        }
    }
    current = nullptr;
}

bool VFXPendingIterator::isDone() const {
    return current == nullptr;
}

WorkComponent* VFXPendingIterator::currentItem() const 
{
    return current;
}
