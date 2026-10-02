//....oo:oOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2BIM code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "XeB2BPrimaryGeneratorMessenger.hh"
#include "XeB2BPrimaryGeneratorAction.hh"
#include "XeB2BOutput.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern XeB2BOutput rootOutput;

XeB2BPrimaryGeneratorMessenger::XeB2BPrimaryGeneratorMessenger(XeB2BPrimaryGeneratorAction* XeB2BGun)
:XeB2BAction(XeB2BGun)
{
	gunDir = new G4UIdirectory("/xe2b2/gun/");
	gunDir->SetGuidance("PrimaryGenerator control");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BPrimaryGeneratorMessenger::~XeB2BPrimaryGeneratorMessenger()
{
	delete PositionOffsetCmd;
	delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

