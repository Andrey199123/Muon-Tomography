#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include <fstream>

SteppingAction::SteppingAction() {
    std::ofstream outFile("stepData.csv");
    outFile << "TrackID,StepNumber,PosX(mm),PosY(mm),PosZ(mm),KineticEnergy(MeV)" << std::endl;
    outFile.close();
}

SteppingAction::~SteppingAction() {}

void SteppingAction::UserSteppingAction(const G4Step* step) {
    G4Track* track = step->GetTrack();
    G4int trackID = track->GetTrackID();
    G4int stepNum = track->GetCurrentStepNumber();

    G4ThreeVector pos = step->GetPreStepPoint()->GetPosition();
    G4double energy = step->GetPreStepPoint()->GetKineticEnergy();

    std::ofstream outFile("stepData.csv", std::ios::app);
    outFile << trackID << "," << stepNum << ","
            << pos.x() / mm << "," << pos.y() / mm << "," << pos.z() / mm << ","
            << energy / MeV << std::endl;
    outFile.close();
}
