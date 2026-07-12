#include "XeB2BInput.hh"
#include "globals.hh"
#include "XeB2BInputMessenger.hh"
XeB2BInput::XeB2BInput():itsName("input.dat")
{
    inputMessenger = new XeB2BInputMessenger(this);
	//inputMessenger = new XeB2BInputMessenger(this);
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//
XeB2BInput::~XeB2BInput()
{
	input_file.close();
}
//
void XeB2BInput::SetInputBunch(G4String NameFile)
{
        if(!itsName){G4cerr<< " Error in passing input bunch file "<<G4endl; exit(1);}
        itsName = NameFile;
        input_file.open(itsName);
        if(!input_file.good()){ G4cerr<< "SetInputBunch : Cannot open bunch file "<< itsName <<G4endl; exit(1);}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BInput::GetNextParticle(G4double & z0, G4double& x0 , G4double& y0 ,
						       G4double& px0, G4double& py0, G4double& pz0)
{
	if (!(input_file >> z0 >> x0 >> y0 >> px0 >> py0 >> pz0))
     {
    	if (!input_file.eof())
        	G4cerr << "Error while reading bunch file " << itsName << G4endl;
     }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
