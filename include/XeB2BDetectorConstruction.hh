// DetectorConstruction.hh
#ifndef XEB2BDETECTOR_CONSTRUCTION_HH
#define XEB2BDETECTOR_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4LogicalVolume.hh"

class XeB2BDetectorConstruction : public G4VUserDetectorConstruction {
public:
    XeB2BDetectorConstruction();
    ~XeB2BDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* logicalInnerXenon;
    G4LogicalVolume* logicalOuterXenon;
};

#endif
