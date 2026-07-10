//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "XeB2BEventAction.hh"
#include "XeB2BSamplerHit.hh"
#include "XeB2BOutput.hh"

#include "G4Event.hh"
#include "G4VVisManager.hh"
#include "G4UnitsTable.hh"
#include "G4SDManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4int evtNb;
extern XeB2BOutput rootOutput;

XeB2BEventAction::XeB2BEventAction(XeB2BRunAction * ra)
:printModulo(10000),runAction(ra),bool_cool1(false),bool_cool2(false)
{
	G4cout << " -----------> Event Action Construtor " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
XeB2BEventAction::~XeB2BEventAction()
{
  rootOutput.WriteAndClose();	
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BEventAction::BeginOfEventAction(const G4Event* evt)
{
   G4SDManager * SDman = G4SDManager::GetSDMpointer();
   SamplerCollID = SDman->GetCollectionID("SamplerCollection");
	
  evtNb = evt->GetEventID();
printModulo=100;
  //printing survey
 if (evtNb%printModulo == 0) 
    G4cout << "\n---> Begin of Event: " << evtNb << G4endl;
	bool_cool1 = false;
	bool_cool2 = false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void XeB2BEventAction::EndOfEventAction(const G4Event* evt)
{
  G4int evtNb = evt->GetEventID();	
  //if (evtNb%printModulo == 0)
  //G4cout << ">>> End Event " << evt->GetEventID() << G4endl;
  
    G4HCofThisEvent* HCE = evt->GetHCofThisEvent();
	XeB2BSamplerHitsCollection*  SampHC=NULL;

    if(SamplerCollID>=0)
    SampHC = (XeB2BSamplerHitsCollection*)(HCE->GetHC(SamplerCollID));
	if(SampHC) {rootOutput.WriteDataSampler(SampHC); };//G4cout << "----> " << SampHC->entries() << G4endl;}
    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
