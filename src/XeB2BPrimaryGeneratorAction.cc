
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
					= particleTable->FindParticle(particleName="geantino");
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

  input.GetNextParticle(z0,x0,y0,px0,py0,pz0);
	G4cout << "Primary " << pz0 << G4endl;
	z0*=cm;x0*=cm; y0*=cm;
	px0*=MeV; py0*=MeV; pz0*=MeV;
	p=sqrt(px0*px0+py0*py0+pz0*pz0);
	m=particleGun->GetParticleDefinition()->GetPDGMass() / MeV;
	E=sqrt(p*p + m*m);

    //offset position
    x0 += GetPositionOffset().x();
    y0 += GetPositionOffset().y();
    //particleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));
    G4double position_shoot = -13.*cm;

    particleGun->SetParticlePosition(G4ThreeVector(0.,0.,0.));//x0,y0,position_shoot + z0));
    //offset angle
    G4double angle=GetAngleOffset();

    G4double u=px0/p;
    G4double v=py0/p;
    G4double w=pz0/p;

    G4double angle_x=u*cos(angle)+(u*w/sqrt(1.-w*w))*sin(angle);
    G4double angle_y=v*cos(angle)+(v*w/sqrt(1.-w*w))*sin(angle);
    G4double angle_z=w*cos(angle)-sqrt(1.-w*w)*sin(angle);
//  G4cout << " Angle " << angle << " " << G4ThreeVector(angle_x,angle_y,angle_z) << G4endl;
//  G4cout << x0/cm << "  " << y0/cm << "  " << E/MeV << G4endl;
    particleGun->SetParticleMomentumDirection(G4ThreeVector(0,1.,0.));//angle_x,angle_y,angle_z));
    //particleGun->SetParticleEnergy(p);
    particleGun->SetParticleEnergy(2*GeV);
    particleGun->GeneratePrimaryVertex(anEvent);

}
