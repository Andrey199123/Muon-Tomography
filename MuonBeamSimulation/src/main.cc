#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "ActionInitialization.hh"

int main(int argc, char** argv) {
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new PhysicsList());
    runManager->SetUserInitialization(new ActionInitialization());

    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    G4UImanager* uiManager = G4UImanager::GetUIpointer();

    if (argc == 1) {

        G4UIExecutive* ui = new G4UIExecutive(argc, argv);
        uiManager->ApplyCommand("/vis/open OGL"); 
        uiManager->ApplyCommand("/run/initialize");
        uiManager->ApplyCommand("/vis/drawVolume");
        uiManager->ApplyCommand("/vis/scene/add/trajectories");
        ui->SessionStart();
        delete ui;
    } else {

        uiManager->ApplyCommand("/run/beamOn 10");
    }

    // Clean up
    delete visManager;
    delete runManager;

    return 0;
}
