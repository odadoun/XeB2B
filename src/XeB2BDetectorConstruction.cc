#include "XeB2BDetectorConstruction.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Torus.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4sphere.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4PSEnergyDeposit.hh"
#include "G4PSTrackLength.hh"
#include "G4PSNofStep.hh"
#include "G4SDParticleFilter.hh"
#include "G4NistManager.hh"
#include "G4ios.hh"
#include "Xenon1tMaterials.hh"

using namespace CLHEP;

XeB2BDetectorConstruction::XeB2BDetectorConstruction()
:constructed(false),itsthickness(0.)
{fMessenger = new XeB2BDetectorMessenger(this);}

XeB2BDetectorConstruction::~XeB2BDetectorConstruction()
{delete fMessenger;}

G4VPhysicalVolume* XeB2BDetectorConstruction::Construct()
{

  if(!constructed)
  {
    constructed = true;
    DefineMaterials();
    SetupGeometry();
  }
  return worldPhys;
}

void XeB2BDetectorConstruction::DefineMaterials()
{
  G4String name, symbol;             //a=mass of a mole;
  G4double a, z, density;            //z=mean number of protons;

  G4int ncomponents, natoms;
  G4double fractionmass;

  Materials = new Xenon1tMaterials();
  G4double pGdConcentration = 0.2;      // Gadolinium mass concntration
  G4double pWABSL = 1.;                 // Water absorption length scaling factor
  G4double pEPTFEReflectivity = 0.9935; // ePTFE reflectivity

  Materials->DefineMaterials(pWABSL, pEPTFEReflectivity, pGdConcentration);
  xenon = G4Material::GetMaterial("LXe");
  G4NistManager* nist = G4NistManager::Instance();
  tungsten = nist->FindOrBuildMaterial("G4_W");
  vacuum = G4Material::GetMaterial("Vacuum");
  //
  // define Elements
  //

  a = 1.01*g/mole;
  G4Element* H  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);

  a = 14.01*g/mole;
  G4Element* N  = new G4Element(name="Nitrogen",symbol="N" , z= 7., a);

  a = 16.00*g/mole;
  G4Element* O  = new G4Element(name="Oxygen"  ,symbol="O" , z= 8., a);

  //
  // define a material from elements.   case 1: chemical molecule
  //
  density = 1.000*g/cm3;
  water = new G4Material(name="Water", density, ncomponents=2);
  water->AddElement(H, natoms=2);
  water->AddElement(O, natoms=1);

  //
  // define a material from elements.   case 2: mixture by fractional mass
  //

  density = 1.290*mg/cm3;
  air = new G4Material(name="Air"  , density, ncomponents=2);
  air->AddElement(N, fractionmass=0.7);
  air->AddElement(O, fractionmass=0.3);

	// Vacuum from example novice No3
   Vacuum = new G4Material("Galactic",z=1.,a=1.01*g/mole,density=universe_mean_density,kStateGas,2.73*kelvin,3.e-18*pascal);


	Al = G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");
	Fe = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");
	Cu = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");
	Tungsten = G4NistManager::Instance()->FindOrBuildMaterial("G4_W");
    Be = G4NistManager::Instance()->FindOrBuildMaterial("G4_Be");

    a = 28.09*g/mole;
    G4Element* Si   = new G4Element(name="Silicium"  ,symbol="Si" , z=14, a);
    density = 2.33*g/cm3;
    quartz = new G4Material(name="quartz"  , density, ncomponents=2);
    quartz->AddElement(Si, natoms=1);
    quartz->AddElement(O, natoms=2);
}

void XeB2BDetectorConstruction::SetupGeometry()
{
  const G4double sampler_thickness = 0.01*um;   // épaisseur des samplers

  // ---------- World ----------
  G4VSolid* worldSolid = new G4Box("World", 2.*m, 2.*m, 2.*m);
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, Vacuum, "World");
  worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, 0);

  // ---------- Dimensions ----------
  G4double innerRadius = 5.*cm;
  G4double innerHeight = 50.*cm;
  G4double outerRadius = 50.*cm;
  G4double outerHeight = 100.*cm;
  G4double thicknesstungsten = 5.*mm;

  G4double wRadius = innerRadius + thicknesstungsten;        // rayon du tungstène
  G4double wHalfH  = innerHeight/2. + thicknesstungsten;     // demi-hauteur du tungstène

  // ---------- Visualisation ----------
  G4VisAttributes* visSampler = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
  visSampler->SetVisibility(true);
  G4VisAttributes* xenonVol = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
  xenonVol->SetVisibility(true);
  G4VisAttributes* tungstenVol = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
  tungstenVol->SetVisibility(true);

  // ---------- Sensitive detector ----------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SamplerSensDet = new XeB2BSamplerSD("XeB2BSamplerSD");
  SDman->AddNewDetector(SamplerSensDet);

  // Fonction utilitaire : coquille fermée (parois + bouchons) sampler_thickness,
  // à l'intérieur d'un cylindre (R, halfH)
  auto shellInside = [&](const G4String& name, G4double R, G4double halfH) {
    G4Tubs* big   = new G4Tubs(name + "_big",   0., R,     halfH,     0.*deg, 360.*deg);
    G4Tubs* small = new G4Tubs(name + "_small", 0., R - sampler_thickness, halfH - sampler_thickness, 0.*deg, 360.*deg);
    return new G4SubtractionSolid(name, big, small);
  };

  // ---------- Outer cylinder (xénon) ----------
  G4Tubs* outerSolid = new G4Tubs("OuterXeSolid", 0., outerRadius,
                                  outerHeight/2., 0.*deg, 360.*deg);
  G4LogicalVolume* outerLogic = new G4LogicalVolume(outerSolid, xenon, "OuterXeLogic");
  new G4PVPlacement(0, G4ThreeVector(), outerLogic, "OuterXe", worldLogical, false, 0, true);
  outerLogic->SetVisAttributes(xenonVol);

  // ---------- Sampler2 : coquille sur la surface interne de l'outer ----------
  G4LogicalVolume* logicSampler2 =
      new G4LogicalVolume(shellInside("Sampler2", outerRadius, outerHeight/2.),
                          Vacuum, "Sampler2");
  pSampler2 = new G4PVPlacement(0, G4ThreeVector(), logicSampler2,
                                "Sampler2", outerLogic, false, 0, true);
  logicSampler2->SetVisAttributes(visSampler);
  logicSampler2->SetSensitiveDetector(SamplerSensDet);


  // ---------- Tungstène (daughter outer) ----------
  G4Tubs* tungstenSolid = new G4Tubs("InnerTungstenSolid", 0., wRadius, wHalfH,
                                     0.*deg, 360.*deg);
  G4LogicalVolume* innerTungstenLogic =
      new G4LogicalVolume(tungstenSolid, tungsten, "InnerTungstenLogic");
  new G4PVPlacement(0, G4ThreeVector(), innerTungstenLogic, "InnerTungsten",
                    outerLogic, false, 0, true);
  innerTungstenLogic->SetVisAttributes(tungstenVol);

  // ---------- Sampler1 :shell around tunsgten (dans le xénon extérieur) ----------
  G4Tubs* s1Big   = new G4Tubs("Sampler1_big",   0., wRadius + sampler_thickness, wHalfH + sampler_thickness, 0.*deg, 360.*deg);
  G4Tubs* s1Small = new G4Tubs("Sampler1_small", 0., wRadius,     wHalfH,     0.*deg, 360.*deg);
  G4SubtractionSolid* solidSampler1 = new G4SubtractionSolid("Sampler1", s1Big, s1Small);
  G4LogicalVolume* logicSampler1 = new G4LogicalVolume(solidSampler1, Vacuum, "Sampler1");
  pSampler1 = new G4PVPlacement(0, G4ThreeVector(), logicSampler1,
                                "Sampler1", outerLogic, false, 0, true);
  logicSampler1->SetVisAttributes(visSampler);
  logicSampler1->SetSensitiveDetector(SamplerSensDet);

  // ---------- Xénon intérieur (fille du tungstène) ----------
  G4Tubs* innerSolid = new G4Tubs("InnerXeSolid", 0., innerRadius,
                                  innerHeight/2., 0.*deg, 360.*deg);
  G4LogicalVolume* innerLogic = new G4LogicalVolume(innerSolid, xenon, "InnerXeLogic");
  new G4PVPlacement(0, G4ThreeVector(), innerLogic, "InnerXe",
                    innerTungstenLogic, false, 0, true);   // <-- mère = tungstène
  innerLogic->SetVisAttributes(xenonVol);

  // ---------- Sampler0 : coquille sur la surface interne du xénon intérieur ----------
  G4LogicalVolume* logicSampler0 =
      new G4LogicalVolume(shellInside("Sampler0", innerRadius, innerHeight/2.),
                          Vacuum, "Sampler0");
  pSampler0 = new G4PVPlacement(0, G4ThreeVector(), logicSampler0,
                                "Sampler0", innerLogic, false, 0, true);
  logicSampler0->SetVisAttributes(visSampler);
  logicSampler0->SetSensitiveDetector(SamplerSensDet);
}

#if 0
void XeB2BDetectorConstruction::SetupGeometry()
{
  const G4double sampler_thickness = 1.*um;

  // ---------- World ----------
  G4VSolid* worldSolid = new G4Box("World", 2.*m, 2.*m, 2.*m);
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid, Vacuum, "World");
  worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogical, "World", 0, false, 0);

  // Rotation de 90° autour de Y (axe du cylindre -> X)
  G4RotationMatrix* rotation = new G4RotationMatrix();
  rotation->rotateY(M_PI / 2);
  G4RotationMatrix *pRotX90 = new G4RotationMatrix();
  pRotX90->rotateX(90. * deg);
  // ---------- Dimensions ----------
  G4double innerRadius = 5.*cm;
  G4double innerHeight = 50.*cm;
  G4double outerRadius = 50.*cm;
  G4double outerHeight = 100.*cm;
  G4double thicknesstungsten = 5.*mm;
  // ---------- Visualisation ----------
  G4VisAttributes* visSampler = new G4VisAttributes(G4Colour(1.0, 1.0, 0.));
  visSampler->SetVisibility(true);
  G4VisAttributes* xenonVol = new G4VisAttributes(G4Colour(.0, 1.0, 0.));
  xenonVol->SetVisibility(true);
  G4VisAttributes* tungstenVol = new G4VisAttributes(G4Colour(.0, .0, 1.));
  tungstenVol->SetVisibility(true);

  // ---------- Sensitive detector (créé UNE fois, avant usage) ----------
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SamplerSensDet = new XeB2BSamplerSD("XeB2BSamplerSD");
  SDman->AddNewDetector(SamplerSensDet);

  // ---------- Outer cylinder (xénon) ----------
  G4Tubs* outerSolid = new G4Tubs("OuterXeSolid", 0., outerRadius,
                                  outerHeight/2., 0.*deg, 360.*deg);
  G4LogicalVolume* outerLogic = new G4LogicalVolume(outerSolid, xenon, "OuterXeLogic");
  new G4PVPlacement(0, G4ThreeVector(), outerLogic, "OuterXe",
                    worldLogical, false, 0, true);
  outerLogic->SetVisAttributes(xenonVol);

  // ---------- Sampler2 : coquille à la surface de l'outer ----------
  G4Tubs* solidSampler2 = new G4Tubs("Sampler2",
                                     0,
                                     outerRadius-sampler_thickness,
                                     outerHeight/2.-sampler_thickness,
                                     0.*deg, 360.*deg);
  G4LogicalVolume* logicSampler2 = new G4LogicalVolume(solidSampler2, Vacuum, "Sampler2");
  pSampler2 = new G4PVPlacement(0, G4ThreeVector(), logicSampler2,
                                "Sampler1", outerLogic, false, 0, true);
  logicSampler2->SetVisAttributes(visSampler);
  logicSampler2->SetSensitiveDetector(SamplerSensDet);

  // ---------- Tungsten cylinder ----------
  G4Tubs* solidSampler1 = new G4Tubs("Sampler1",
                                     0,
                                     innerRadius+thicknesstungsten + sampler_thickness,
                                     innerHeight/2.+thicknesstungsten+sampler_thickness,
                                     0.*deg, 360.*deg);
  G4LogicalVolume* logicSampler1 = new G4LogicalVolume(solidSampler1, Vacuum, "Sampler1");
  pSampler1 = new G4PVPlacement(0, G4ThreeVector(), logicSampler1,
                                "Sampler1", logicSampler2, false, 0, true);
  logicSampler1->SetVisAttributes(visSampler);
  logicSampler1->SetSensitiveDetector(SamplerSensDet);

   G4Tubs* tungstenSolid = new G4Tubs("InnerTungstenSolid", 0, innerRadius+thicknesstungsten,
                                  innerHeight/2.+thicknesstungsten, 0.*deg, 360.*deg);
  G4LogicalVolume* innerTungstenLogic = new G4LogicalVolume(tungstenSolid, tungsten, "InnerTungstenLogic");
  new G4PVPlacement(0,                    //
                    G4ThreeVector(),
                    innerTungstenLogic,
                    "InnerTungsten",
                    logicSampler1,           //
                    false, 0, true);
  innerTungstenLogic->SetVisAttributes(tungstenVol);

  // Inner cylinder Xenon
  G4Tubs* innerSolid = new G4Tubs("InnerXeSolid", 0., innerRadius,
                                  innerHeight/2., 0.*deg, 360.*deg);
  G4LogicalVolume* innerLogic = new G4LogicalVolume(innerSolid, xenon, "InnerXeLogic");
  new G4PVPlacement(0,                    //
                    G4ThreeVector(),
                    innerTungstenLogic,
                    "InnerXe",
                    outerLogic,           //
                    false, 0, true);
  innerLogic->SetVisAttributes(xenonVol);
  //
  // ---------- Sampler0 : coquille autour de l'inner, FILLE de l'outer ----------
  G4Tubs* solidSampler0 = new G4Tubs("Sampler0",
                                     0,
                                     innerRadius - sampler_thickness,
                                     innerHeight/2.- sampler_thickness,
                                     0.*deg, 360.*deg);
  G4LogicalVolume* logicSampler0 = new G4LogicalVolume(solidSampler0, Vacuum, "Sampler0");
  pSampler0 = new G4PVPlacement(0, G4ThreeVector(), logicSampler0,
                                "Sampler0", innerLogic, false, 0, true);
  logicSampler0->SetVisAttributes(visSampler);
  logicSampler0->SetSensitiveDetector(SamplerSensDet);
}
#endif
