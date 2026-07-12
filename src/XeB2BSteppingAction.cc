//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
   XeB2BIM code.   
   dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "XeB2BSteppingAction.hh"
#include "XeB2BDetectorConstruction.hh"
#include "XeB2BPrimaryGeneratorAction.hh"
#include "XeB2BRunAction.hh"
#include "XeB2BEventAction.hh"
#include "G4RunManager.hh"
#include "G4PolarizationHelper.hh"
#include "G4UnitsTable.hh"
#include "G4StokesVector.hh"
#include "G4SystemOfUnits.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSteppingAction::XeB2BSteppingAction(XeB2BDetectorConstruction* det,
		XeB2BPrimaryGeneratorAction* prim, XeB2BRunAction* RunAct, XeB2BEventAction* EveAct)
:detector(det), primary(prim), runAction(RunAct),eventAction(EveAct),tot_coll1_edep(0.),tot_coll1_edep2(0.),
tot_coll2_edep(0.),tot_coll2_edep2(0.)
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSteppingAction::~XeB2BSteppingAction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XeB2BSteppingAction::UserSteppingAction(const G4Step* aStep)
{
	G4StepPoint* prePoint = aStep->GetPreStepPoint();
	G4StepPoint* endPoint = aStep->GetPostStepPoint();

	G4double edep=aStep->GetTotalEnergyDeposit();
    G4String name_element = prePoint->GetTouchableHandle()->GetVolume()->GetName();

    //if(!name_element.find("Collimator1a")) G4cout << "-----> Coll 1 a" << G4endl;
     //  G4cout << "-----> " << name_element << G4endl;
#if 0
    if (!name_element.find("Collimator1")  && edep>0.)
	{
		tot_coll1_edep+=edep; 
		tot_coll1_edep2+=edep*edep;
		runAction->nb_coll1_edep+=1;
		runAction->SetColl1EDep(tot_coll1_edep);// Edep;;
		runAction->SetColl1EDep2(tot_coll1_edep2);
	}  

	if (!name_element.find("Collimator2")  && edep>0.)
	{
		tot_coll2_edep+=edep; 
		tot_coll2_edep2+=edep*edep;
		runAction->nb_coll2_edep += 1;
		runAction->SetColl2EDep(tot_coll2_edep);// Edep;;
		runAction->SetColl2EDep2(tot_coll2_edep2);
	}

	if (!name_element.find("Collimator3")  && edep>0.)
	{
		tot_coll3_edep+=edep; 
		tot_coll3_edep2+=edep*edep;
		runAction->nb_coll3_edep += 1;
		runAction->SetColl3EDep(tot_coll3_edep);// Edep;;
		runAction->SetColl3EDep2(tot_coll3_edep2);
	}
#endif
	//killed the - at the exit of the magnet - there are bend -
	G4Track* aTrack = aStep->GetTrack();
	G4String particleName = aTrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
        G4int trackID=aTrack->GetTrackID();// Primary tracks have a track ID =1 	
/*
 * if( endPoint->GetPosition().z()>12.*cm && particleName=="e-" && trackID==1)
	{
		fpSteppingManager->GetTrack()->SetTrackStatus(fStopAndKill);
//		G4cout << " e- killed !!! " << G4endl;	
		runAction->countkiller +=1;
	}	
	*/
}   
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

