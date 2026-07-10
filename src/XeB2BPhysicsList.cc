#include "XeB2BPhysicsList.hh"

#include "G4ProcessManager.hh"
#include "G4ParticleTypes.hh"
#include "G4SystemOfUnits.hh"
XeB2BPhysicsList::XeB2BPhysicsList():  G4VUserPhysicsList()
{
  defaultCutValue = 0.01*mm;
  SetVerboseLevel(1);
}

XeB2BPhysicsList::~XeB2BPhysicsList()
{;}

void XeB2BPhysicsList::ConstructParticle()
{
  // In this method, static member functions should be called
  // for all particles which you want to use.
  // This ensures that objects of these particle types will be
  // created in the program. 

  ConstructBosons();
  ConstructLeptons();
  ConstructMesons();
  ConstructBaryons();
}

void XeB2BPhysicsList::ConstructBosons()
{
  // pseudo-particles
  G4Geantino::GeantinoDefinition();
  G4ChargedGeantino::ChargedGeantinoDefinition();

  // gamma
  G4Gamma::GammaDefinition();

  // optical photon
  G4OpticalPhoton::OpticalPhotonDefinition();
}

void XeB2BPhysicsList::ConstructLeptons()
{
  // leptons
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4MuonPlus::MuonPlusDefinition();
  G4MuonMinus::MuonMinusDefinition();

  G4NeutrinoE::NeutrinoEDefinition();
  G4AntiNeutrinoE::AntiNeutrinoEDefinition();
  G4NeutrinoMu::NeutrinoMuDefinition();
  G4AntiNeutrinoMu::AntiNeutrinoMuDefinition();
}

void XeB2BPhysicsList::ConstructMesons()
{
 //  mesons
  G4PionPlus::PionPlusDefinition();
  G4PionMinus::PionMinusDefinition();
  G4PionZero::PionZeroDefinition();
  G4Eta::EtaDefinition();
  G4EtaPrime::EtaPrimeDefinition();
  G4KaonPlus::KaonPlusDefinition();
  G4KaonMinus::KaonMinusDefinition();
  G4KaonZero::KaonZeroDefinition();
  G4AntiKaonZero::AntiKaonZeroDefinition();
  G4KaonZeroLong::KaonZeroLongDefinition();
  G4KaonZeroShort::KaonZeroShortDefinition();
}

void XeB2BPhysicsList::ConstructBaryons()
{
  //  barions
  G4Proton::ProtonDefinition();
  G4AntiProton::AntiProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4AntiNeutron::AntiNeutronDefinition();
}


void XeB2BPhysicsList::ConstructProcess()
{
  AddTransportation();
  ConstructEM();
  ConstructDecay();
}

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

#include "G4eMultipleScattering.hh"
#include "G4MuMultipleScattering.hh"

#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hIonisation.hh"

void XeB2BPhysicsList::ConstructEM()
{
   GetParticleIterator()->reset();
  while( (*GetParticleIterator())() ){
    G4ParticleDefinition* particle = GetParticleIterator()->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    G4String particleName = particle->GetParticleName();
    
    if (particleName == "gamma") {
      // gamma         
      pmanager->AddDiscreteProcess(new G4PhotoElectricEffect);
      pmanager->AddDiscreteProcess(new G4ComptonScattering);
      pmanager->AddDiscreteProcess(new G4GammaConversion);
      
    } else if (particleName == "e-") {
      //electron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);      

    } else if (particleName == "e+") {
      //positron
      pmanager->AddProcess(new G4eMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4eIonisation,       -1, 2,2);
      pmanager->AddProcess(new G4eBremsstrahlung,   -1, 3,3);
      pmanager->AddProcess(new G4eplusAnnihilation,  0,-1,4);

    } else if( particleName == "mu+" || 
               particleName == "mu-"    ) {
      //muon  
      pmanager->AddProcess(new G4MuMultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
      pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
      pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);       
     
    } /*else if ((!particle->IsShortLived()) &&
	       (particle->GetPDGCharge() != 0.0) && 
	       (particle->GetParticleName() != "chargedgeantino")) {
      //all others charged particles except geantino
      pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
      pmanager->AddProcess(new G4hIonisation,       -1, 2,2); 
    }*/
  }
}

#if 0
#include "G4LowEnergyRayleigh.hh"
#include "G4LowEnergyPhotoElectric.hh"
#include "G4LowEnergyCompton.hh"
#include "G4LowEnergyGammaConversion.hh"

void XeB2BPhysicsList::ConstructEM_Low_Energy()
{
    
    GetParticleIterator()->reset();
    while( (*GetParticleIterator())() ){
        G4ParticleDefinition* particle = GetParticleIterator()->value();
        G4ProcessManager* pmanager = particle->GetProcessManager();
        G4String particleName = particle->GetParticleName();
        
        if (particleName == "gamma") {
            
            pmanager->AddDiscreteProcess(new G4LowEnergyRayleigh());
            pmanager->AddDiscreteProcess(new G4LowEnergyPhotoElectric);
            pmanager->AddDiscreteProcess(new G4LowEnergyCompton);
            pmanager->AddDiscreteProcess(new G4LowEnergyGammaConversion);
            
        } else if (particleName == "e-") {
            
            pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
            pmanager->AddProcess(new G4LowEnergyIonisation,        -1, 2,2);
            pmanager->AddProcess(new G4LowEnergyBremsstrahlung,    -1, 3,3);
            
        } else if (particleName == "e+") {
            
            pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
            pmanager->AddProcess(new G4eIonisation,        -1, 2,2);
            pmanager->AddProcess(new G4eBremsstrahlung,    -1, 3,3);
            pmanager->AddProcess(new G4eplusAnnihilation,   0,-1,4);
            
        } else if( particleName == "mu+" ||
                  particleName == "mu-"    ) {
            
            pmanager->AddProcess(new G4MultipleScattering,-1, 1,1);
            pmanager->AddProcess(new G4MuIonisation,      -1, 2,2);
            pmanager->AddProcess(new G4MuBremsstrahlung,  -1, 3,3);
            pmanager->AddProcess(new G4MuPairProduction,  -1, 4,4);
            
        } else if (particleName == "GenericIon") {
            
            pmanager->AddProcess(new G4MultipleScattering, -1, 1,1);
            pmanager->AddProcess(new G4hLowEnergyIonisation,       -1,2,2);
            //      pmanager->AddProcess(new G4ionIonisation,      -1, 2,2);
            // it dose not work here
        } else if ((!particle->IsShortLived()) &&
                   (particle->GetPDGCharge() != 0.0) &&
                   (particle->GetParticleName() != "chargedgeantino")) {
            
            pmanager->AddProcess(new G4MultipleScattering,-1,1,1);
            pmanager->AddProcess(new G4hLowEnergyIonisation,       -1,2,2);
        }
    }
}
#endif 

#include "G4Decay.hh"

void XeB2BPhysicsList::ConstructDecay()
{
  // Add Decay Process
  G4Decay* theDecayProcess = new G4Decay();
  GetParticleIterator()->reset();
  while( (*GetParticleIterator())() ){
    G4ParticleDefinition* particle = GetParticleIterator()->value();
    G4ProcessManager* pmanager = particle->GetProcessManager();
    if (theDecayProcess->IsApplicable(*particle)) { 
      pmanager ->AddProcess(theDecayProcess);
      // set ordering for PostStepDoIt and AtRestDoIt
      pmanager ->SetProcessOrdering(theDecayProcess, idxPostStep);
      pmanager ->SetProcessOrdering(theDecayProcess, idxAtRest);
    }
  }
}

void XeB2BPhysicsList::SetCuts()
{
  if (verboseLevel >0){
    G4cout << "XeB2BPhysicsList::SetCuts:";
    G4cout << "CutLength : " << G4BestUnit(defaultCutValue,"Length") << G4endl;
  }

  // set cut values for gamma at first and for e- second and next for e+,
  // because some processes for e+/e- need cut values for gamma
  //
  SetCutValue(defaultCutValue, "gamma");
  SetCutValue(defaultCutValue, "e-");
  SetCutValue(defaultCutValue, "e+");

  if (verboseLevel>0) DumpCutValuesTable();
}


