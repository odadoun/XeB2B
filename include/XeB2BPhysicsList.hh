#ifndef XeB2BPhysicsList_h
#define XeB2BPhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "globals.hh"

class XeB2BPhysicsList: public G4VUserPhysicsList
{
public:
  XeB2BPhysicsList();
  virtual ~XeB2BPhysicsList();

  // Construct particle and physics
  void ConstructParticle();
  void ConstructProcess();
 
  void SetCuts();
   
private:
  // these methods Construct particles 
  void ConstructBosons();
  void ConstructLeptons();
  void ConstructMesons();
  void ConstructBaryons();

  // these methods Construct physics processes and register them
  void ConstructDecay();
  void ConstructEM();
  //void ConstructEM_Low_Energy();
};


#endif



