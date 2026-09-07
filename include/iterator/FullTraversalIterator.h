#ifndef FULLTRAVERSALITERATOR_H
#define FULLTRAVERSALITERATOR_H

#include <vector>
#include <cstddef>
#include "WorkIterator.h"

class ProductionUnit;
class WorkComponent;

// Concrete Iterator
// SNAPSHOT traversal. Visits every WorkComponent in the tree,
// depth first, in the order captured at construction time. 
// Structural changes made to the tree AFTER construction are NOT reflected,
// that trade off is what makes this one suitable for a stable "full script report". 
// Note: this class does NOT own anything in 'snapshot',
//  those are borrowed pointers into the live tree, owned by whichever ProductionUnit they actually belong to
class FullTraversalIterator : public WorkIterator 
{
    public:
        explicit FullTraversalIterator(ProductionUnit* root);

        virtual void first() override;
        virtual void next() override;
        virtual bool isDone() const override;
        virtual WorkComponent* currentItem() const override;

    private:
        void buildSnapshot(ProductionUnit* unit);

        std::vector<WorkComponent*> snapshot;
        std::size_t position;
};

#endif // FULLTRAVERSALITERATOR_H
