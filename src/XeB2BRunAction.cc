#include "XeB2BRunAction.hh"

#include "XeB2BDetectorConstruction.hh"
#include "XeB2BPrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4EmCalculator.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include <iomanip>
#include "XeB2BOutput.hh"
extern G4double sum_initial_E;
extern XeB2BOutput rootOutput;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BRunAction::XeB2BRunAction(XeB2BDetectorConstruction* det, XeB2BPrimaryGeneratorAction* prim)
: detector(det), primary(prim),itstotcoll1_edep(0.),itstotcoll1_edep2(0.),
itstotcoll2_edep(0.),itstotcoll2_edep2(0.),
nb_coll1_edep(0),nb_coll2_edep(0),countkiller(0)
{
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BRunAction::~XeB2BRunAction()
{ 
	G4cout << " XeB2B run action is deleted "  << G4endl; 
	G4cout << countkiller << " e- after the magnet have been killed" << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BRunAction::BeginOfRunAction(const G4Run* aRun)
{  
	G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void XeB2BRunAction::EndOfRunAction(const G4Run* aRun)
{
	
	Char_t temp[1024];
}
