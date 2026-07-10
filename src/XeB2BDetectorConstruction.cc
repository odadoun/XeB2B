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

#include "G4ios.hh"

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
		
	//  XeB2Bllary
        current_position = -10.*cm;
	G4Tubs* capillarySolid = new G4Tubs("XeB2Bllary", pRmin, pRmin+capillaryThickness, capillary_length/2., 0., 360.*deg);
	G4LogicalVolume* capillaryLogical = new G4LogicalVolume(capillarySolid,quartz,"XeB2Bllary");
	capillaryPhys = new G4PVPlacement(0,G4ThreeVector(0.,0,current_position-capillary_length/2.),capillaryLogical,"XeB2Bllary", worldLogical,false,0);
	G4VisAttributes * capillaryVisAtt       = new G4VisAttributes ( G4Colour(1.0,1.0,0.));// G4Colour(153/255. ,255/255. ,153/255. )); //green
	capillaryVisAtt->SetVisibility(true);
	//capillaryVisAtt->SetForceWireframe (true);
    
	capillaryVisAtt->SetForceSolid(true);
	capillaryLogical->SetVisAttributes(capillaryVisAtt);

	//Sampler1
    current_position = -10*cm ;
    G4ThreeVector positionSampler1= G4ThreeVector(0.,0.,current_position+samplerZ/2.);
    G4LogicalVolume* logicSampler1 = new G4LogicalVolume(solidSampler0,Vacuum,"Sampler1");
    pSampler1 = new G4PVPlacement(0,positionSampler1,logicSampler0,"Sampler1",worldLogical,false,0);
    logicSampler1 -> SetVisAttributes(LogVisAttSampler);
    logicSampler1 -> SetSensitiveDetector(SamplerSensDet);

    
    current_position +=samplerZ;
    
//magnet
	G4double length_mag=12.*cm;
	G4VSolid* outersolid =
    new G4Box("outersolid", 55*mm/2., 70*mm/2., length_mag/2.);  
	
	G4VSolid* innersolid =
    new G4Box("innersolid", 15*mm/2., 50*mm/2.,(length_mag+0.01*cm)/2.);  
    
    G4VSolid* magnet
    = new G4SubtractionSolid("magnet",outersolid,innersolid);
    
    G4LogicalVolume* magnetLogical = new G4LogicalVolume(magnet,Fe,"magnet");
    G4VPhysicalVolume* magnetPhys = new G4PVPlacement(0,G4ThreeVector(0.,-16*mm,length_mag/2.),magnetLogical,"magnet", worldLogical,false,0);
    G4VisAttributes * magnetVisAtt       = new G4VisAttributes ( G4Colour(204/255. ,204/255. ,255/255. )); //metal
    magnetVisAtt->SetVisibility(true);
//    magnetVisAtt->SetForceWireframe (true);
  //  magnetVisAtt->SetForceAuxEdgeVisible(true);
    magnetVisAtt->SetForceSolid(true);
    magnetLogical->SetVisAttributes(magnetVisAtt);
    
    
    //Vaccum sphere
	G4double radius=60*cm;
	G4double radius_max=radius + 5.7*cm;
	G4Sphere* sphereSolid = new G4Sphere("sphere",radius,radius_max,  0*deg,360*deg,0*deg,360*deg);
	// Vacccum beampipe
	G4double beampipe_length = 35. * cm;
	G4double beampipe_length2 = beampipe_length + 5.7*cm+1*cm;
	G4Tubs* beampipeSolid1 = new G4Tubs("beampipe", 0.*cm, 6.*cm, beampipe_length/2., 0., 360.*deg);
	G4Tubs* beampipeSolid2 = new G4Tubs("beampipe", 0.*cm, 5.*cm, beampipe_length2/2., 0., 360.*deg);
	
G4VSolid* substract1
        = new G4UnionSolid("vacuum_chamber1", sphereSolid,beampipeSolid1,0,G4ThreeVector(0.,0.,radius_max+beampipe_length/2));
G4SubtractionSolid* substract2
        = new G4SubtractionSolid("vacuum_chamber2", substract1,beampipeSolid2,0,G4ThreeVector(0.,0.,radius+beampipe_length2/2));

	//G4LogicalVolume* beampipeLogical = new G4LogicalVolume(beampipeSolid,Fe,"beampipe");
	G4LogicalVolume* beampipeLogical = new G4LogicalVolume(substract2,Al,"beampipe");
	beampipePhys = new G4PVPlacement(0,G4ThreeVector(0.,0,0*cm),beampipeLogical,"beampipe", worldLogical,false,0);
	G4VisAttributes * beampipeVisAtt       = new G4VisAttributes ( G4Colour(204/255. ,204/255. ,255/255. )); //metal
	beampipeVisAtt->SetVisibility(false);
//	beampipeVisAtt->SetForceWireframe (true);
//	beampipeVisAtt->SetForceAuxEdgeVisible(true);
	beampipeVisAtt->SetForceSolid(true);
	beampipeLogical->SetVisAttributes(beampipeVisAtt);
	
    current_position = 95.*cm;
    // Berylium Windows 1
	
G4Tubs* BeSolid = new G4Tubs("berylium_window", 0.*cm, 6.*cm, Be_thickness/2., 0., 360.*deg);
	G4LogicalVolume* BeLogical1 = new G4LogicalVolume(BeSolid,Be,"berylium_window1");
	BePhys1 = new G4PVPlacement(0,G4ThreeVector(0.,0,current_position+Be_thickness/2.),BeLogical1,"berylium_window1", worldLogical,false,0);
	G4VisAttributes * BeVisAtt       = new G4VisAttributes (G4Colour(0/255. ,204/255. ,204/255.   )); //metal
    BeVisAtt->SetVisibility(true);
//	BeVisAtt->SetForceWireframe (true);
    
	BeVisAtt->SetForceSolid(true);
	BeLogical1->SetVisAttributes(BeVisAtt);
    
current_position += Be_thickness;
  
//air 
    G4double air_tube = 5. * cm;
	G4Tubs* airSolid = new G4Tubs("air", 5.*cm, 6.*cm,air_tube/2., 0., 360.*deg);
    G4LogicalVolume* airLogical = new G4LogicalVolume(airSolid,air,"air");
    G4VPhysicalVolume *airPhys = new G4PVPlacement(0,G4ThreeVector(0.,0,current_position+air_tube/2),airLogical,"air", worldLogical,false,0);
    current_position += air_tube;

//Berylium Windows 2
    G4LogicalVolume* BeLogical2 = new G4LogicalVolume(BeSolid,Be,"berylium_window2");
    BePhys2 = new G4PVPlacement(0,G4ThreeVector(0.,0,current_position+Be_thickness/2.),BeLogical2,"berylium_window2",worldLogical,false,0);
    BeLogical2 -> SetVisAttributes(BeVisAtt);
    
	current_position +=Be_thickness;
    //Sampler
    G4ThreeVector positionSampler2= G4ThreeVector(0.,0.,current_position+samplerZ/2.);
    G4LogicalVolume* logicSampler2 = new G4LogicalVolume(solidSampler0,Vacuum,"Sampler2");
    pSampler2 = new G4PVPlacement(0,positionSampler2,logicSampler0,"Sampler2",worldLogical,false,0);
    logicSampler2 -> SetVisAttributes(LogVisAttSampler);
    LogVisAttSampler->SetVisibility(false);
    
}


