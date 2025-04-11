#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class SteppingAction : public G4UserSteppingAction {
public:
    SteppingAction();
    ~SteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif
