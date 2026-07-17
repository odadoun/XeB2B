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
	
	PositionOffsetCmd = new G4UIcmdWith3VectorAndUnit("/xe2b2/gun/offset_position",this);  
	PositionOffsetCmd->SetGuidance("Set Primary Position offset ");
        PositionOffsetCmd->SetUnitCandidates("um");
	
	AngleOffsetCmd = new G4UIcmdWithADouble("/xe2b2/gun/offset_angle",this);
        AngleOffsetCmd->SetGuidance("Set Primary Angle offset");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BPrimaryGeneratorMessenger::~XeB2BPrimaryGeneratorMessenger()
{
	delete PositionOffsetCmd;
	delete gunDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void XeB2BPrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
if( command == PositionOffsetCmd )
	{ 	
		(XeB2BAction->SetPositionOffset(PositionOffsetCmd->GetNew3VectorValue(newValue)));
	}
if( command == AngleOffsetCmd )
	{ 	
		(XeB2BAction->SetAngleOffset(AngleOffsetCmd->GetNewDoubleValue(newValue)));
	}
	
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

