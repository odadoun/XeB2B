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
	// Construct the run manager
	//
	 /* to have the possibility to change seed */
       G4long seed = time(NULL);
       if (seed == 0) seed = 1; // sécurité
       CLHEP::HepRandom::setTheSeed(seed);
	//G4long myseed = 12345;
     //if(argv[2]!=0) myseed=(G4long)atoi(argv[2]);
  	 CLHEP::HepRandom::setTheSeed(seed);

	G4RunManager * runManager = new G4RunManager;
   
	XeB2BDetectorConstruction* det;
	runManager->SetUserInitialization(det = new XeB2BDetectorConstruction);

	G4VUserPhysicsList* physics = new XeB2BPhysicsList;
	runManager->SetUserInitialization(physics);
	
	XeB2BPrimaryGeneratorAction* prim;
    runManager->SetUserAction(prim = new XeB2BPrimaryGeneratorAction());

	XeB2BRunAction* run;
	runManager->SetUserAction(run = new XeB2BRunAction(det,prim));
	XeB2BEventAction* event;
	runManager->SetUserAction(event = new XeB2BEventAction(run));
    
	runManager->SetUserAction(new XeB2BSteppingAction(det,prim,run,event));
    
#ifdef G4VIS_USE
	// Visualization manager
	//
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
#endif
    
	// Initialize G4 kernel
	//
	runManager->Initialize();
	
	// Get the pointer to the User Interface manager
	//
	G4UImanager* UI = G4UImanager::GetUIpointer();  
	
	rootOutput.Init();

	G4String    command = "/control/execute ";
	
	if (argc==2 || argc==3)   // Define UI session for interactive mode
	{
		G4UIsession* session=0;
		
		// G4UIterminal is a (dumb) terminal
		//
		G4String fileName = argv[1];
		if(fileName.find(".mac")!=G4String::npos) // From string funcition: If the content is not found, the member value npos is returned.
		{
#ifdef G4UI_USE_QT
			session = new G4UIQt(argc,argv);
#endif
			
#ifdef G4UI_USE_TCSH
			session = new G4UIterminal(new G4UItcsh);      
#else
			//   session = new G4UIterminal();
#endif   
			G4cout << " \n Run in visu mode ... \n" << G4endl;
			UI->ApplyCommand(command+fileName);
			session->SessionStart();
			delete session;
		}
		else 
		if(fileName.find(".in")!=G4String::npos) // From string funcition: If the content is not found, the member value npos is returned.
		{
			G4cout << " \n Run in batch mode ... \n" << G4endl;
			UI->ApplyCommand(command+fileName);
		}
		else {
			G4cerr << " \n Run aborted not visu file nor batch file, What do you want exactly ... \n" << G4endl;
			exit(1); 
		}
	}
	
	else {
        G4cerr << " \n Run aborted need an argument... \n" << G4endl;
        exit(1); 
	}      
	// Job termination
	// Free the store: user actions, physics_list and detector_description are
	//                 owned and deleted by the run manager, so they should not
	//                 be deleted in the main() program !
	
#ifdef G4VIS_USE
	delete visManager;
#endif
	delete runManager;
	//rootOutput.~XeB2BOutput();
	return 0;
}
