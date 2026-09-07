#ifndef VFXPENDINGITERATOR_H
#define VFXPENDINGITERATOR_H

#include <vector>
#include <cstddef>
#include <utility>
#include "WorkIterator.h"

class ProductionUnit;
class WorkComponent;

// Concrete Iterator
// LIVE traversal. Unlike FullTraversalIterator, this does not copy anything at construction: 
// each first()/next() call walks the real
// tree by reading each ProductionUnit's children fresh. 
// Onlyccomponents whose isWaitingOnVFX() is currently true are surfaced


// Safety rule: a Shot may be MOVED between units while this iterator is active, 
// but must not be DELETED from the tree while a live  iterator could still reference it

class VFXPendingIterator : public WorkIterator 
{
    public:
        explicit VFXPendingIterator(ProductionUnit* root);

        virtual void first() override;
        virtual void next() override;
        virtual bool isDone() const override;
        virtual WorkComponent* currentItem() const override;

    private:
        // Advances the internal position until it lands on a component
        // whose isWaitingOnVFX() is true, or runs out of tree
        void advanceToNextMatch();

        // A simple approach: a stack of (unit, next-child-index-to-try)
        // frames, so you can pause and resume a depth first walk one step
        // at a time without recursion. This class is a friend of ProductionUnit, so it can read 'children' directly : see the
        // friend declaration in composite/ProductionUnit.h.
        ProductionUnit* root;
        std::vector<std::pair<ProductionUnit*, std::size_t> > frameStack;
        WorkComponent* current;
};

#endif // VFXPENDINGITERATOR_H
