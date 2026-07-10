#ifndef XeB2BEventAction_h
#define XeB2BEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class XeB2BRunAction;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BEventAction : public G4UserEventAction
{
  public:
    XeB2BEventAction(XeB2BRunAction *ra);
   ~XeB2BEventAction();

  public:
    void 	BeginOfEventAction(const G4Event*);
    void	EndOfEventAction(const G4Event*);
    
    void SetPrintModulo(G4int val) {printModulo = val;};
	G4bool bool_cool1;  
	G4bool bool_cool2;  
  private:
    G4int                 		printModulo;                    
    XeB2BRunAction*            	runAction;
	 
    G4int SamplerCollID;
	G4int TargetCaloCollID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
