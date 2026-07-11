//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef XeB2BInput_h
#define XeB2BInput_h 1
#include "G4ios.hh"
#include <fstream>
#include "globals.hh"
using namespace std;
class XeB2BInputMessenger;

class XeB2BInput
{
  public:
    XeB2BInput();
   ~XeB2BInput();
    void GetNextParticle(G4double& z0, G4double& x0 , G4double& y0 , G4double& px0, G4double& py0, G4double& zp0);
  private:
    ifstream input_file;
    G4String itsName;
    G4bool pola_file; 
    G4bool channelling_file; 
  public:
	 XeB2BInputMessenger* inputMessenger;	
	 void SetInputBunch(G4String NameFile);
	//XeB2BInputMessenger* inputMessenger;
	G4String GetInputName(){return itsName;}
};


#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

