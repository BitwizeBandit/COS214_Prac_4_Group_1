#include "iterator/FullTraversalIterator.h"
#include "composite/ProductionUnit.h"

FullTraversalIterator::FullTraversalIterator(ProductionUnit* root) : position(0) {
    // TODO: call buildSnapshot(root) here so 'snapshot' is ready
    // before first() is ever called.
}

void FullTraversalIterator::buildSnapshot(ProductionUnit* unit) 
{
    // TODO: this class is a friend of ProductionUnit, so you can read
    // unit->children directly. For each child:
    //   1. push it into 'snapshot'
    //   2. if the child is itself a ProductionUnit (check with
    //      dynamic_cast<ProductionUnit*>), recurse:
    //      buildSnapshot(childAsUnit)
    // This is one of the few reasonable places for a cast like this -
    // it's internal to the iterator's own recursive-descent logic, not
    // client code substituting a type check for polymorphism (that's
    // what rule 8 actually forbids).
}

void FullTraversalIterator::first() {
    position = 0;
}

void FullTraversalIterator::next() {
    // TODO: ++position
}

bool FullTraversalIterator::isDone() const {
    // TODO: return position >= snapshot.size()
    return true;
}

WorkComponent* FullTraversalIterator::currentItem() const 
{
    // TODO: return snapshot[position] if not done, else nullptr
    return nullptr;
}
