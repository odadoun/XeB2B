
#include "XeB2BPrimaryGeneratorAction.hh"
#include "XeB2BPrimaryGeneratorMessenger.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

XeB2BPrimaryGeneratorAction::XeB2BPrimaryGeneratorAction()
{
  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);
  primaryMessenger = new XeB2BPrimaryGeneratorMessenger(this);
  // default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
					//= particleTable->FindParticle(particleName="e-");
					= particleTable->FindParticle(particleName="gamma");
  particleGun->SetParticleDefinition(particle);
//  particleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));
  particleGun->SetParticleMomentum(G4ThreeVector(0.,1.*GeV,1.*GeV));
  particleGun->SetParticleEnergy(2*GeV);
}

XeB2BPrimaryGeneratorAction::~XeB2BPrimaryGeneratorAction()
{
  delete particleGun;

}

void XeB2BPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4double z0,x0,y0;
	G4double px0,py0,pz0;
	G4double p;
	G4double E;
	G4double m;

        input.GetNextParticle(x0,y0,z0,px0,py0,pz0);
	z0*=cm;x0*=cm; y0*=cm;
	px0*=MeV; py0*=MeV; pz0*=MeV;
	p=sqrt(px0*px0+py0*py0+pz0*pz0);
	m=particleGun->GetParticleDefinition()->GetPDGMass() / MeV;
	E=sqrt(p*p + m*m);
	//G4cout << E << " Primary " << pz0 << G4endl;

    //offset position
    //particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));//x0,y0,position_shoot + z0));
    //offset angle

    particleGun->SetParticleMomentum(G4ThreeVector(px0,py0,pz0));//angle_x,angle_y,angle_z));

    //particleGun->SetParticleEnergy(p);
    particleGun->SetParticleEnergy(E);
    particleGun->GeneratePrimaryVertex(anEvent);

}
