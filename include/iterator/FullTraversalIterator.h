#ifndef FULLTRAVERSALITERATOR_H
#define FULLTRAVERSALITERATOR_H

#include <vector>
#include <cstddef>
#include "WorkIterator.h"

class ProductionUnit;
class WorkComponent;

// SNAPSHOT traversal (see design doc S4). Visits every WorkComponentcin the tree, depth first, 
// in the order captured at construction time
// Structural changes made to the tree AFTER construction will
// NOT be reflected: that trade off is what makes this one suitable for a stable "full script report"
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
