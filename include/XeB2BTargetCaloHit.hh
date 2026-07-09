//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
// See Geant4 tips
// http://geant4.slac.stanford.edu/Tips/event/3.html
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#ifndef XeB2BTargetCaloHit_h
#define XeB2BTargetCaloHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

class XeB2BTargetCaloHit : public G4VHit
{
  public:
  XeB2BTargetCaloHit();
  XeB2BTargetCaloHit(G4int pdg,G4int nx,G4int ny,G4int nz,G4double x,G4double y,G4double z,G4double depdE=0.,G4double EnWeightZ=0.);
  ~XeB2BTargetCaloHit();

	XeB2BTargetCaloHit(const XeB2BTargetCaloHit&);
   const XeB2BTargetCaloHit& operator=(const XeB2BTargetCaloHit&);
   G4int operator==(const XeB2BTargetCaloHit&) const;

   inline void* operator new(size_t);
   inline void  operator delete(void*);


  private:
  G4int 	itsPDG;
  G4int 	itsNX;
  G4int 	itsNY;
  G4int 	itsNZ;
  G4double  itsX;
  G4double  itsY;
  G4double 	itsZ;
  G4double 	itsDEPdE;
  G4double 	itsSumDEPdE;
  G4double itsEnergyWeightedPosition;

  public:
  inline G4int GetPDG() const
  {return itsPDG;}
  inline G4double GetX() const
  {return itsX;}	  
  inline G4double GetY() const
  {return itsY;}	  
  inline G4double GetZ() const
  {return itsZ;}	  
  inline G4int GetNX() const
  {return itsNX;}
  inline G4int GetNY() const
  {return itsNY;}
  inline G4int GetNZ() const
  {return itsNZ;}
  inline G4double GetDEPdE() const
  {return itsDEPdE;}
  inline G4double GetSumDEPdE() const
  {return itsSumDEPdE;}
  inline G4double GetEnergyWeightedPosition() const
  {return itsEnergyWeightedPosition;}
 
};
typedef G4THitsCollection<XeB2BTargetCaloHit> XeB2BTargetCaloHitsCollection;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern G4Allocator<XeB2BTargetCaloHit> XeB2BTargetCaloHitAllocator;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void* XeB2BTargetCaloHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) XeB2BTargetCaloHitAllocator.MallocSingle();
  return aHit;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
inline void XeB2BTargetCaloHit::operator delete(void *aHit)
{
  XeB2BTargetCaloHitAllocator.FreeSingle((XeB2BTargetCaloHit*) aHit);
}
#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
