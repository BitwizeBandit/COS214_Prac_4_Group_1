#include <iostream>
#include <limits>
#include <string>

#include "composite/ProductionUnit.h"
#include "composite/Shot.h"
#include "decorator/RushPriorityDecorator.h"
#include "decorator/StuntSafetyDecorator.h"
#include "decorator/VFXEnhancementDecorator.h"
#include "iterator/FullTraversalIterator.h"
#include "iterator/VFXPendingIterator.h"
#include "IteratorType.h"

// ---------------------------------------------------------------------
// DEMO_MODE controls ONLY presentation (section banners + a pause between scenarios so a live audience can follow along). 
// It never changes which pattern operations run or what gets built, the underlying behaviour is identical either way
//
//   1 = live demo build (verbose banners, pauses for pacing)
//   0 = FitchFork build (quiet, fully deterministic, never blocks waiting on stdin)
//
// We Set this to 0 before submitting to FitchFork
// ---------------------------------------------------------------------
#define DEMO_MODE 1

static void banner(const std::string& text) {
#if DEMO_MODE
    std::cout << "\n========== " << text << " ==========" << std::endl;
#else
    (void)text;
#endif
}

static void pauseForDemo() {
#if DEMO_MODE
    std::cout << "\n(press Enter to continue)" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
#endif
}

// ---------------------------------------------------------------------
// Builds the shared production tree used by both scenarios.
//
//   Midnight Run (Production)              <- root
//     Camera (Department)                  <- level 1 below root
//       Rooftop Chase (Scene)              <- level 2 below root
//         Wide establishing shot           <- level 3 below root (leaf)
//         Hero jumps gap  (Rush + Stunt Safety stacked)
//     VFX (Department)
//       Explosion Sequence (Scene)
//         Building explosion   (needsVFX = true from construction)
//         Debris cleanup shot
//
// Composite requirement (rule 6): 3 levels of nesting below the
// root/client boundary, mixing individual Shots and nested
// ProductionUnits.
// ---------------------------------------------------------------------
static ProductionUnit* buildProductionTree(Shot*& heroJump, Shot*& explosionShot, Shot*& debrisShot,
                                            ProductionUnit*& rooftopSceneOut, ProductionUnit*& explosionSceneOut) {
    ProductionUnit* production = new ProductionUnit("Midnight Run", "Production");

    ProductionUnit* cameraDept = new ProductionUnit("Camera", "Department");
    ProductionUnit* rooftopScene = new ProductionUnit("Rooftop Chase", "Scene");
    Shot* wideShot = new Shot("Wide establishing shot");
    heroJump = new Shot("Hero jumps gap");

    // Decorator applied BEFORE the shot enters the tree: from here on,
    // the composite and both iterators only ever see the decorated
    // version. We keep our own 'heroJump' pointer on the side purely
    // so main() can still call Shot-specific lifecycle methods
    // (film(), approve(), ...) - those aren't part of the generic
    // WorkComponent interface, so a concrete handle is needed for them
    // regardless of how the object is stored in the tree.
    WorkComponent* heroJumpDecorated = new StuntSafetyDecorator(new RushPriorityDecorator(heroJump));

    rooftopScene->add(wideShot);
    rooftopScene->add(heroJumpDecorated);
    cameraDept->add(rooftopScene);

    ProductionUnit* vfxDept = new ProductionUnit("VFX", "Department");
    ProductionUnit* explosionScene = new ProductionUnit("Explosion Sequence", "Scene");
    explosionShot = new Shot("Building explosion", true);
    debrisShot = new Shot("Debris cleanup shot");
    explosionScene->add(explosionShot);
    explosionScene->add(debrisShot);
    vfxDept->add(explosionScene);

    production->add(cameraDept);
    production->add(vfxDept);

    rooftopSceneOut = rooftopScene;
    explosionSceneOut = explosionScene;
    return production;
}

// ---------------------------------------------------------------------
// Scenario A: Daily production meeting.
//   - Composite: uniform print()/computeCost() across the whole tree
//   - Decorator: a stacked (Rush + Stunt Safety) shot participates normally in that same traversal, through the same interface.
//   - Iterator #1: FullTraversalIterator walks everything, for the
//                 report, a real "visit the complete structure" traversal
//   - State: a shot is driven through valid transitions, and one invalid transition is attempted and rejected 
//            (not silently accepted, not a crash)
// ---------------------------------------------------------------------
static void runDailyMeetingScenario(ProductionUnit* production, Shot* heroJump) {
    banner("Scenario A: Daily production meeting");

    std::cout << "-- Nested tree view (ProductionUnit::print(), called once on the root) --" << std::endl;
    production->print(0);

    std::cout << "\n-- Running execute() across the whole tree --" << std::endl;
    production->execute();

    std::cout << "\n-- Flat full script report (FullTraversalIterator - every node, once each) --" << std::endl;
    WorkIterator* reportIt = production->createIterator(IteratorType::FULL_TRAVERSAL);
    for (reportIt->first(); !reportIt->isDone(); reportIt->next()) {
        std::cout << "  - " << reportIt->currentItem()->getName() << std::endl;
    }
    delete reportIt;

    std::cout << "\nTotal estimated cost so far: " << production->computeCost() << std::endl;

    std::cout << "\n-- Driving 'Hero jumps gap' through its lifecycle --" << std::endl;
    heroJump->film();
    heroJump->print(0);
    heroJump->submitForReview();
    heroJump->print(0);
    heroJump->approve();
    heroJump->print(0);

    std::cout << "\n-- Attempting an invalid transition (approve() while still Storyboarded) --" << std::endl;
    Shot invalidTest("Rejected test shot");
    invalidTest.approve(); // must be rejected, not silently succeed or crash

    pauseForDemo();
}

// ---------------------------------------------------------------------
// Scenario B: Reshoot crisis.
//   - State: the reshoot loop (InReview --reject()--> Filming).
//   - Iterator #2: VFXPendingIterator, LIVE - proven by flipping a
//                flag on a shot the iterator hasn't reached yet, and watching it
//                 get picked up on the very next step of the SAME iterator.
//   - Independent traversals: a FullTraversalIterator and a
//                             VFXPendingIterator are alive over the SAME tree at once

//   - Structural change #1: an item is moved between groups at
//                                                           runtime via remove()/add().
//   - Structural change #2: a brand-new item is added AFTER a
//                          FullTraversalIterator's snapshot was already taken, proving it
//                          does NOT reflect the change
// ---------------------------------------------------------------------
static void runReshootCrisisScenario(ProductionUnit* production, ProductionUnit* rooftopScene,
     ProductionUnit* explosionScene, Shot* debrisShot) 
    {

    banner("Scenario B: Reshoot crisis");

    std::cout << "-- Debris cleanup shot goes through review and fails (reshoot loop) --" << std::endl;
    debrisShot->film();
    debrisShot->submitForReview();
    debrisShot->reject(); // InReview -> Filming: the reshoot loop
    debrisShot->print(0);

    std::cout << "\n-- After the reshoot, resubmitting and getting approved this time --" << std::endl;
    debrisShot->submitForReview();
    debrisShot->approve();
    debrisShot->print(0);

    std::cout << "\n-- Two independent iterators over the SAME tree, interleaved --" << std::endl;
    WorkIterator* liveVfxIt = production->createIterator(IteratorType::VFX_PENDING);
    WorkIterator* freshReportIt = production->createIterator(IteratorType::FULL_TRAVERSAL);

    liveVfxIt->first();
    std::cout << "VFX-pending iterator, first match: "
              << (liveVfxIt->isDone() ? "(none yet)" : liveVfxIt->currentItem()->getName()) << std::endl;

    freshReportIt->first();
    std::cout << "Full-traversal iterator, first item: " << freshReportIt->currentItem()->getName() << std::endl;
    freshReportIt->next(); // proves this iterator has its own independent position

    std::cout << "\n-- Mid-crisis: debris shot now ALSO needs VFX cleanup work --" << std::endl;
    debrisShot->setNeedsVFX(true); // a live, in-flight behavioural change

    liveVfxIt->next();
    std::cout << "VFX-pending iterator, next match (should now include debris shot): "
              << (liveVfxIt->isDone() ? "(none)" : liveVfxIt->currentItem()->getName()) << std::endl;
    delete liveVfxIt;

    std::cout << "\n-- Structural change: moving 'Debris cleanup shot' to a different scene --" << std::endl;
    explosionScene->remove(debrisShot);
    WorkComponent* debrisWithVFX = new VFXEnhancementDecorator(debrisShot);
    rooftopScene->add(debrisWithVFX);
    std::cout << "Moved 'Debris cleanup shot' from Explosion Sequence to Rooftop Chase (now with VFX enhancement)." << std::endl;

    std::cout << "\n-- Debris cleanup shot's own updated info (proving the VFX decorator is genuinely active) --" << std::endl;
    debrisWithVFX->print(0);
    debrisWithVFX->execute();

    std::cout << "\n-- Structural change: a brand-new shot is added AFTER freshReportIt's snapshot was taken --" << std::endl;
    Shot* pickupShot = new Shot("Pickup insert shot");
    explosionScene->add(pickupShot);
    std::cout << "Added new shot: Pickup insert shot." << std::endl;

    std::cout << "\nfreshReportIt keeps walking its ORIGINAL snapshot - the new shot will NOT appear:" << std::endl;
    for (; !freshReportIt->isDone(); freshReportIt->next()) {
        std::cout << "  - " << freshReportIt->currentItem()->getName() << std::endl;
    }
    delete freshReportIt;

    std::cout << "\nA BRAND NEW FullTraversalIterator sees the current, updated tree instead:" << std::endl;
    WorkIterator* updatedReportIt = production->createIterator(IteratorType::FULL_TRAVERSAL);
    for (updatedReportIt->first(); !updatedReportIt->isDone(); updatedReportIt->next()) {
        std::cout << "  - " << updatedReportIt->currentItem()->getName() << std::endl;
    }
    delete updatedReportIt;

    std::cout << "\nUpdated total cost after Scenario B's changes: " << production->computeCost() << std::endl;

    pauseForDemo();
}

int main() 
{
    std::cout << "TaskForge -- Movie Studio Edition" << std::endl;

    Shot* heroJump = nullptr;
    Shot* explosionShot = nullptr;
    Shot* debrisShot = nullptr;
    ProductionUnit* rooftopScene = nullptr;
    ProductionUnit* explosionScene = nullptr;
    ProductionUnit* production = buildProductionTree(heroJump, explosionShot, debrisShot, rooftopScene, explosionScene);

    runDailyMeetingScenario(production, heroJump);
    runReshootCrisisScenario(production, rooftopScene, explosionScene, debrisShot);

    std::cout << "\nShutting down - deleting the production tree cascades through everything it owns." << std::endl;
    delete production;

    return 0;
}