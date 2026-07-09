//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "XeB2BEventAction.hh"
#include "XeB2BEventActionMessenger.hh"
#include "XeB2BSamplerHit.hh"
#include "XeB2BTargetCaloHit.hh"
#include "XeB2BOutput.hh"

#include "G4Event.hh"
//#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
#include "XeB2BRunAction.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int evtNb;
extern XeB2BOutput rootOutput;

XeB2BEventAction::XeB2BEventAction(XeB2BRunAction * ra)
:printModulo(10000),eventMessenger(0),runAction(ra),stepNumber(0)
{
  eventMessenger = new XeB2BEventActionMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
XeB2BEventAction::~XeB2BEventAction()
{
  delete eventMessenger;
  rootOutput.WriteAndClose();	
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BEventAction::BeginOfEventAction(const G4Event* evt)
{
   G4SDManager * SDman = G4SDManager::GetSDMpointer();
   SamplerCollID = SDman->GetCollectionID("SamplerCollection");
   TargetCaloCollID = SDman->GetCollectionID("TargetCaloCollection");
	
  evtNb = evt->GetEventID();
  //printing survey
 if (evtNb%printModulo == 0) 
    G4cout << "\n---> Begin of Event: " << evtNb << G4endl;
	stepNumber=0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XeB2BEventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();	
  if (evtNb%printModulo == 0)
  G4cout << ">>> End Event " << evt->GetEventID() << G4endl;
  
  if (runAction) runAction->EventFinished(); 

   
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	XeB2BSamplerHitsCollection*  SampHC=NULL;
	XeB2BTargetCaloHitsCollection* TargetCaloHC=NULL;

    if(SamplerCollID>=0)
    SampHC = (XeB2BSamplerHitsCollection*)(HCE->GetHC(SamplerCollID));
	//if(SampHC) {if(rootOutput.GetrootOutputFormat() == "All" ) rootOutput.WriteDataSampler(SampHC);}
	if(SampHC) rootOutput.WriteDataSampler(SampHC);
	
    
	if(TargetCaloCollID>=0)
	TargetCaloHC = (XeB2BTargetCaloHitsCollection*)(HCE->GetHC(TargetCaloCollID));
    //if(TargetCaloHC) outputTarget.WriteDataTarget(TargetCaloHC);
    if(TargetCaloHC) rootOutput.WriteDataSampler(TargetCaloHC);
    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
