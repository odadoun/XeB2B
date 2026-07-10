#ifndef XeB2BOutput_h
#define XeB2BOutput_h 1
#include "G4ios.hh"

#include "XeB2BSamplerHit.hh"
#include "XeB2BSamplerSD.hh"
#include "XeB2BDetectorConstruction.hh"

#include "TROOT.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TNtuple.h"
#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"
#include "TObjString.h"

using namespace std;
class XeB2BOutputMessenger;

class XeB2BOutput
{
  public:
    XeB2BOutput();
    ~XeB2BOutput();
	void WriteAndClose();
	void WriteDataSampler(XeB2BSamplerHitsCollection*);
	TTree*      sTree;
	void Init();
private:
	
    XeB2BDetectorConstruction* detector;
  public:
	TFile*   	rootFile;
	TObjString* header;
  
  private:
	TTree*   	SamplerTree;
    
	Int_t pdg,track_id;
	Float_t t,x,y,z,E,px,py,pz,E0,r0,z0;
	
};

#endif
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
