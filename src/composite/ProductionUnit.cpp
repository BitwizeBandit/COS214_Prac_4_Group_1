#include "composite/ProductionUnit.h"
#include "iterator/FullTraversalIterator.h"
#include "iterator/VFXPendingIterator.h"
#include <iostream>

ProductionUnit::ProductionUnit(const std::string& name, const std::string& unitType)
    : name(name), unitType(unitType) {}

ProductionUnit::~ProductionUnit() {
    // TODO: delete every WorkComponent* still in 'children' (this
    // ProductionUnit owns them - see the header comment and design
    // doc S4), then clear the vector. Follow the pattern from the
    // Ch.11 IntermediateNode destructor.
}

void ProductionUnit::add(WorkComponent* component) {
    // TODO: push_back onto 'children'.
}

void ProductionUnit::remove(WorkComponent* component) {
    // TODO: find 'component' in 'children' and erase it WITHOUT
    // deleting it (ownership passes to the caller - see header
    // comment). std::find + vector::erase, or std::remove + erase,
    // both work fine here.
}

WorkIterator* ProductionUnit::createIterator(IteratorType type) {
    // TODO: return `new FullTraversalIterator(this)` or
    // `new VFXPendingIterator(this)` depending on 'type'. This is the
    // textbook Iterator "factory method" hook (see L15 S15.2.4/S15.4.5).
    return nullptr;
}

void ProductionUnit::execute() {
    // TODO: do this unit's own work (if any), then call execute() on
    // every child in 'children'. Looping over your OWN private
    // container from inside your OWN method is fine - rule 7 is about
    // CLIENT code reaching in from outside, not this.
}

void ProductionUnit::print(int indent) const {
    // TODO: also print name/unitType nicely and recurse into children
    // with an increased indent so nesting is visible in the output.
    std::cout << std::string(static_cast<size_t>(indent) * 2, ' ')
              << unitType << ": " << name << std::endl;
}

std::string ProductionUnit::getName() const {
    return name;
}

double ProductionUnit::computeCost() const {
    // TODO: sum computeCost() across every child.
    return 0.0;
}

const std::string& ProductionUnit::getUnitType() const {
    return unitType;
}
