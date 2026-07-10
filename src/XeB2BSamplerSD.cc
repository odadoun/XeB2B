#include "XeB2BSamplerSD.hh"
//#include "XeB2BOutput.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4PolarizationHelper.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4StokesVector.hh"
#include "G4SystemOfUnits.hh"

G4String particleName;
G4double initial_Positron_pt, initial_Positron_E;
G4int particleNumber=0.;
extern G4ThreeVector initial_PartMomDir;
//extern XeB2BOutput rootOutput;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSamplerSD::XeB2BSamplerSD(G4String name):G4VSensitiveDetector(name),StoreHit(true)
{
	G4String HCname;
	collectionName.insert(HCname="SamplerCollection");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BSamplerSD::~XeB2BSamplerSD()
{
	G4cout << " XeB2B Sampler ended " << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BSamplerSD::Initialize(G4HCofThisEvent* HCE)
{
	
	XeB2BSamplerCollection = new XeB2BSamplerHitsCollection
	(SensitiveDetectorName,collectionName[0]); 
	/*  static G4int HCID = -1;
	 if(HCID<0)
	 { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]); 
	 HCE->AddHitsCollection(HCID,SamplerCollection); 
	 }
	 */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4bool XeB2BSamplerSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
	G4Track* theTrack		    =	aStep->GetTrack();
	
	if(StoreHit)
	{
		G4ThreeVector pos		=	theTrack->GetPosition();
		G4ThreeVector momDir	=	theTrack->GetMomentumDirection();
		G4ThreeVector vtx		=	theTrack->GetVertexPosition();
		G4double energy		    =	theTrack->GetKineticEnergy();
		
		G4double x			    =	pos.x();
		G4double y			    =	pos.y();
		G4double z			    =	pos.z();
		
		G4double px			    =	momDir.x();
		G4double py			    =	momDir.y();
		G4double pz			    =	momDir.z();
		G4int    pdg			=	theTrack->GetDefinition()->GetPDGEncoding();
		G4int    trackID  	    =   theTrack->GetTrackID();// Primary tracks have a track ID = 1
	
		G4double time			=   (theTrack->GetTrackLength()/meter)/(theTrack->GetVelocity()/(meter/nanosecond));

		particleName            =   theTrack->GetDynamicParticle()->GetDefinition()->GetParticleName();
		
		G4double x0             =	vtx.x();
		G4double y0             =	vtx.y();
		G4double r0             =   sqrt(x0*x0+y0*y0);
		G4double z0             =    vtx.z();
                G4double energy0        =   theTrack->GetVertexKineticEnergy();


		G4String sampname       =  theTrack->GetVolume()->GetName();
		
	if(pz<0)  energy*=-1;// to distinguish backscattered particles
		XeB2BSamplerHit* newHit = new XeB2BSamplerHit(sampname,pdg,trackID,time,x,y,z,energy,px,py,pz,energy0,r0,z0);
	
		XeB2BSamplerCollection->insert( newHit );	
		
		if(theTrack->GetVolume()!=theTrack->GetNextVolume()) StoreHit=true;
		else StoreHit=false;
		return true;
	}	
	else
	{
		if(theTrack->GetVolume()!=theTrack->GetNextVolume()) StoreHit=true;
		else StoreHit=false;
		return false;
	 }

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BSamplerSD::EndOfEvent(G4HCofThisEvent *HCE)
{
	//  if (verboseLevel>0) 
	 //{ 
	 G4int NbHits = XeB2BSamplerCollection->entries();
//	 G4cout << "\n-------->Hits Collection: in this event they are " << NbHits << " hits in the Sampler: " << G4endl;
	 for (G4int i=0;i<NbHits;i++) (*XeB2BSamplerCollection)[i]->Print();
	 //}
	 
	G4SDManager * SDman = G4SDManager::GetSDMpointer();
	G4int HCID = SDman->GetCollectionID(collectionName[0]);
	HCE->AddHitsCollection( HCID, XeB2BSamplerCollection );
	
}
