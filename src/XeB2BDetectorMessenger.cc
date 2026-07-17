//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/* 
 XeB2B code.   
 dadoun@lal.in2p3.fr 
 */
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
#include "XeB2BDetectorMessenger.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BDetectorMessenger::XeB2BDetectorMessenger(XeB2BDetectorConstruction * Det)
:Detector(Det)
{ 
    G4cout << "XeB2BDetectorMessenger created" << G4endl;

    detDir = new G4UIdirectory("/xeb2b/det/");
    detDir->SetGuidance("Detector construction");

    CylinderThicknessCmd = new G4UIcmdWithADoubleAndUnit("/xeb2b/det/cylinderthickness",this);
    CylinderThicknessCmd->SetGuidance("Set Cylinder Thickness");
    CylinderThicknessCmd->SetParameterName("cylinderthickness",false);
    CylinderThicknessCmd->SetRange("cylinderthickness>=0.");
    CylinderThicknessCmd->SetUnitCategory("Length");
    CylinderThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BDetectorMessenger::~XeB2BDetectorMessenger()
{ 
	delete CylinderThicknessCmd;
}

void XeB2BDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 

   if( command == CylinderThicknessCmd )
    {
        Detector->SetCylinderThickness(CylinderThicknessCmd->GetNewDoubleValue(newValue));
	}
    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
