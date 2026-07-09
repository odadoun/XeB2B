// DetectorConstruction.cc
#include "XeB2BDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

XeB2BDetectorConstruction::XeB2BDetectorConstruction() {}

XeB2BDetectorConstruction::~XeB2BDetectorConstruction() {}

G4VPhysicalVolume* XeB2BDetectorConstruction::Construct() {
    // Matériau : Xénon gazeux
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* xenon = nist->FindOrBuildMaterial("G4_Xe");

    // Monde (vide)
    G4Box* solidWorld = new G4Box("World", 1.0*m, 1.0*m, 1.0*m);
    G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "World");
    G4VPhysicalVolume* physicalWorld = new G4PVPlacement(0, G4ThreeVector(), logicalWorld, "World", 0, false, 0);

    // World visualization attributes (light blue, transparent)
    G4VisAttributes* worldAttributes = new G4VisAttributes(G4Colour(0.5, 0.8, 1.0, 0.1)); // RGBA
    worldAttributes->SetVisibility(true);
    worldAttributes->SetDaughtersInvisible(false);
    logicalWorld->SetVisAttributes(worldAttributes);

    // Cylindre externe (Xénon)
    G4Tubs* solidOuterXenon = new G4Tubs("OuterXenon", 0., 0.5*m, 1.0*m, 0., 360.*deg);
    logicalOuterXenon = new G4LogicalVolume(solidOuterXenon, xenon, "OuterXenon");
    new G4PVPlacement(0, G4ThreeVector(), logicalOuterXenon, "OuterXenon", logicalWorld, false, 0);

    // Outer xenon visualization attributes (cyan, semi-transparent)
    G4VisAttributes* outerXenonAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0, 0.3)); // Cyan
    outerXenonAttributes->SetVisibility(true);
    outerXenonAttributes->SetLineWidth(2);
    logicalOuterXenon->SetVisAttributes(outerXenonAttributes);

    // Cylindre interne (Xénon)
    G4Tubs* solidInnerXenon = new G4Tubs("InnerXenon", 0., 0.2*m, 0.5*m, 0., 360.*deg);
    logicalInnerXenon = new G4LogicalVolume(solidInnerXenon, xenon, "InnerXenon");
    new G4PVPlacement(0, G4ThreeVector(), logicalInnerXenon, "InnerXenon", logicalWorld, false, 0);

    // Inner xenon visualization attributes (green, semi-transparent)
    G4VisAttributes* innerXenonAttributes = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0, 0.4)); // Green
    innerXenonAttributes->SetVisibility(true);
    innerXenonAttributes->SetLineWidth(2);
    logicalInnerXenon->SetVisAttributes(innerXenonAttributes);

    return physicalWorld;
}
