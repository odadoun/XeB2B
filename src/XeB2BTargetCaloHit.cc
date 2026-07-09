//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "XeB2BOutput.hh"
#include "XeB2BTargetCaloHit.hh"
#include "XeB2BDetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4RotationMatrix.hh"
#include "G4Box.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4VisAttributes.hh"
#include "G4LogicalVolume.hh"
#include "G4ios.hh"

extern XeB2BOutput rootOutput;
G4Allocator<XeB2BTargetCaloHit> XeB2BTargetCaloHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BTargetCaloHit::XeB2BTargetCaloHit()
{;}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BTargetCaloHit::XeB2BTargetCaloHit(G4int pdg,G4int nx,G4int ny,G4int nz,G4double x,G4double y,G4double z,G4double depdE,G4double EnWeightZ)
:itsPDG(pdg),itsNX(nx),itsNY(ny),itsNZ(nz),itsX(x),itsY(y),itsZ(z),itsDEPdE(depdE),itsEnergyWeightedPosition(EnWeightZ)
{;}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BTargetCaloHit::~XeB2BTargetCaloHit()
{;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BTargetCaloHit::XeB2BTargetCaloHit(const XeB2BTargetCaloHit& right)
{
  itsPDG   = right.itsPDG;
  itsX     = right.itsX;
  itsY     = right.itsY;
  itsZ     = right.itsZ;
  itsNX    = right.itsNX;
  itsNY    = right.itsNY;
  itsNZ    = right.itsNZ;
  itsDEPdE = right.itsDEPdE;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const XeB2BTargetCaloHit& XeB2BTargetCaloHit::operator=(const XeB2BTargetCaloHit& right)
{
  itsPDG   = right.itsPDG;
  itsX     = right.itsX;
  itsY     = right.itsY;
  itsZ     = right.itsZ;
  itsNX    = right.itsNX;
  itsNY	   = right.itsNY;
  itsNZ    = right.itsNZ;
  itsDEPdE = right.itsDEPdE;
		  
  return *this;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
