#include "XeB2BInput.hh"
#include "globals.hh"
#include "XeB2BInputMessenger.hh"
XeB2BInput::XeB2BInput():itsName("input.dat")
{
	inputMessenger = new XeB2BInputMessenger(this);
    input_file.open(itsName, ios::out);
	//inputMessenger = new XeB2BInputMessenger(this);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
XeB2BInput::~XeB2BInput()
{
	input_file.close();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BInput::GetNextParticle(G4double & x0, G4double& y0 , G4double& z0 ,
						       G4double& px0, G4double& py0, G4double& pz0)
{
#define _READ(value) input_file>>value
 
	if(!input_file.good()) {
             G4cerr<<"Cannot open bunch file "<< "input.dat" <<G4endl; exit(1); }
      if(_READ(x0))
          {
           _READ(y0);
           _READ(z0);
      	   _READ(px0);
           _READ(py0);
           _READ(pz0);
	  }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
