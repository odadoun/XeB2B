#ifndef XeB2BPrimaryGeneratorAction_h
#define XeB2BPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "XeB2BPrimaryGeneratorMessenger.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "XeB2BInput.hh"

class G4ParticleGun;
class G4Event;

class XeB2BPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    XeB2BPrimaryGeneratorAction();    
    virtual ~XeB2BPrimaryGeneratorAction();

 	
  public:
    virtual void GeneratePrimaries(G4Event*);

   void SetPositionOffset(G4ThreeVector offsetposition);
   G4ThreeVector GetPositionOffset();

   void SetAngleOffset(G4double offsetangle);
   G4double GetAngleOffset();
  private:
    G4ParticleGun*                particleGun;
    XeB2BInput input;
    XeB2BPrimaryGeneratorMessenger* primaryMessenger;
    G4ThreeVector itsoffsetposition;
    G4double itsoffsetangle;	
};

inline void XeB2BPrimaryGeneratorAction::SetPositionOffset(G4ThreeVector offsetposition)
{itsoffsetposition = offsetposition;}

inline G4ThreeVector  XeB2BPrimaryGeneratorAction::GetPositionOffset()
{return itsoffsetposition;}

inline void XeB2BPrimaryGeneratorAction::SetAngleOffset(G4double offsetangle)
{itsoffsetangle = offsetangle;}

inline G4double  XeB2BPrimaryGeneratorAction::GetAngleOffset()
{return itsoffsetangle;}
#endif


