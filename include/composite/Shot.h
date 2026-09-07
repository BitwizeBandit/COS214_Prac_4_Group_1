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

        // Ownership: Shot owns its ShotState and deletes it here 
        virtual ~Shot();

        // Lifecycle actions: each delegates to 'state'. Whatever the current state does 
        // with an invalid call (ex: approve() on a Storyboarded shot) is handled good, not crash
        void film();
        void submitForReview();
        void approve();
        void reject();

        // Called BY the ShotState classes to move this shot to a new state object
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
