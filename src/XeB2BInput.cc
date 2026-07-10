#include "XeB2BInput.hh"
#include "globals.hh"
#include "XeB2BInputMessenger.hh"
XeB2BInput::XeB2BInput():itsName("beam.dat")
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
        //if(itsName){G4cerr<< " Error in passing input bunch file "<<G4endl; exit(1);}
        //input_file.close();
        itsName = NameFile;
        input_file.open(itsName);
        if(!input_file.good()){ G4cerr<<"Cannot open bunch file "<< itsName <<G4endl; exit(1);}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BInput::GetNextParticle(G4double & z0, G4double& x0 , G4double& y0 ,
						       G4double& px0, G4double& py0, G4double& pz0)
{
#define _READ(value) input_file>>value
	
	     if(!input_file.good()) { G4cerr<<"Cannot open bunch file "<< "input.dat" <<G4endl; exit(1); }
	//X[cm] Y[cm] px[MeV] py[MeV] pz[MeV] 
	if(_READ(z0))
	{
		_READ(x0);
		_READ(y0);
		_READ(pz0);
		_READ(px0);
		_READ(py0);
	}
 
}		  
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
