// PhysicsList.cc
#include "XeB2BPhysicsList.hh"
#include "G4EmStandardPhysics.hh"

XeB2BPhysicsList::XeB2BPhysicsList() {
    RegisterPhysics(new G4EmStandardPhysics());
}

XeB2BPhysicsList::~XeB2BPhysicsList() {}
