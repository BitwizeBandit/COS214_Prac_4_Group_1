#ifndef SHOT_H
#define SHOT_H

#include <string>
#include "WorkComponent.h"

class ShotState;

// Leaf participant (Composite) AND Context participant (State). A
// Shot has no children, but it DOES have a lifecycle, delegated
// entirely to whichever ShotState object 'state' currently points to.
class Shot : public WorkComponent 
{
    public:
        explicit Shot(const std::string& name, bool needsVFX = false);

        // Ownership: Shot owns its ShotState and deletes it here (see
        // design doc S4).
        virtual ~Shot();

        // Lifecycle actions - each delegates to 'state'. Whatever the
        // current state does with an invalid call (e.g. approve() on a
        // Storyboarded shot) should be handled sensibly, not crash.
        void film();
        void submitForReview();
        void approve();
        void reject();

        // Called BY the ShotState classes (not by client code) to move
        // this shot to a new state object. Decide and document: does the
        // old state get deleted here, or does each state manage its own
        // lifetime? (Simplest: delete the old one here before swapping.)
        void setState(ShotState* newState);

        void setNeedsVFX(bool waiting);

        virtual void execute() override;
        virtual void print(int indent = 0) const override;
        virtual std::string getName() const override;
        virtual double computeCost() const override;
        virtual bool isWaitingOnVFX() const override;

    private:
        std::string name;
        ShotState* state;
        bool needsVFX;
};

#endif // SHOT_H
