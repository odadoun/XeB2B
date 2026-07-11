#include "XeB2BOutput.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4SystemOfUnits.hh"
#include <time.h>

extern G4double sum_initial_E;

XeB2BOutput::XeB2BOutput()
{
		G4cout << "XeB2BOutput CONSTRUCTOR ...." << G4endl;
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BOutput::~XeB2BOutput(){
/*
 * if(rootFile && rootFile->IsOpen())
	{
	     G4cout << " ))))))))))))))))))))))))))))))))) Root File Open  (msg from XeB2BOutput destructor)" << G4endl;
	     if(sTree) rootFile->Write();
	     rootFile->Close();
	     G4cout << " Root File close proprely (msg from XeB2BOutput destructor) " << G4endl;
	     delete rootFile;
	}
	*/
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BOutput::WriteAndClose()
{
	if(rootFile->IsOpen())
	{
		rootFile->Write();
		rootFile->Close();
	}
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BOutput::Init()
{
	rootFile = new TFile ("XeB2B.root","RECREATE","XeB2BSim output file");
  header = new TObjString("MyHeader");
	G4cout << "HERE WE ARE..." << G4endl;
	G4String name;
	for(G4int i=0;i<=4;i++){
		if(i==0) name="Sampler0";
        if(i==1) name="Sampler1";
		if(i==2) name="Sampler2";
		if(i==3) name="Sampler3";
		if(i==4) name="Sampler4";


		TTree* SamplerTree = new TTree(name,"Sampler output");
		SamplerTree->Branch("pdg",&pdg,"pdg/I");
		SamplerTree->Branch("tID",&track_id,"tID/I");
		SamplerTree->Branch("t",&t,"t/F");

		SamplerTree->Branch("x",&x,"x/F");
		SamplerTree->Branch("y",&y,"y/F");
		SamplerTree->Branch("z",&z,"z/F");

		SamplerTree->Branch("E",&E,"E/F");
		SamplerTree->Branch("px",&px,"px/F");
		SamplerTree->Branch("py",&py,"py/F");
		SamplerTree->Branch("pz",&pz,"pz/F");
        if(i != 0)
        {
            SamplerTree->Branch("E0",&E0,"E0/F");
            SamplerTree->Branch("r0",&r0,"r0/F");
            SamplerTree->Branch("z0",&z0,"z0/F");
        }
	}
}

void XeB2BOutput::WriteDataSampler(XeB2BSamplerHitsCollection *hc)
{
	G4cout.precision(6);
	for (G4int i=0; i<hc->entries(); i++)
	{
		//TTree*
		sTree=(TTree*)gDirectory->Get((*hc)[i]->GetName());
		if(!sTree) 
		G4Exception("PPSOutput: ROOT Sampler not found!","sTree pb",FatalException,"don't find tree in the rootfile:(");

		pdg=(*hc)[i]->GetPDG();
		track_id=(*hc)[i]->GetTrackID();
		t=(*hc)[i]->GetTime() / nanosecond ;
		x=(*hc)[i]->GetX()/cm;
		y=(*hc)[i]->GetY()/cm;
		z=(*hc)[i]->GetZ()/cm;

		E=(*hc)[i]->GetEnergy() / MeV ;
		px=(*hc)[i]->GetPX();
		py=(*hc)[i]->GetPY();
		pz=(*hc)[i]->GetPZ();

    		if((*hc)[i]->GetName() != "Sampler0")
    		{
			E0=(*hc)[i]->GetEnergy0() / MeV;
			r0=(*hc)[i]->GetR0()/cm;
			z0=(*hc)[i]->GetZ0()/cm;
			sTree->Fill();
		}
		else
		sTree->Fill();
	}

}
