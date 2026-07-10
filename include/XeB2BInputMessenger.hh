//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef XeB2BInputMessenger_h
#define XeB2BInputMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class XeB2BInput;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BInputMessenger: public G4UImessenger
{
  public:
  
    XeB2BInputMessenger(XeB2BInput* );
   ~XeB2BInputMessenger();
    
   void SetNewValue(G4UIcommand*, G4String);
    
  private:
  
    XeB2BInput*   Input;
    G4UIcmdWithAString*        InputCmd;
    G4bool itsV;
  
  public :  

};


#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

