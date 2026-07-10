//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooGo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef XeB2BSteppingAction_h
#define XeB2BSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class XeB2BDetectorConstruction;
class XeB2BPrimaryGeneratorAction;
class XeB2BRunAction;
class XeB2BEventAction;


class XeB2BSteppingAction : public G4UserSteppingAction
{
  public:
    XeB2BSteppingAction(XeB2BDetectorConstruction*, XeB2BPrimaryGeneratorAction*, XeB2BRunAction*, XeB2BEventAction*);
   ~XeB2BSteppingAction();
    
     G4double total_dep;
    void UserSteppingAction(const G4Step*);
  
  private:
    XeB2BDetectorConstruction*   detector;
    XeB2BPrimaryGeneratorAction* primary;
    XeB2BRunAction*              runAction;
    XeB2BEventAction*            eventAction;
	G4double tot_coll1_edep;
	G4double tot_coll1_edep2;
	G4double tot_coll2_edep;
	G4double tot_coll2_edep2;
	G4double tot_coll3_edep;
	G4double tot_coll3_edep2;
	G4double tot_sampler;
	G4int MaxStepNumber;
};

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
