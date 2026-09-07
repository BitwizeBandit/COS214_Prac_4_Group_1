#ifndef WORKCOMPONENT_H
#define WORKCOMPONENT_H

#include <string>

// Component participant, shared by the Composite AND Decorator
// patterns. Every leaf (Shot), composite (ProductionUnit), and
// decorator (Decorator and its subclasses) implements this SAME
// interface, which is what lets a client treat all of them the same
// way and lets a Decorator wrap any of them interchangeably.
//
// Rule 7 reminder: client code must never reach past this interface
// to grab a composite's internal container directly - traversal goes
// through a WorkIterator instead (see iterator/WorkIterator.h).
class WorkComponent {
public:
    virtual ~WorkComponent() {}

    // Performs this component's core action for the current demo
    // scenario (your choice what this means, as long as a composite's
    // execute() meaningfully involves its children rather than doing
    // nothing).
    virtual void execute() = 0;

    // Prints a human-readable description of this component.
    // 'indent' lets composites print nested children with visual
    // indentation (e.g. two spaces per level).
    virtual void print(int indent = 0) const = 0;

    virtual std::string getName() const = 0;

    // Leaf: its own cost. Composite: sum of its children's costs.
    // Decorator: its own added cost plus the wrapped component's cost.
    virtual double computeCost() const = 0;

    // Used by VFXPendingIterator. Defaults to false; Shot overrides it
    // with its real flag, Decorator forwards it to the component it
    // wraps.
    virtual bool isWaitingOnVFX() const { return false; }
};

#endif // WORKCOMPONENT_H
