#include "XeB2BSamplerHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4Allocator<XeB2BSamplerHit> SamplerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSamplerHit::XeB2BSamplerHit() 
{;}

XeB2BSamplerHit::XeB2BSamplerHit(G4String aName,G4int pdg, G4int trackID,G4double time,
				G4double x,G4double y, G4double z,
			        G4double energy,G4double px, G4double py, G4double pz,
			        G4double energy0, G4double r0,G4double z0)
:itsName(aName),itsPDG(pdg),itsTrackID(trackID),itsTime(time),
itsX(x),itsY(y),itsZ(z),
itsEnergy(energy),itsPX(px),itsPY(py),itsPZ(pz),
itsEnergy0(energy0),itsR0(r0),itsZ0(z0)
{;}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSamplerHit::~XeB2BSamplerHit() 
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSamplerHit::XeB2BSamplerHit(const XeB2BSamplerHit& right)
//  : G4VHit()
{
	itsName=right.itsName;
  	itsPDG = right.itsPDG;
  	itsTrackID=right.itsTrackID;
	itsTime = right.itsTime; 
  
  	itsX = right.itsX;
  	itsY = right.itsY;
  	itsZ = right.itsZ;
  	
	itsEnergy = right.itsEnergy;
  	itsPX = right.itsPX;
  	itsPY = right.itsPY;
  	itsPZ = right.itsPZ;
	
	itsEnergy0=right.itsEnergy0;
  	itsR0 = right.itsR0;
  	itsZ0 = right.itsZ0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const XeB2BSamplerHit& XeB2BSamplerHit::operator=(const XeB2BSamplerHit& right)
{
  	itsName= right.itsName;
  	itsPDG = right.itsPDG;
  	itsTrackID=right.itsTrackID;
  	itsTime = right.itsTime;

  	itsX = right.itsX;
  	itsY = right.itsY;
  	itsZ = right.itsZ;
  	
	itsEnergy = right.itsEnergy;
  	itsPX = right.itsPX;
  	itsPY = right.itsPY;
  	itsPZ = right.itsPZ;
  	
	itsEnergy0=right.itsEnergy0;
  	itsR0 = right.itsR0;
  	itsZ0 = right.itsZ0;

	return *this;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

