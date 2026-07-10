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
#if 0       
    detDir = new G4UIdirectory("/eli/det/");
    detDir->SetGuidance("Detector construction");

    Coll1_positionCmd = new G4UIcmdWith3VectorAndUnit("/eli/det/coll1_position",this);
    Coll1_positionCmd->SetGuidance("Set Position offset collimator 1");
    Coll1_positionCmd->SetUnitCandidates("um");
    
    Coll2_positionCmd = new G4UIcmdWith3VectorAndUnit("/eli/det/coll2_position",this);
    Coll2_positionCmd->SetGuidance("Set Position offset collimator 3");
    Coll2_positionCmd->SetUnitCandidates("um");
    
    Coll3_positionCmd = new G4UIcmdWith3VectorAndUnit("/eli/det/coll3_position",this);
    Coll3_positionCmd->SetGuidance("Set Position offset collimator 3");
    Coll3_positionCmd->SetUnitCandidates("um");
#endif 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

XeB2BDetectorMessenger::~XeB2BDetectorMessenger()
{ 
/*	
    delete Coll1_positionCmd;
    delete Coll2_positionCmd;
    delete Coll3_positionCmd;
    */
}

void XeB2BDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
/*
   if( command == Coll1_positionCmd )
    {
        Detector->SetPositionOffsetColl1(Coll1_positionCmd->GetNew3VectorValue(newValue));
    	G4cout << " ---))))) "  << newValue << G4endl;
	}
    
    if( command == Coll2_positionCmd )
    {
        Detector->SetPositionOffsetColl2(Coll2_positionCmd->GetNew3VectorValue(newValue));
    }
    
    if( command == Coll3_positionCmd )
    {
        Detector->SetPositionOffsetColl3(Coll3_positionCmd->GetNew3VectorValue(newValue));
    }
*/    
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
