//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2B code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef XeB2BDetectorMessenger_h
#define XeB2BDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"
#include "XeB2BDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class XeB2BDetectorConstruction;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithADouble;
class G4UIdirectory;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BDetectorMessenger: public G4UImessenger
{
  public:
  
    XeB2BDetectorMessenger(XeB2BDetectorConstruction* );
   ~XeB2BDetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
   G4UIdirectory*                              detDir;
   XeB2BDetectorConstruction*                  Detector;
	
   G4UIcmdWithADoubleAndUnit*                  CylinderThicknessCmd; 
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......:
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

