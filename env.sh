#!/bin/bash
#source /usr/local/geant4/10.06.p03/bin/geant4.sh
source /usr/local/geant4/geant4-v11.4.0-install/bin/geant4.sh

#export CMAKE_PREFIX_PATH=/usr/local/geant4/10.06.p03/lib/Geant4-11.2.1/
export CMAKE_PREFIX_PATH=/usr/local/geant4/geant4-v11.4.0-install/lib/Geant4-10.6.3
export ROOTSYS=/usr/local/Cellar/root/ #/usr/local/root/root5.34/

export G4DATA=/usr/local/geant4/geant4-v10.6.3-build/data
export G4LEDATA=$G4DATA/G4EMLOW7.13
export G4SAIDDATA=$G4DATA/G4SAIDDATA2.0/
export G4NEUTRONHPDATA=$G4DATA/G4NDL4.6
export G4ENSDFSTATEDATA=$G4DATA/G4NDL4.6
export G4NEUTRONXSDATA=$G4DATA/G4NEUTRONXS1.4
export G4LEVELGAMMADATA=$G4DATA/PhotonEvaporation5.7
export G4RADIOACTIVEDATA=$G4DATA/RadioactiveDecay5.4
export NeutronHPCrossSections=$G4DATA/G4NDL4.6
export G4REALSURFACEDATA=$G4DATA/RealSurface2.2
export G4PIIDATA=$G4DATA/G4PII1.3
export G4ENSDFSTATEDATA=$G4DATA/G4ENSDFSTATE2.2
export G4PARTICLEXSDATA=$G4DATA/G4PARTICLEXS3.1.1
