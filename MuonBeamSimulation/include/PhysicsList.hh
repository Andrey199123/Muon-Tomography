#ifndef PhysicsList_h
#define PhysicsList_h

#include "G4VModularPhysicsList.hh"

class PhysicsList : public G4VModularPhysicsList {
public:
    PhysicsList();
    ~PhysicsList();

    void ConstructParticle() override;
    void ConstructProcess() override;
};

#endif
