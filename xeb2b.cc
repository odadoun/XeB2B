#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#if defined(G4UI_USE_QT)
#include "G4UIQt.hh"
#include "G4Qt.hh"
#endif
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "XeB2BDetectorConstruction.hh"
#include "XeB2BPhysicsList.hh"
#include "XeB2BPrimaryGeneratorAction.hh"
#include "XeB2BOutput.hh"
#include "XeB2BRunAction.hh"
#include "XeB2BEventAction.hh"
#include "XeB2BSteppingAction.hh"
XeB2BOutput rootOutput;
G4int increment_collimator;
G4double collimator_depth;
int main(int argc,char** argv)
{

  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }
	// Construct the run manager
	//
	 /* to have the possibility to change seed */
  /*     G4long seed = time(NULL);
       if (seed == 0) seed = 1; // sécurité
       CLHEP::HepRandom::setTheSeed(seed);*/
	//G4long myseed = 12345;
     //if(argv[2]!=0) myseed=(G4long)atoi(argv[2]);
  //	 CLHEP::HepRandom::setTheSeed(seed);

	G4RunManager * runManager = new G4RunManager;

	XeB2BDetectorConstruction* det;
	runManager->SetUserInitialization(det = new XeB2BDetectorConstruction);

	G4VUserPhysicsList* physics;
	runManager->SetUserInitialization(physics = new XeB2BPhysicsList);

	XeB2BPrimaryGeneratorAction* prim;
        runManager->SetUserAction(prim = new XeB2BPrimaryGeneratorAction());

	XeB2BRunAction* run;
	runManager->SetUserAction(run = new XeB2BRunAction(det,prim));
  XeB2BEventAction* event;
	runManager->SetUserAction(event = new XeB2BEventAction(run));

	runManager->SetUserAction(new XeB2BSteppingAction(det,prim,run,event));
  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  rootOutput.Init();
  // Activate score ntuple writer
  // Process macro or start UI session
  //
  if ( ! ui ) {
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else {
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted
  // in the main() program !

  delete visManager;
  delete runManager;

	return 0;
}
