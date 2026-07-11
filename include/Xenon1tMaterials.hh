#ifndef __XENONPMATERIALS_H__
#define __XENONPMATERIALS_H__

// Additional Header Files
#include <globals.hh>
#include <map>
#include <vector>

using std::map;
using std::vector;

// Root Header Files
#include "TDirectory.h"
#include "TFile.h"

// G4 Header Files
#include <G4OpticalSurface.hh>
#include <G4ThreeVector.hh>

class Xenon1tMaterials {
 public:
  Xenon1tMaterials();
  // Xenon1tMaterials(Xenon1tDetectorConstruction*);
  ~Xenon1tMaterials();
  void DefineMaterials(G4double pWABSL, G4double pEPTFEReflectivity, G4double pGdConcentration);
  
  void SetLXeTeflonReflectivity(G4double);
  void SetGXeTeflonReflectivity(G4double);
  void SetLXeTeflonUnpolishedReflectivity(G4double);
  void SetGXeTeflonUnpolishedReflectivity(G4double);
  void SetTeflonReflectivitySpikeLobeBackscatter(G4String, G4ThreeVector);
  void SetWireReflectivity(G4String, G4double);
  void DumpTeflonSurfaceParameters(G4String);
  inline G4OpticalSurface *LXeTeflonOpticalSurface()
				{ return pLXeTeflonOpticalSurface; };
  inline G4OpticalSurface *GXeTeflonOpticalSurface()
				{ return pGXeTeflonOpticalSurface; };
  inline G4OpticalSurface *GXeTeflonUnpolishedOpticalSurface()
				{ return pGXeTeflonUnpolishedOpticalSurface; };
  inline G4OpticalSurface *LXeTeflonUnpolishedOpticalSurface()
				{ return pLXeTeflonUnpolishedOpticalSurface; };
  inline G4OpticalSurface *GXeWireSurface()
                { return pGXeWireSurface;}
  inline G4OpticalSurface *LXeWireSurface()
                { return pLXeWireSurface;}
  inline G4OpticalSurface *ePTFEWaterOpticalSurface(){ 
    return pEPTFEWaterOpticalSurface;};
  inline G4OpticalSurface *MvFoilOpticalSurface(){ 
    return pMvFoilOpticalSurface;};
  inline G4OpticalSurface *PMTAlEvaporationOpticalSurface(){ 
    return pPMTAlEvaporationOpticalSurface;};
  inline G4OpticalSurface *SSOpticalSurface(){ 
    return pSSOpticalSurface;};

  //photo cathode material parameters
  void SetPhCathRef(G4String);
  void SetQETable(G4String,G4int);
  inline G4OpticalSurface *WindowPCOpticalSurface()
				{ return pWindowPCOpticalSurface; };

  // Setting Water and GdWater optical properties
  // with scaling factor for absorption length
  G4MaterialPropertiesTable *SetWaterOpticalProperties(G4double pWABSL);
  G4MaterialPropertiesTable *SetGdWaterOpticalProperties(G4double pWABSL);

 private:
  // Xenon1tDetectorConstruction *pDetectorConstruction;
  G4double pLXeElectricField;
  G4double pGXeElectricField;

  G4OpticalSurface *pLXeTeflonOpticalSurface;
  G4OpticalSurface *pGXeTeflonOpticalSurface;
  G4OpticalSurface *pGXeTeflonUnpolishedOpticalSurface;
  G4OpticalSurface *pLXeTeflonUnpolishedOpticalSurface;

  G4OpticalSurface *pLXeWireSurface;
  G4OpticalSurface *pGXeWireSurface;

  G4OpticalSurface *pEPTFEWaterOpticalSurface;
  G4OpticalSurface *pMvFoilOpticalSurface;
  G4OpticalSurface *pPMTAlEvaporationOpticalSurface;
  G4OpticalSurface *pSSOpticalSurface;

  //photo cathode material parameters
  G4OpticalSurface *pWindowPCOpticalSurface;
  G4MaterialPropertiesTable *pmctsurf_mt;
  G4MaterialPropertiesTable *rpmctsurf_mt;
  static const G4int PNUM = 2;
  G4double pmctsurf_PP[PNUM];
  G4double thePCEff;
  G4double theALRATIO;
  G4double theALREFL;
  G4double theALXeREFL;
};

#endif
