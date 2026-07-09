//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
#ifndef XeB2BSamplerHit_h
#define XeB2BSamplerHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BSamplerHit : public G4VHit
{
  public:

      XeB2BSamplerHit();
   	  XeB2BSamplerHit(G4String aName,G4double z0,G4double E0,G4double r0,
							  G4double energy,G4double x, G4double y, G4double z,
							  G4double px, G4double py, G4double pz,G4int pdg,G4double Sx,
							  G4double Sy,G4double Sz,G4int trackID,G4double time);
								  
	  ~XeB2BSamplerHit();
      XeB2BSamplerHit(const XeB2BSamplerHit&);
      const XeB2BSamplerHit& operator=(const XeB2BSamplerHit&);
      G4int operator==(const XeB2BSamplerHit&) const;

      inline void* operator new(size_t);
      inline void  operator delete(void*);

  //    void Draw();
  //  void Print();
  private:
  G4String itsName;
  G4double itsZ0;
  G4double itsEnergy0;
  G4double itsR0;
  G4double itsTime;  
  G4double itsEnergy;
  G4double itsX;
  G4double itsY;
  G4double itsZ;
  G4double itsPX;
  G4double itsPY;
  G4double itsPZ;
  G4int    itsPDG;
  G4double itsSx;
  G4double itsSy;
  G4double itsSz;
  G4int    itsTrackID;
  public:
  inline G4double GetZ0() const
  {return itsZ0;}
  inline G4double GetEnergy0() const
  {return itsEnergy0;}
  inline G4double GetR0() const
  {return itsR0;}
  inline G4double GetTime() const
  {return itsTime;}
  
  inline G4double GetEnergy() const
  {return itsEnergy;}
  inline G4double GetX() const
  {return itsX;}  
  inline G4double GetY() const
  {return itsY;}  
  inline G4double GetZ() const
  {return itsZ;}  
  inline G4double GetPX() const
  {return itsPX;}  
  inline G4double GetPY() const
  {return itsPY;}
  inline G4double GetPZ() const
  {return itsPZ;}  
  inline G4int GetPDG() const
  {return itsPDG;}
  inline G4double GetSx() const
  {return itsSx;}
  inline G4double GetSy() const
  {return itsSy;}
  inline G4double GetSz() const
  {return itsSz;}
  inline G4int GetTrackID() const
  {return itsTrackID;}
  inline void SetName(G4String aName)
  {itsName=aName;}
  inline G4String GetName() const
  {return itsName;}

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<XeB2BSamplerHit> XeB2BSamplerHitsCollection;

extern G4Allocator<XeB2BSamplerHit> SamplerHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* XeB2BSamplerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) SamplerHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void XeB2BSamplerHit::operator delete(void *aHit)
{
  SamplerHitAllocator.FreeSingle((XeB2BSamplerHit*) aHit);
}

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

