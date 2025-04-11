#include "PhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4HadronElasticPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "G4StoppingPhysics.hh"
#include "G4IonPhysics.hh"

PhysicsList::PhysicsList() {
    SetDefaultCutValue(1.0 * mm);
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronElasticPhysics());
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());
    RegisterPhysics(new G4StoppingPhysics());
    RegisterPhysics(new G4IonPhysics());
}

PhysicsList::~PhysicsList() {}

void PhysicsList::ConstructParticle() {
    G4VModularPhysicsList::ConstructParticle();
}

void PhysicsList::ConstructProcess() {
    G4VModularPhysicsList::ConstructProcess();
}
