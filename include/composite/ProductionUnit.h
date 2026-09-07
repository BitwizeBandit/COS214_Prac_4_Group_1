#ifndef PRODUCTIONUNIT_H
#define PRODUCTIONUNIT_H

#include <string>
#include <vector>
#include "WorkComponent.h"
#include "IteratorType.h"

class WorkIterator;
class FullTraversalIterator;
class VFXPendingIterator;

// Composite participant. A ProductionUnit can hold OTHER
// ProductionUnits and/or Shot leaves, to any depth, this is what
// gives the hierarchy genuine recursion instead of a fixed number of
// levels. 'unitType' is just a label (ex: "Production", "Department", Scene") so the 
// SAME class can represent every level
class ProductionUnit : public WorkComponent 
{
    public:
        ProductionUnit(const std::string& name, const std::string& unitType);

        // Ownership: deletes every child still attached at destruction
        // time. Children removed earlier via remove()
        // are NOT deleted here, because remove() already handed ownership to whoever called it
        virtual ~ProductionUnit();

        // Ownership: this ProductionUnit takes ownership of 'component'.
        // Do not add the same raw pointer to more than one ProductionUnit
        // at the same time.
        void add(WorkComponent* component);

        // Detaches 'component' WITHOUT deleting it: the caller becomes
        // responsible for it (typically to add() it under a different
        // ProductionUnit right afterwards, ex moving a Shot to a new
        // scene). If 'component' is not a direct child, do nothing
        void remove(WorkComponent* component);

        // Iterator participant hook: hands back a NEW iterator without
        // ever exposing 'children' to the caller. Caller owns the
        // returned pointer and must delete it when done.
        WorkIterator* createIterator(IteratorType type);

        virtual void execute() override;
        virtual void print(int indent = 0) const override;
        virtual std::string getName() const override;
        virtual double computeCost() const override;

        const std::string& getUnitType() const;

    private:
        std::string name;
        std::string unitType;
        std::vector<WorkComponent*> children;

        // Only the concrete iterators may reach into 'children' directly 
        //  using a FRIEND class as one of the accepted ways for an iterator to access its aggregates elements. 
        // This is what keeps rule 7 satisfied: nobody else (least of all main.cpp)
        // can get at this container
        friend class FullTraversalIterator;
        friend class VFXPendingIterator;
};

#endif // PRODUCTIONUNIT_H
