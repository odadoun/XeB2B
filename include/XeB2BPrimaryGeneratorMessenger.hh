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

#ifndef XeB2BPrimaryGeneratorMessenger_h
#define XeB2BPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "globals.hh"

class XeB2BPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADouble;
class XeB2BPrimaryGeneratorMessenger: public G4UImessenger
{
public:
  XeB2BPrimaryGeneratorMessenger(XeB2BPrimaryGeneratorAction*);
  virtual ~XeB2BPrimaryGeneratorMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  G4UIdirectory*               gunDir; 
   XeB2BPrimaryGeneratorAction*    XeB2BAction;
   G4UIcmdWith3VectorAndUnit*          PositionOffsetCmd;
   G4UIcmdWithADouble* AngleOffsetCmd;
};


#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

