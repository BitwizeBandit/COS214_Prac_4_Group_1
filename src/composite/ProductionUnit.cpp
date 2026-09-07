#include "composite/ProductionUnit.h"
#include "iterator/FullTraversalIterator.h"
#include "iterator/VFXPendingIterator.h"
#include <iostream>

ProductionUnit::ProductionUnit(const std::string& name, const std::string& unitType)
    : name(name), unitType(unitType) {}

ProductionUnit::~ProductionUnit() 
{
    // deleting every WorkComponent* still in 'children' 
    // (this ProductionUnit owns them- see the header comment and design
    // doc S4), then clear the vector

    for (WorkComponent* child : children) 
    {
        delete child;
    }
    children.clear();

}

void ProductionUnit::add(WorkComponent* component) 
{
    children.push_back(component);
}

void ProductionUnit::remove(WorkComponent* component) 
{
    // finding the 'component' in 'children' and erase it WITHOUT
    // deleting it (ownership passes to the caller: see header comment)
    // std::find + vector::erase, or std::remove + erase, both work fine here

    for (auto it = children.begin(); it != children.end(); ++it) 
    {
        if (*it == component) 
        {
            children.erase(it); // only remove from vector
            return;
        }
    }
}

//-----------------------------------------Iterator "factory method" hook 
WorkIterator* ProductionUnit::createIterator(IteratorType type) 
{
    // returning `new FullTraversalIterator(this)` or `new VFXPendingIterator(this)` depending on 'type' that the client chose
    
    switch (type) 
    {
        case IteratorType::FULL_TRAVERSAL:
            return new FullTraversalIterator(this); //  pick which Concr Iterator to hand back

        case IteratorType::VFX_PENDING:
            return new VFXPendingIterator(this);
    }

    return nullptr;
}

void ProductionUnit::execute() 
{
    //  do this unit's own work (if any), then call execute() on every child in 'children'

    std::cout << "[" << unitType << "] " << name << " is coordinating its work..." << std::endl;
    for (WorkComponent* child : children) 
    {
        child->execute();
    }
   
}

void ProductionUnit::print(int indent) const 
{
    // also print name/unitType nicely and recurse into children with an increased indent so nesting is visible in the output

    std::cout << std::string(static_cast<size_t>(indent) * 2, ' ')  << unitType << ": " << name << std::endl;

    for (const WorkComponent* child : children) {
        child->print(indent + 1);
    }
}

std::string ProductionUnit::getName() const 
{
    return name;
}

double ProductionUnit::computeCost() const 
{
    //  Summing computeCost() across every child
     double total = 0.0;

    for (const WorkComponent* child : children) 
    {
        total += child->computeCost();
    }
    
    return total;
}

const std::string& ProductionUnit::getUnitType() const {
    return unitType;
}
