// PrimaryGeneratorAction.hh
#ifndef XEB2BPRIMARYGENERATORACTION_HH
#define XEB2BPRIMARYGENERATORACTION_HH 

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"

class XeB2BPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
    XeB2BPrimaryGeneratorAction();
    ~XeB2BPrimaryGeneratorAction();

    virtual void GeneratePrimaries(G4Event* event);

private:
    G4ParticleGun* particleGun;
};

#endif
