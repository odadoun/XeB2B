//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
// $Id: EventActionMessenger.hh,v 1.1 2006/10/02 13:48:10 vnivanch Exp $
// GEANT4 tag $Name: geant4-08-02-patch-01-ref $
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef XeB2BEventActionMessenger_h
#define XeB2BEventActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class XeB2BEventAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BEventActionMessenger: public G4UImessenger
{
  public:
    XeB2BEventActionMessenger(XeB2BEventAction*);
   ~XeB2BEventActionMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    XeB2BEventAction* eventAction;
    
    G4UIdirectory*        eventDir;   
    G4UIcmdWithAnInteger* PrintCmd;    
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
