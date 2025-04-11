#ifndef EventAction_h
#define EventAction_h

#include "G4UserEventAction.hh"

class EventAction : public G4UserEventAction {
public:
    EventAction();
    ~EventAction();

    void EndOfEventAction(const G4Event*) override;
};

#endif
