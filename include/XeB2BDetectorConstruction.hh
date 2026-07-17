#ifndef XeB2BDetectorConstruction_h
#define XeB2BDetectorConstruction_h 1

#include "XeB2BSamplerSD.hh"
#include "XeB2BDetectorMessenger.hh"
#include "Xenon1tMaterials.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"


class G4VPhysicalVolume;
class G4Material;
class XeB2BDetectorMessenger;
class XeB2BDetectorConstruction : public G4VUserDetectorConstruction
{
	public:
		XeB2BDetectorConstruction();
		virtual ~XeB2BDetectorConstruction();

	public:
		virtual G4VPhysicalVolume* Construct();
		XeB2BDetectorMessenger* fMessenger;
		
		void SetCylinderThickness(G4double thickness){itsthickness=thickness;}
   		G4double GetCylinderThickness() {return itsthickness;}



	private:
		void DefineMaterials();
		void SetupGeometry();
	        void UpdateGeometry();
   		G4double itsthickness;
	private:
		G4Material* air;
		G4Material* water;
		G4Material* Vacuum;
		G4Material* Al;
		G4Material* Fe;
		G4Material* Cu;
		G4Material* Tungsten;
		G4Material* Be;
                Xenon1tMaterials *Materials;
		G4Material *xenon;
		G4Material *vacuum;

		G4Material* quartz;
		G4VPhysicalVolume* worldPhys;
		G4VPhysicalVolume*    pSampler0;
		G4VPhysicalVolume*    pSampler1;
		G4VPhysicalVolume*    pSampler2;
		G4VPhysicalVolume*    pSampler3;
		G4VPhysicalVolume*    pSampler4;
		XeB2BSamplerSD*	      SamplerSensDet;	

		G4VPhysicalVolume* capillaryPhys;
		G4VPhysicalVolume* beampipePhys;
		G4VPhysicalVolume* BePhys1;
		G4VPhysicalVolume* BePhys2;
		G4VPhysicalVolume* collimator1_Phys;
		G4VPhysicalVolume* collimator2_Phys;
		G4VPhysicalVolume* collimator3_Phys;
		G4bool constructed;


	public:
		const G4VPhysicalVolume*  GetCollimator1()               {return collimator1_Phys;}
		const G4VPhysicalVolume*  GetCollimator2()               {return collimator2_Phys;}
		const G4VPhysicalVolume*  GetCollimator3()               {return collimator3_Phys;}

		void SetPositionOffsetColl1(G4ThreeVector position1);
		G4ThreeVector GetPositionOffsetColl1(){return itsposition1;}

		void SetPositionOffsetColl2(G4ThreeVector position2);
		G4ThreeVector GetPositionOffsetColl2(){return itsposition2;}

		void SetPositionOffsetColl3(G4ThreeVector position3);
		G4ThreeVector GetPositionOffsetColl3(){return itsposition3;}

	private:
		G4ThreeVector itsposition1;
		G4ThreeVector itsposition2;
		G4ThreeVector itsposition3;
};

#endif

