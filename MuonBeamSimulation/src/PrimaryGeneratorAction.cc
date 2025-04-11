#include "PrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Event.hh"
#include "G4ThreeVector.hh"
#include "TrackingAction.hh" 
#include "G4RunManager.hh" 
#include <cmath>

PrimaryGeneratorAction::PrimaryGeneratorAction() {
    fParticleGun = new G4ParticleGun(1);
    G4ParticleDefinition* muon = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
    fParticleGun->SetParticleDefinition(muon);
    fParticleGun->SetParticleEnergy(2.5 * GeV);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction() {
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    const G4double radius = 5.0 * m;  

    for (int thetaDeg = 0; thetaDeg < 180; thetaDeg += 5) {  
        for (int phiDeg = 0; phiDeg < 360; phiDeg += 5) {  
            G4double theta = thetaDeg * deg;  
            G4double phi = phiDeg * deg;

            
            G4double x = radius * std::sin(theta) * std::cos(phi);
            G4double y = radius * std::sin(theta) * std::sin(phi);
            G4double z = radius * std::cos(theta);

            G4ThreeVector position(x, y, z);
            G4ThreeVector direction = -position.unit();  

            fParticleGun->SetParticlePosition(position);
            fParticleGun->SetParticleMomentumDirection(direction);
            fParticleGun->GeneratePrimaryVertex(event);
        }
    }
}

