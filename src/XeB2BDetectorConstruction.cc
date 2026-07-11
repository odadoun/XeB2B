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
G4double samplerZ  = 2.E-11 * m;
G4double samplerXY = 40.*cm;//40.*cm;

G4double pRmin = 0.089*mm;
G4double pRmax = 2.75*mm;
G4double capillaryThickness =  pRmax - pRmin;
G4double capillary_length = 30. * mm;
G4double Be_thickness = 150. * micrometer ;

using namespace CLHEP;

XeB2BDetectorConstruction::XeB2BDetectorConstruction()
:constructed(false)
{;}

XeB2BDetectorConstruction::~XeB2BDetectorConstruction()
{;}

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
  //
  // World
  //

  G4VSolid* worldSolid = new G4Box("World",2.*m,2.*m,2.*m);
  G4LogicalVolume* worldLogical = new G4LogicalVolume(worldSolid,Vacuum,"World");
  worldPhys = new G4PVPlacement(0,G4ThreeVector(),worldLogical,"World", 0,false,0);

   G4double current_position = -13.*cm;
	//Sampler0
	G4Box* solidSampler0 = new G4Box("Sampler0", samplerXY/2., samplerXY/2., samplerZ/2.);
  G4VisAttributes* LogVisAttSampler= new G4VisAttributes(G4Colour(1.0,1.0,0.));
	//LogVisAttSampler->SetForceSolid(true);
	LogVisAttSampler->SetVisibility(false);
  G4ThreeVector positionSampler0= G4ThreeVector(0.,0.,current_position);
  G4LogicalVolume* logicSampler0 = new G4LogicalVolume(solidSampler0,Vacuum,"Sampler0");
  pSampler0 = new G4PVPlacement(0,positionSampler0,logicSampler0,"Sampler0",worldLogical,false,0);
  logicSampler0 ->SetVisAttributes(LogVisAttSampler);

	G4SDManager* SDman = G4SDManager::GetSDMpointer();

	SamplerSensDet = new XeB2BSamplerSD("XeB2BSamplerSD");
	SDman->AddNewDetector(SamplerSensDet);
	logicSampler0->SetSensitiveDetector(SamplerSensDet);

  current_position = -10*cm ;
  G4ThreeVector positionSampler1= G4ThreeVector(0.,0.,current_position+samplerZ/2.);
  G4LogicalVolume* logicSampler1 = new G4LogicalVolume(solidSampler0,Vacuum,"Sampler1");
  pSampler1 = new G4PVPlacement(0,positionSampler1,logicSampler0,"Sampler1",worldLogical,false,0);
  logicSampler1 -> SetVisAttributes(LogVisAttSampler);
  logicSampler1 -> SetSensitiveDetector(SamplerSensDet);


  //G4NistManager* nist = G4NistManager::Instance();
  //G4Material* xenon = nist->FindOrBuildMaterial("G4_XENON");

// Grand cylindre de xénon
G4double outerRadius = 50.*cm;
G4double outerHeight = 100.*cm;

G4RotationMatrix* rotation = new G4RotationMatrix();
rotation->rotateY(M_PI / 2);  // Rotation de 90° autour de Y pour aligner sur X

G4Tubs* outerSolid =
    new G4Tubs("OuterXeSolid",
               0.,
               outerRadius,
               outerHeight/2.,
               0.*deg,
               360.*deg);

G4LogicalVolume* outerLogic =
    new G4LogicalVolume(outerSolid,
                        xenon,
                        "OuterXeLogic");

new G4PVPlacement(rotation,
                  G4ThreeVector(),
                  outerLogic,
                  "OuterXe",
                  worldLogical,
                  false,
                  0,
                  true);


// Petit cylindre de xénon au centre
G4double innerRadius = 20.*cm;
G4double innerHeight = 50.*cm;

G4Tubs* innerSolid =
    new G4Tubs("InnerXeSolid",
               0.,
               innerRadius,
               innerHeight/2.,
               0.*deg,
               360.*deg);

G4LogicalVolume* innerLogic =
    new G4LogicalVolume(innerSolid,
                        xenon,
                        "InnerXeLogic");

new G4PVPlacement(nullptr,
                  G4ThreeVector(0,0,0),
                  innerLogic,
                  "InnerXe",
                  outerLogic,
                  false,
                  0,
                  true);

}
