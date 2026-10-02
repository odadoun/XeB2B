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

  private:
    G4ParticleGun*                particleGun;
    XeB2BInput input;
    XeB2BPrimaryGeneratorMessenger* primaryMessenger;
    G4ThreeVector itsoffsetposition;
    G4double itsoffsetangle;	
};

#endif


