#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "XeB2BDetectorConstruction.hh"
#include "XeB2BPrimaryGeneratorAction.hh"
#include "XeB2BPhysicsList.hh"
#include "G4UIExecutive.hh"
#include "G4UIsession.hh"

int main(int argc, char** argv)
{
    // Run manager
    auto runManager = new G4RunManager;

    runManager->SetUserInitialization(new XeB2BDetectorConstruction());
    runManager->SetUserInitialization(new XeB2BPhysicsList());
    runManager->SetUserAction(new XeB2BPrimaryGeneratorAction());

    runManager->Initialize();

    // Visualisation
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    auto UImanager = G4UImanager::GetUIpointer();

    if (argc == 1) {
        // Mode interactif
        auto ui = new G4UIExecutive(argc, argv);

        UImanager->ApplyCommand("/control/execute vis.mac");

        ui->SessionStart();

        delete ui;
    }
    else {
        // Mode batch
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    delete visManager;
    delete runManager;

    return 0;
}
