#ifndef XeB2BRunAction_h
#define XeB2BRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <fstream>
using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BDetectorConstruction;
class XeB2BPrimaryGeneratorAction;
class G4Run;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class XeB2BRunAction : public G4UserRunAction
{
	public:
		XeB2BRunAction(XeB2BDetectorConstruction*, XeB2BPrimaryGeneratorAction*);
		virtual ~XeB2BRunAction();
		
		void   BeginOfRunAction(const G4Run*);
		void   EndOfRunAction(const G4Run*);
		
		void CountProcesses(G4String);
		
		void SetColl1EDep(G4double tot_coll1_edep);
		G4double GetColl1EDep2();
		void SetColl1EDep2(G4double tot_coll1_edep2);
		G4double GetColl1EDep();
	    G4int nb_coll1_edep;
		
		void SetColl2EDep(G4double tot_coll2_edep);
		G4double GetColl2EDep();
		void SetColl2EDep2(G4double tot_coll2_edep2);
		G4double GetColl2EDep2();
	    G4int nb_coll2_edep;
	
		void SetColl3EDep(G4double tot_coll3_edep);
		G4double GetColl3EDep();
		void SetColl3EDep2(G4double tot_coll3_edep2);
		G4double GetColl3EDep2();
	    G4int nb_coll3_edep;
	    G4int countkiller;			
	 
	private:
		XeB2BDetectorConstruction*   detector;
		XeB2BPrimaryGeneratorAction* primary;
		G4double itstotcoll1_edep;
		G4double itstotcoll1_edep2;
		G4double itstotcoll2_edep;
		G4double itstotcoll2_edep2;
		G4double itstotcoll3_edep;
		G4double itstotcoll3_edep2;
};
inline void XeB2BRunAction::SetColl1EDep(G4double tot_coll1_edep)
{itstotcoll1_edep = tot_coll1_edep;}
inline G4double XeB2BRunAction::GetColl1EDep() {return itstotcoll1_edep;}

inline void XeB2BRunAction::SetColl1EDep2(G4double tot_coll1_edep2)
{itstotcoll1_edep2 = tot_coll1_edep2;}
inline G4double XeB2BRunAction::GetColl1EDep2() {return itstotcoll1_edep2;}


inline void XeB2BRunAction::SetColl2EDep(G4double tot_coll2_edep)
{itstotcoll2_edep = tot_coll2_edep;}
inline G4double XeB2BRunAction::GetColl2EDep() {return itstotcoll2_edep;}

inline void XeB2BRunAction::SetColl2EDep2(G4double tot_coll2_edep2)
{itstotcoll2_edep2 = tot_coll2_edep2;}
inline G4double XeB2BRunAction::GetColl2EDep2() {return itstotcoll2_edep2;}

inline void XeB2BRunAction::SetColl3EDep(G4double tot_coll3_edep)
{itstotcoll3_edep = tot_coll3_edep;}
inline G4double XeB2BRunAction::GetColl3EDep() {return itstotcoll3_edep;}

inline void XeB2BRunAction::SetColl3EDep2(G4double tot_coll3_edep2)
{itstotcoll3_edep2 = tot_coll3_edep2;}
inline G4double XeB2BRunAction::GetColl3EDep2() {return itstotcoll3_edep2;}

#endif

