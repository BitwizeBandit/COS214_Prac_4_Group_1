// Concrete Iterator
#include "iterator/FullTraversalIterator.h"
#include "composite/ProductionUnit.h"

FullTraversalIterator::FullTraversalIterator(ProductionUnit* root) : position(0) 
{
    // calling buildSnapshot(root) here so 'snapshot' is ready before first() is ever called

    if (root != nullptr) {
        buildSnapshot(root);
    }
}

void FullTraversalIterator::buildSnapshot(ProductionUnit* unit) 
{
    // 'unit->children' is private -> this only compiles because ProductionUnit declares FullTraversalIterator as a friend
    for (WorkComponent* child : unit->children) 
    {
        snapshot.push_back(child);
        // this snapshot does NOT include the root itself, only  its descendants-> matches how the aggregate is treated as
        // the thing being iterated OVER, not one of its own items
        ProductionUnit* nested = dynamic_cast<ProductionUnit*>(child);
        if (nested != nullptr) {
            buildSnapshot(nested);
        }
    }
}

void FullTraversalIterator::first() {
    position = 0;
}

void FullTraversalIterator::next() {

    ++position;
}

bool FullTraversalIterator::isDone() const {
    
    return position >= snapshot.size();
}

WorkComponent* FullTraversalIterator::currentItem() const 
{
    // returning the snapshot[position] if not done, else nullptr
    if (isDone()) 
    {
        return nullptr;
    }

    return snapshot[position];
}
