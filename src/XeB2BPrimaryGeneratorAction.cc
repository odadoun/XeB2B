// PrimaryGeneratorAction.cc
#include "XeB2BPrimaryGeneratorAction.hh"
#include "G4ParticleTable.hh"
#include "G4SystemOfUnits.hh"

XeB2BPrimaryGeneratorAction::XeB2BPrimaryGeneratorAction() {
    particleGun = new G4ParticleGun(1);
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("gamma");
    particleGun->SetParticleDefinition(particle);
    particleGun->SetParticleEnergy(1.*MeV);
    particleGun->SetParticlePosition(G4ThreeVector(0., 0., 0.));
    particleGun->SetParticleMomentumDirection(G4ThreeVector(1., 0., 0.));
}

XeB2BPrimaryGeneratorAction::~XeB2BPrimaryGeneratorAction() {
    delete particleGun;
}

void XeB2BPrimaryGeneratorAction::GeneratePrimaries(G4Event* event) {
    particleGun->GeneratePrimaryVertex(event);
}
