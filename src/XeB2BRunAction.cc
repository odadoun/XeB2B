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
	G4cout << " ### Run " << aRun->GetRunID() << " end" << G4endl;
	G4double edep_mean1 = GetColl1EDep() / nb_coll1_edep;
	G4double edep_mean2 = GetColl2EDep() / nb_coll2_edep;
	G4double edep_mean3 = GetColl3EDep() / nb_coll3_edep;
	
	G4double rms1 =  (GetColl1EDep2()/nb_coll1_edep - edep_mean1*edep_mean1);
	G4double rms2 =  (GetColl2EDep2()/nb_coll2_edep - edep_mean2*edep_mean2);
	G4double rms3 =  (GetColl3EDep2()/nb_coll3_edep - edep_mean3*edep_mean2);
	
	G4cout << " Deposited energies on Coll1 " << GetColl1EDep() / MeV << " MeV +- " << rms1 / MeV << G4endl;
	G4cout << " Deposited energies on Coll2 " << GetColl2EDep() / MeV << " MeV +- " << rms2 / MeV  << G4endl;
	G4cout << " Deposited energies on Coll2 " << GetColl3EDep() / MeV << " MeV +- " << rms3 / MeV  << G4endl;
	G4cout << " ########################### " << G4endl;
	
	
	Char_t temp[1024];
	if((rootOutput.rootFile)->IsOpen())
	{
	sprintf(temp,	"\n#################################################################\n\
			#  Deposited energies on Coll1 %f +- %f MeV #\n\
			#  Deposited energies on Coll2 %f +- %f MeV #\n\
			#  Deposited energies on Coll3 %f +- %f MeV #\n\
		        ################################################################\n",
				  GetColl1EDep() / MeV, rms1 / MeV, GetColl2EDep() / MeV , rms2 / MeV , GetColl3EDep() / MeV , rms3 / MeV);
			      (rootOutput.rootFile)->WriteObject((rootOutput.header), temp);
	}
}
