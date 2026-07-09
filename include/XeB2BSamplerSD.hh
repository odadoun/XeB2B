//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef XeB2BSamplerSD_h
#define XeB2BSamplerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "XeB2BSamplerHit.hh"
#include "G4Navigator.hh"
#include "G4TransportationManager.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class XeB2BSamplerSD : public G4VSensitiveDetector
{
  public:
      XeB2BSamplerSD(G4String);
     ~XeB2BSamplerSD();

      void Initialize(G4HCofThisEvent*HCE);
      G4bool ProcessHits(G4Step*, G4TouchableHistory*);
      void EndOfEvent(G4HCofThisEvent*HCE);
	  //	   void clear();
//		void DrawAll();
//		void PrintAll();
  private:
      XeB2BSamplerHitsCollection* XeB2BSamplerCollection;
	  G4Navigator* StepperNavigator;
  	  G4bool StoreHit;
};


#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

