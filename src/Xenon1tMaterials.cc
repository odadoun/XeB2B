// XENON Header Files
#include "Xenon1tMaterials.hh"

// G4 Header Files
#include <G4Material.hh>
#include <G4NistManager.hh>
#include <G4SystemOfUnits.hh>

Xenon1tMaterials::Xenon1tMaterials() { ; }

Xenon1tMaterials::~Xenon1tMaterials() { ; }

void Xenon1tMaterials::DefineMaterials(
	G4double pWABSL = 1., 
	G4double pEPTFEReflectivity = 0.9935,
	G4double pGdConcentration = 0.2) {
  G4NistManager *pNistManager = G4NistManager::Instance();

  //========== Elements ==========
  pNistManager->FindOrBuildElement("U");
  G4Element *Xe = new G4Element("Xenon", "Xe", 54., 131.293 * g / mole);
  G4Element *H = new G4Element("Hydrogen", "H", 1., 1.0079 * g / mole);
  G4Element *C = new G4Element("Carbon", "C", 6., 12.011 * g / mole);
  G4Element *N = new G4Element("Nitrogen", "N", 7., 14.007 * g / mole);
  G4Element *O = new G4Element("Oxygen", "O", 8., 15.999 * g / mole);
  G4Element *F = new G4Element("Fluorine", "F", 9., 18.998 * g / mole);
  G4Element *Al = new G4Element("Aluminium", "Al", 13., 26.982 * g / mole);
  G4Element *Si = new G4Element("Silicon", "Si", 14., 28.086 * g / mole);
  G4Element *Cr = new G4Element("Chromium", "Cr", 24., 51.996 * g / mole);
  G4Element *Mn = new G4Element("Manganese", "Mn", 25., 54.938 * g / mole);
  G4Element *Fe = new G4Element("Iron", "Fe", 26., 55.85 * g / mole);
  G4Element *Ni = new G4Element("Nickel", "Ni", 28., 58.693 * g / mole);
  G4Element *Cu = new G4Element("Copper", "Cu", 29., 63.546 * g / mole);
  G4Element *B = pNistManager->FindOrBuildElement("B");
  G4Element *Gd = pNistManager->FindOrBuildElement("Gd");
  // elements for GSRock
  G4Element *Ca = pNistManager->FindOrBuildElement("Ca");
  G4Element *Mg = pNistManager->FindOrBuildElement("Mg");
  G4Element *Co = pNistManager->FindOrBuildElement("Co");
  G4Element *Ti = pNistManager->FindOrBuildElement("Ti");
  G4Element *Mo = pNistManager->FindOrBuildElement("Mo");
  // elements for Concrete
  G4Element *Na = pNistManager->FindOrBuildElement("Na");
  G4Element *P = pNistManager->FindOrBuildElement("P");
  G4Element *S = pNistManager->FindOrBuildElement("S");
  G4Element *K = pNistManager->FindOrBuildElement("K");
  // added from calibsource
  G4Element *W = pNistManager->FindOrBuildElement("W");
  G4Element *Zr = pNistManager->FindOrBuildElement("Zr");
  G4Element *V = pNistManager->FindOrBuildElement("V");
  G4Isotope *D_Iso = new G4Isotope("D_Iso", 1, 2, 2.014102 * g / mole);
  G4Element *D = new G4Element("Deuterium", "D", 1);
  D->AddIsotope(D_Iso, 1);

  //========== Defined from NistManager ==========
  // G4 Aluminium
  pNistManager->FindOrBuildMaterial("G4_Al");
  // G4 Molybdenum
  pNistManager->FindOrBuildMaterial("G4_Mo");
  // G4 Lead
  pNistManager->FindOrBuildMaterial("G4_Pb");
  // G4 Copper
  pNistManager->FindOrBuildMaterial("G4_Cu");
  // PVC Pipe
  pNistManager->FindOrBuildMaterial("G4_POLYVINYL_CHLORIDE");
  // Plexiglass
  pNistManager->FindOrBuildMaterial("G4_PLEXIGLASS");

  //==== Gran Sasso Rock ==== // PAOLO
  G4Material *GSrock = new G4Material("GSrock", 2.71 * g / cm3, 6);
  GSrock->AddElement(O, 0.51);
  GSrock->AddElement(Ca, 0.27);
  GSrock->AddElement(C, 0.12);
  GSrock->AddElement(Mg, 0.084);
  GSrock->AddElement(Si, 0.01);
  GSrock->AddElement(Al, 0.006);

  //==== LNGS Concrete ==== // PAOLO
  G4Material *Concrete = new G4Material("Concrete", 2.4 * g / cm3, 13);
  G4double FactorToFixConcreteFraction = 1./0.9879;
  // 0.9879 was shown in G4 runtime error message
  // Original fraction of components is refered in 
  // https://arxiv.org/pdf/hep-ex/0312050.pdf (Table 4)
  Concrete->AddElement(H, 0.0089  * FactorToFixConcreteFraction);
  Concrete->AddElement(C, 0.0799  * FactorToFixConcreteFraction);
  Concrete->AddElement(O, 0.4843  * FactorToFixConcreteFraction);
  Concrete->AddElement(Na, 0.006  * FactorToFixConcreteFraction);
  Concrete->AddElement(Mg, 0.0085 * FactorToFixConcreteFraction);
  Concrete->AddElement(Al, 0.009  * FactorToFixConcreteFraction);
  Concrete->AddElement(Si, 0.0386 * FactorToFixConcreteFraction);
  Concrete->AddElement(P, 0.0004  * FactorToFixConcreteFraction);
  Concrete->AddElement(S, 0.0016  * FactorToFixConcreteFraction);
  Concrete->AddElement(K, 0.0054  * FactorToFixConcreteFraction);
  Concrete->AddElement(Ca, 0.3406 * FactorToFixConcreteFraction);
  Concrete->AddElement(Ti, 0.0004 * FactorToFixConcreteFraction);
  Concrete->AddElement(Fe, 0.0043 * FactorToFixConcreteFraction);

  //==== Water ====
  G4Material *Water = new G4Material("Water", 1. * g / cm3, 2, kStateLiquid);
  Water->AddElement(H, 2);
  Water->AddElement(O, 1);
  // optical properties
  G4MaterialPropertiesTable *WaterMPT = SetWaterOpticalProperties(pWABSL);
  Water->SetMaterialPropertiesTable(WaterMPT);

  //==== Gd2(SO4)3 8H20 ====
  G4Material *Gd2S3O12 = new G4Material( "Gd2S3O12", 4.139*g/cm3, 4, kStateSolid);
  Gd2S3O12->AddElement( Gd, 2 );
  Gd2S3O12->AddElement( S, 3 );
  Gd2S3O12->AddElement( H, 16 );
  Gd2S3O12->AddElement( O, 20 );

  //==== Gd-loaded Water ====
  double conc = pGdConcentration / 0.4211; // Gd mass concentration (default 0.2%, 
					   // corresponding to 0.5% GdSO concentration)

  G4cout << 
      "Xenon1tMaterials : Gadolinium mass concentration set to: " 
			   << pGdConcentration << G4endl; 
	
  G4Material *GdWater = new G4Material( "GdWater", 1.006278*g/cm3, 2, kStateLiquid);
  GdWater->AddMaterial( Water,    (100.0 - conc)*0.01 );
  GdWater->AddMaterial( Gd2S3O12, conc*0.01 );
  // optical properties
  G4MaterialPropertiesTable *GdWaterMPT = SetGdWaterOpticalProperties(pWABSL);
  GdWater->SetMaterialPropertiesTable(GdWaterMPT);

  if (pWABSL != 1){ G4cout << 
      "Xenon1tMaterials : GdWater (or Water) absorption length scaled by a factor " 
			   << pWABSL << G4endl; }

  //Tyvek//
  pNistManager->FindOrBuildMaterial("G4_POLYETHYLENE");
  G4Material* Tyvek = new G4Material("Tyvek", 0.6*g/cm3, 1);
  Tyvek->AddMaterial(G4Material::GetMaterial("G4_POLYETHYLENE"), 100.0*perCent);

  //==== Air ====
  pNistManager->FindOrBuildMaterial("G4_AIR");
  G4Material *Air = G4Material::GetMaterial("G4_AIR");

  // Optical properties of air
  const G4int nEntries = 32;
  G4double PhotonEnergy[nEntries] = {
      2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
      2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
      2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
      2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
      3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
      4.002 * eV, 4.136 * eV};

  G4double RefractiveIndex2[nEntries] = {
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
  G4MaterialPropertiesTable *myMPT2 = new G4MaterialPropertiesTable();
  myMPT2->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex2, nEntries);
  Air->SetMaterialPropertiesTable(myMPT2);

  //==== Vacuum ====
  G4Material *Vacuum = new G4Material("Vacuum", 1.e-20 * g / cm3, 2, kStateGas);
  Vacuum->AddElement(N, 0.755);
  Vacuum->AddElement(O, 0.245);

  // Optical properties of vacuum
  G4double RefractiveIndex3[nEntries] = {
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
      1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00};
  G4MaterialPropertiesTable *myMPT3 = new G4MaterialPropertiesTable();
  myMPT3->AddProperty("RINDEX", PhotonEnergy, RefractiveIndex3, nEntries);
  Vacuum->SetMaterialPropertiesTable(myMPT3);

  //==== Collimator Alloy ====
  G4Material *CollimatorAlloy =
      new G4Material("CollimatorAlloy", 19.25 * g / cm3, 3, kStateSolid);
  CollimatorAlloy->AddElement(W, 0.95);
  CollimatorAlloy->AddElement(Ni, 0.035);
  CollimatorAlloy->AddElement(Cu, 0.015);

  //==== Steel ====
  G4Material *Steel = new G4Material("Steel", 7.7 * g / cm3, 3);
  Steel->AddElement(C, 0.04);
  Steel->AddElement(Fe, 0.88);
  Steel->AddElement(Co, 0.08);

  //==== Low-density polyurethane foam (nVeto displacer) ====
  // DR 20160824
  G4Material *Foam =
      new G4Material("Foam", 0.032 * g / cm3, 4, kStateSolid);  // 2*lb/ft^3
  Foam->AddElement(C, 25);
  Foam->AddElement(H, 42);
  Foam->AddElement(N, 2);
  Foam->AddElement(O, 6);

  //==== Organic Liquid Scintillator (nVeto) ====
  // DR 20160824 - Reference: Daya Bay
  // (http://dx.doi.org/10.1016/j.nima.2014.05.119)
  G4Material *LAB = new G4Material("LAB", 0.863 * g / cm3, 2, kStateLiquid);
  LAB->AddElement(C, 18);
  LAB->AddElement(H, 30);  // C(6)H(5)C(n)H(2n+1) - 'n' typically equal to
                           // 10-13. 12 chosen for this case.

  G4Material *PPO = new G4Material("PPO", 0.882 * g / cm3, 4, kStateSolid);
  PPO->AddElement(C, 15);
  PPO->AddElement(H, 11);
  PPO->AddElement(N, 1);
  PPO->AddElement(O, 1);

  G4Material *LScint =
      new G4Material("LScint", 0.863 * g / cm3, 2, kStateLiquid);
  LScint->AddMaterial(LAB, 0.99654);
  LScint->AddMaterial(PPO, 0.00346);
  // Negligible contribution from bis-MSB (wavelength shifter)
  LScint->GetIonisation()->SetBirksConstant(0.117 * mm / MeV);

  //==== Gd-doped Liquid Scintillator ====
  G4Material *Gd_carboxylate =
      new G4Material("Gd_carboxylate", 2.42 * g / cm3, 4, kStateSolid);
  Gd_carboxylate->AddElement(Gd, 1);
  Gd_carboxylate->AddElement(H, 51);
  Gd_carboxylate->AddElement(C, 27);
  Gd_carboxylate->AddElement(O, 6);

  G4Material *Gd_LScint =
      new G4Material("Gd_LScint", 0.863 * g / cm3, 2, kStateLiquid);
  Gd_LScint->AddMaterial(LScint, 0.996006);
  Gd_LScint->AddMaterial(Gd_carboxylate, 0.003994);
  // Makes 0.1% of Gd in mass.
  Gd_LScint->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);

  // Optical properties of Gd_LScint
  // DR 20160824
  const G4int iNbEntries = 3;
  G4double pdGdLScintPhotonMomentum[iNbEntries] = {2.59 * eV, 2.88 * eV,
                                                   3.17 * eV};
  G4double pdGdLScintScintillation[iNbEntries] = {0.1, 1.0, 0.1};
  G4double pdGdLScintRefractiveIndex[iNbEntries] = {1.5, 1.5, 1.49};
  G4double pdGdLScintAbsorbtionLength[iNbEntries] = {
      30. * m, 30. * m, 30. * m};  // With L_att = 14.5m
  G4double pdGdLScintScatteringLength[iNbEntries] = {27. * m, 27. * m, 27. * m};
  G4MaterialPropertiesTable *pGdLScintPropertiesTable =
      new G4MaterialPropertiesTable();
  pGdLScintPropertiesTable->AddProperty("FASTCOMPONENT",
                                        pdGdLScintPhotonMomentum,
                                        pdGdLScintScintillation, iNbEntries);
  pGdLScintPropertiesTable->AddProperty("SLOWCOMPONENT",
                                        pdGdLScintPhotonMomentum,
                                        pdGdLScintScintillation, iNbEntries);
  pGdLScintPropertiesTable->AddProperty("RINDEX", pdGdLScintPhotonMomentum,
                                        pdGdLScintRefractiveIndex, iNbEntries);
  pGdLScintPropertiesTable->AddProperty("ABSLENGTH", pdGdLScintPhotonMomentum,
                                        pdGdLScintAbsorbtionLength, iNbEntries);
  pGdLScintPropertiesTable->AddProperty("RAYLEIGH", pdGdLScintPhotonMomentum,
                                        pdGdLScintScatteringLength, iNbEntries);
  pGdLScintPropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
  pGdLScintPropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
  pGdLScintPropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
  pGdLScintPropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
  pGdLScintPropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
  Gd_LScint->SetMaterialPropertiesTable(pGdLScintPropertiesTable);

  // 0.2% Gd-doped
  G4Material *Gd_LScint_0_2 =
      new G4Material("Gd_LScint_0_2", 0.863 * g / cm3, 2, kStateLiquid);
  Gd_LScint_0_2->AddMaterial(LScint, 0.992011);
  Gd_LScint_0_2->AddMaterial(Gd_carboxylate, 0.007989);
  // Makes 0.2% of Gd in mass.
  Gd_LScint_0_2->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);

  // 0.4% Gd-doped
  G4Material *Gd_LScint_0_4 =
      new G4Material("Gd_LScint_0_4", 0.863 * g / cm3, 2, kStateLiquid);
  Gd_LScint_0_4->AddMaterial(LScint, 0.984023);
  Gd_LScint_0_4->AddMaterial(Gd_carboxylate, 0.015977);
  // Makes 0.4% of Gd in mass.
  Gd_LScint_0_4->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);

  // 0.8% Gd-doped
  G4Material *Gd_LScint_0_8 =
      new G4Material("Gd_LScint_0_8", 0.863 * g / cm3, 2, kStateLiquid);
  Gd_LScint_0_8->AddMaterial(LScint, 0.968046);
  Gd_LScint_0_8->AddMaterial(Gd_carboxylate, 0.031954);
  // Makes 0.8% of Gd in mass.
  Gd_LScint_0_8->GetIonisation()->SetBirksConstant(0.124 * mm / MeV);

  //==== Liquid Scintillator Borexino ====
  G4Material *PC = new G4Material("PC", 0.882 * g / cm3, 2, kStateLiquid);
  PC->AddElement(C, 9);
  PC->AddElement(H, 12);

  G4Material *B_LScint =
      new G4Material("B_LScint", 0.882 * g / cm3, 2, kStateLiquid);  // B-doped
  B_LScint->AddMaterial(LScint, 0.999);
  B_LScint->AddElement(B, 0.001);

  //==== Acrylic (nVeto Vessels) ====
  G4Material *Acrylic =
      new G4Material("Acrylic", 1.18 * g / cm3, 3, kStateSolid, 168.15 * kelvin,
                     1.5 * atmosphere);
  Acrylic->AddElement(C, 5);
  Acrylic->AddElement(H, 8);
  Acrylic->AddElement(O, 2);

  // DR 20160725 - Optical properties Acrylic
  // const G4int iNbEntries = 3;
  G4double pdAcrylicPhotonMomentum[iNbEntries] = {2.59 * eV, 2.88 * eV,
                                                  3.17 * eV};
  G4double pdAcrylicRefractiveIndex[iNbEntries] = {1.50, 1.50, 1.50};
  G4double pdAcrylicAbsorbtionLength[iNbEntries] = {3.5 * m, 3.5 * m, 3.5 * m};
  G4MaterialPropertiesTable *pAcrylicPropertiesTable =
      new G4MaterialPropertiesTable();
  pAcrylicPropertiesTable->AddProperty("RINDEX", pdAcrylicPhotonMomentum,
                                       pdAcrylicRefractiveIndex, iNbEntries);
  pAcrylicPropertiesTable->AddProperty("ABSLENGTH", pdAcrylicPhotonMomentum,
                                       pdAcrylicAbsorbtionLength, iNbEntries);
  // pAcrylicPropertiesTable->AddProperty("RAYLEIGH", pdAcrylicPhotonMomentum,
  // pdAcrylicScatteringLength, iNbEntries);
  Acrylic->SetMaterialPropertiesTable(pAcrylicPropertiesTable);

  //==== DF2000MA (MV reflector) ====
  pNistManager->FindOrBuildMaterial("G4_MYLAR");
  G4Material* DF2000MA = new G4Material("DF2000MA", 1.5*g/cm3, 2);
  DF2000MA->AddMaterial(G4Material::GetMaterial("G4_MYLAR"), 0.575);
  DF2000MA->AddMaterial(Acrylic, 0.425);
  //---- DF2000MA-Water Optical Surface ---
  // Reflectivity from https://arxiv.org/pdf/1706.03687.pdf
  const G4int NUM_ = 7;
  G4double pp_[NUM_] = {2.034 * eV, 3.179 * eV, 3.351 * eV, 3.701 * eV,
                        4.065 * eV, 4.509 * eV, 4.959 * eV};
  G4double reflectivity_W[NUM_] = {0.95, 0.95, 0.07, 0.05, 0.11, 0.06, 0.19};
  G4MaterialPropertiesTable *pMvFoilMPT = new G4MaterialPropertiesTable();
  pMvFoilMPT->AddProperty("REFLECTIVITY", pp_, reflectivity_W, NUM_);
  pMvFoilOpticalSurface = new G4OpticalSurface("MvFoilOpticalSurface");
  pMvFoilOpticalSurface->SetType(dielectric_dielectric);
  pMvFoilOpticalSurface->SetModel(unified);
  pMvFoilOpticalSurface->SetFinish(groundfrontpainted);
  pMvFoilOpticalSurface->SetMaterialPropertiesTable(pMvFoilMPT);

  //==== Liquid Xenon ====
  G4Material *LXe = new G4Material("LXe", 2.862 * g / cm3, 1, kStateLiquid,
                                   177.05 * kelvin, 1.5 * atmosphere);
  // DR 20180518 - Density according to:
  // -
  // https://xe1t-wiki.lngs.infn.it/doku.php?id=xenon:xenon1t:deg:tpc:targetmass
  // -
  // https://xe1t-wiki.lngs.infn.it/doku.php?id=xenon:xenon1t:analysis:sciencerun1:sc_summary
  LXe->AddElement(Xe, 1);

  // Optical properties LXe
  G4double pdLXePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double pdLXeScintillation[iNbEntries] = {0.1, 1.0, 0.1};
  G4double pdLXeRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
  // G4double pdLXeRefractiveIndex[iNbEntries]  = {1.56,    1.56,    1.56};
  // G4double pdLXeRefractiveIndex[iNbEntries]  = {1.69,    1.69,    1.69};
  G4double pdLXeAbsorbtionLength[iNbEntries] = {100. * cm, 100. * cm,
                                                100. * cm};
  G4double pdLXeScatteringLength[iNbEntries] = {30. * cm, 30. * cm, 30. * cm};
  G4MaterialPropertiesTable *pLXePropertiesTable =
      new G4MaterialPropertiesTable();
  pLXePropertiesTable->AddProperty("FASTCOMPONENT", pdLXePhotonMomentum,
                                   pdLXeScintillation, iNbEntries);
  pLXePropertiesTable->AddProperty("SLOWCOMPONENT", pdLXePhotonMomentum,
                                   pdLXeScintillation, iNbEntries);
  pLXePropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum,
                                   pdLXeRefractiveIndex, iNbEntries);
  pLXePropertiesTable->AddProperty("ABSLENGTH", pdLXePhotonMomentum,
                                   pdLXeAbsorbtionLength, iNbEntries);
  pLXePropertiesTable->AddProperty("RAYLEIGH", pdLXePhotonMomentum,
                                   pdLXeScatteringLength, iNbEntries);
  pLXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / keV);
  pLXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
  pLXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
  pLXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
  pLXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
  pLXePropertiesTable->AddConstProperty("TOTALNUM_INT_SITES", -1);
  // initialize the number of interaction sites
  LXe->SetMaterialPropertiesTable(pLXePropertiesTable);

  //==== Gaseous Xenon ====
  G4Material *GXe = new G4Material("GXe", 0.005887 * g / cm3, 1, kStateGas,
                                   173.15 * kelvin, 1.5 * atmosphere);
  GXe->AddElement(Xe, 1);

  // Optical properties GXe
  G4double pdGXePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double pdGXeScintillation[iNbEntries] = {0.1, 1.0, 0.1};
  G4double pdGXeRefractiveIndex[iNbEntries] = {1.00, 1.00, 1.00};
  G4double pdGXeAbsorbtionLength[iNbEntries] = {100 * m, 100 * m, 100 * m};
  G4double pdGXeScatteringLength[iNbEntries] = {100 * m, 100 * m, 100 * m};
  G4MaterialPropertiesTable *pGXePropertiesTable =
      new G4MaterialPropertiesTable();
  pGXePropertiesTable->AddProperty("FASTCOMPONENT", pdGXePhotonMomentum,
                                   pdGXeScintillation, iNbEntries);
  pGXePropertiesTable->AddProperty("SLOWCOMPONENT", pdGXePhotonMomentum,
                                   pdGXeScintillation, iNbEntries);
  pGXePropertiesTable->AddProperty("RINDEX", pdGXePhotonMomentum,
                                   pdGXeRefractiveIndex, iNbEntries);
  pGXePropertiesTable->AddProperty("ABSLENGTH", pdGXePhotonMomentum,
                                   pdGXeAbsorbtionLength, iNbEntries);
  pGXePropertiesTable->AddProperty("RAYLEIGH", pdGXePhotonMomentum,
                                   pdGXeScatteringLength, iNbEntries);
  pGXePropertiesTable->AddConstProperty("SCINTILLATIONYIELD", 0. / (keV));
  pGXePropertiesTable->AddConstProperty("RESOLUTIONSCALE", 0);
  pGXePropertiesTable->AddConstProperty("FASTTIMECONSTANT", 3. * ns);
  pGXePropertiesTable->AddConstProperty("SLOWTIMECONSTANT", 27. * ns);
  pGXePropertiesTable->AddConstProperty("YIELDRATIO", 1.0);
  GXe->SetMaterialPropertiesTable(pGXePropertiesTable);

  //==== Quartz ====
  // ref: http://www.sciner.com/Opticsland/FS.htm
  G4Material *Quartz = new G4Material("Quartz", 2.201 * g / cm3, 2, kStateSolid,
                                      168.15 * kelvin, 1.5 * atmosphere);
  Quartz->AddElement(Si, 1);
  Quartz->AddElement(O, 2);

  // Optical properties Quartz
  const G4int iNbEntriesMatch = 5;
  G4double pdQuartzPhotonMomentum[iNbEntriesMatch] = {
      1. * eV, 6.9 * eV, 6.91 * eV, 6.98 * eV,
      7.05 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
                   // "Out of Range - Attempt to retrieve information below
                   // range!"
  G4double pdQuartzRefractiveIndex[iNbEntriesMatch] = {1.50, 1.50, 1.50, 1.56,
                                                       1.60};
  G4double pdQuartzAbsorbtionLength[iNbEntriesMatch] = {30 * m, 30 * m, 30 * m,
                                                        30 * m, 30 * m};
  G4MaterialPropertiesTable *pQuartzPropertiesTable =
      new G4MaterialPropertiesTable();

  /*
  // Masatoshi Kobayashi for ID PMT photocathode:  For debug. Set same RINDEX with LXe to ignore reflection etc between PMT Window and LXe.
  pQuartzPropertiesTable->AddProperty("RINDEX", pdLXePhotonMomentum,
                                      pdLXeRefractiveIndex, iNbEntriesMatch);
  */


  pQuartzPropertiesTable->AddProperty("RINDEX", pdQuartzPhotonMomentum,
                                      pdQuartzRefractiveIndex, iNbEntriesMatch);
  pQuartzPropertiesTable->AddProperty("ABSLENGTH", pdQuartzPhotonMomentum,
                                      pdQuartzAbsorbtionLength,
                                      iNbEntriesMatch);
  Quartz->SetMaterialPropertiesTable(pQuartzPropertiesTable);

  //==== Glass for mu/nVeto PMTs ====
  G4Material *Glass = new G4Material("Glass", 2.201 * g / cm3, 2, kStateSolid,
                                      168.15 * kelvin, 1.5 * atmosphere);
  Glass->AddElement(Si, 1);
  Glass->AddElement(O, 2);

  // Optical properties Glass
  const G4int iNbEntriesGlass = 7;
  G4double pdGlassPhotonMomentum[iNbEntriesGlass] = {
    1.55*eV, 2.0664*eV, 2.48*eV, 2.755*eV, 3.1*eV, 4.133*eV, 6.2*eV
  };
  // Cauchy dispersion law n = 1.472 + 3760 / wavelength**2
  G4double pdGlassRefractiveIndex[iNbEntriesGlass] = {
    1.478, 1.482, 1.487, 1.491, 1.496, 1.51, 1.57
  };
  G4double pdGlassAbsorbtionLength[iNbEntriesGlass] = {
    300*mm, 300*mm, 300*mm, 300*mm, 300*mm, 300*mm, 300*mm
  };
  G4MaterialPropertiesTable *pGlassPropertiesTable =
      new G4MaterialPropertiesTable();
  pGlassPropertiesTable->AddProperty("RINDEX", pdGlassPhotonMomentum,
                                      pdGlassRefractiveIndex, iNbEntriesGlass);
  pGlassPropertiesTable->AddProperty("ABSLENGTH", pdGlassPhotonMomentum,
                                      pdGlassAbsorbtionLength,
                                      iNbEntriesGlass);
  Glass->SetMaterialPropertiesTable(pGlassPropertiesTable);

  //==== mu/nVeto PMT Alluminum evaporation part ====
  // Reflectivity assumed 90%
  // See https://xe1t-wiki.lngs.infn.it/doku.php?id=xenon:xenonnt:analysis:mc-subgroup:neutron_veto_sim:pmt_geometry_update#pmt_alminium_evaporation_part_reflectivity
  const G4int NUM_AlEv = 2;
  G4double pp_AlEv[NUM_AlEv] = {1.*eV, 5.*eV};
  G4double reflectivity_AlEv[NUM_AlEv] = {0.90, 0.90};
  G4MaterialPropertiesTable* pPMTAlEvMPT = new G4MaterialPropertiesTable();
  pPMTAlEvMPT->AddProperty("REFLECTIVITY",pp_AlEv,reflectivity_AlEv,NUM_AlEv);

  pPMTAlEvaporationOpticalSurface = new G4OpticalSurface("PMTAlEvaporationOpticalSurface");  
  pPMTAlEvaporationOpticalSurface->SetType(dielectric_dielectric);
  pPMTAlEvaporationOpticalSurface->SetModel(unified);
  pPMTAlEvaporationOpticalSurface->SetFinish(polishedfrontpainted);
  pPMTAlEvaporationOpticalSurface->SetMaterialPropertiesTable(pPMTAlEvMPT);

  //==== Kovar ====
  // RINO  6 June 2012
  G4Material *Kovar = new G4Material("Kovar", 8.33 * g / cm3, 6, kStateSolid);
  Kovar->AddElement(Fe, 0.5358);
  Kovar->AddElement(Ni, 0.29);
  Kovar->AddElement(Co, 0.17);
  Kovar->AddElement(C, 0.0002);
  Kovar->AddElement(Si, 0.001);
  Kovar->AddElement(Mn, 0.003);

  // G4MaterialPropertiesTable *pKovarPropertiesTable = new
  // G4MaterialPropertiesTable();
  // G4double pdKovarPhotonMomentum[iNbEntries] = {6.91*eV, 6.98*eV, 7.05*eV};
  // G4double pdKovarReflectivity[iNbEntries] = {0.15, 0.2, 0.15}; // check
  // pKovarPropertiesTable->AddProperty("REFLECTIVITY", pdKovarPhotonMomentum,
  // pdKovarReflectivity, iNbEntries);
  // Kovar->SetMaterialPropertiesTable(pKovarPropertiesTable);

  //==== Cirlex ====
  // RINO  6 June 2012 - Imported from Xe100 code
  G4Material *Cirlex = new G4Material("Cirlex", 1.43 * g / cm3, 4, kStateSolid);
  Cirlex->AddElement(C, 22);
  Cirlex->AddElement(H, 10);
  Cirlex->AddElement(N, 2);
  Cirlex->AddElement(O, 5);

  // G4double pdCirlexPhotonMomentum[]  = {6.91*eV, 6.98*eV, 7.05*eV};
  // G4double pdCirlexReflectivity[]   = {0.5,    0.5,     0.5};
  // G4MaterialPropertiesTable *pCirlexPropertiesTable = new
  // G4MaterialPropertiesTable();
  // pCirlexPropertiesTable->AddProperty("REFLECTIVITY",
  // pdCirlexPhotonMomentum, pdCirlexReflectivity, iNbEntries);
  // Cirlex->SetMaterialPropertiesTable(pCirlexPropertiesTable);

  //==== Stainless Steel ====
  G4Material *SS304LSteel =
      new G4Material("SS304LSteel", 8.00 * g / cm3, 5, kStateSolid);
  SS304LSteel->AddElement(Fe, 0.65);
  SS304LSteel->AddElement(Cr, 0.20);
  SS304LSteel->AddElement(Ni, 0.12);
  SS304LSteel->AddElement(Mn, 0.02);
  SS304LSteel->AddElement(Si, 0.01);

  //---- SS-Water Optical Surface ---
  G4MaterialPropertiesTable *pSSPropertiesTable =
    new G4MaterialPropertiesTable();
  const G4int n_SS = 2;
  G4double dEnergy_SS[n_SS] = {1.*eV, 5.*eV};
  G4double dReflectivity_SS[n_SS] = {0.5, 0.5}; // tentative!
  pSSPropertiesTable->
    AddProperty("REFLECTIVITY", dEnergy_SS, dReflectivity_SS, n_SS);
  // optical surface
  pSSOpticalSurface = new G4OpticalSurface("SSOpticalSurface");
  pSSOpticalSurface->SetType(dielectric_dielectric);
  pSSOpticalSurface->SetModel(unified);
  pSSOpticalSurface->SetFinish(groundfrontpainted);
  pSSOpticalSurface->
    SetMaterialPropertiesTable(pSSPropertiesTable);

  // G4double pdSteelPhotonMomentum[] = {6.91*eV, 6.98*eV, 7.05*eV};
  // G4double pdSteelReflectivity[]   = {0.15,    0.2,     0.15};
  // G4MaterialPropertiesTable *pSteelPropertiesTable = new
  // G4MaterialPropertiesTable();
  // pSteelPropertiesTable->AddProperty("REFLECTIVITY", pdSteelPhotonMomentum,
  // pdSteelReflectivity, iNbEntries);
  // SS304LSteel->SetMaterialPropertiesTable(pSteelPropertiesTable);

  // A.P. Colijn 26-07-2011
  // AISI 316Ti steel / UNS S 31635
  //
  // 1. Take the maximum specified fraction of each component.
  //    See http://www.atimetals.com/ludlum/Documents/316ti.pdf
  // 2. Leave out tracer elements <0.05% of Phosphor and Sulphur (justifiable?)
  //
  G4Material *SS316Ti =
      new G4Material("SS316Ti", 8.00 * g / cm3, 8, kStateSolid);
  SS316Ti->AddElement(Cr, 0.18);
  SS316Ti->AddElement(Ni, 0.14);
  SS316Ti->AddElement(Mo, 0.03);
  SS316Ti->AddElement(Mn, 0.02);
  SS316Ti->AddElement(C, 0.008);
  SS316Ti->AddElement(Si, 0.0075);
  SS316Ti->AddElement(Ti, 0.0070);
  SS316Ti->AddElement(Fe, 0.6075);

  //==== Polyethylene ====
  G4Material *Polyethylene =
      new G4Material("Polyethylene", .925 * g / cm3, 2, kStateSolid);
  Polyethylene->AddElement(H, 4);
  Polyethylene->AddElement(C, 2);

  //==== Delrin ====
  G4Material *Delrin =
      new G4Material("Delrin", 1.415 * g / cm3, 3, kStateSolid);
  Delrin->AddElement(C, 1);
  Delrin->AddElement(H, 2);
  Delrin->AddElement(O, 1);

  //==== Belt Polyurethane ====
  // Mike Clark 210329
  G4Material *Polyurethane =
      new G4Material("Polyurethane", 1.005 * g / cm3, 4, kStateSolid);
  Polyurethane->AddElement(C, 3);
  Polyurethane->AddElement(H, 8);
  Polyurethane->AddElement(N, 2);
  Polyurethane->AddElement(O, 1);

  //==== I-belt Material ====
  //Approximation of Polyurethane and Steel
  // Mike Clark 210329
  G4Material *IBeltMaterial =
      new G4Material("IBeltMaterial", 4.5 * g / cm3, 2, kStateSolid);
  IBeltMaterial->AddMaterial(Polyurethane,0.5);
  IBeltMaterial->AddMaterial(SS316Ti,0.5);

  //==== 1.4571 NiCrSteel ====
  // List of fractions by mass obtained from datasheets
  G4Material *NiCrSteel =
      new G4Material("NiCrSteel", 8. * g / cm3, 10, kStateSolid);
  NiCrSteel->AddElement(Fe, 0.5811);
  NiCrSteel->AddElement(C, 0.0008);
  NiCrSteel->AddElement(Si, 0.01);
  NiCrSteel->AddElement(Mn, 0.02);
  NiCrSteel->AddElement(P, 0.00045);
  NiCrSteel->AddElement(S, 0.00015);
  NiCrSteel->AddElement(Cr, 0.175);
  NiCrSteel->AddElement(Mo, 0.0225);
  NiCrSteel->AddElement(Ni, 0.12);
  NiCrSteel->AddElement(Ti, 0.070);

  //==== Titanium Alloys ====
  // 1. Titanium grade1: UNS R50250; ASTM Grade 1
  //    See http://asm.matweb.com/search/SpecificMaterial.asp?bassnum=MTU010
  // 2. Maximum specified fraction for each component
  //
  // A.P. Colijn 26-07-2011
  //
  G4Material *TiGrade1 =
      new G4Material("TiGrade1", 4.51 * g / cm3, 6, kStateSolid);
  TiGrade1->AddElement(C, 0.0010);
  TiGrade1->AddElement(Fe, 0.0020);
  TiGrade1->AddElement(H, 0.00015);
  TiGrade1->AddElement(N, 0.0003);
  TiGrade1->AddElement(O, 0.0018);
  TiGrade1->AddElement(Ti, 0.99475);

  // As far as Geant4 is concerned grade1 and grade2 identical I would
  // think.....

  // 1. Titanium grade2: UNS R50400; ASTM Grade 2
  //    See http://asm.matweb.com/search/SpecificMaterial.asp?bassnum=MTU020
  // 2. Maximum specified fraction for each component
  //
  // A.P. Colijn 26-07-2011
  //
  G4Material *TiGrade2 =
      new G4Material("TiGrade2", 4.51 * g / cm3, 6, kStateSolid);
  TiGrade2->AddElement(C, 0.001);
  TiGrade2->AddElement(Fe, 0.003);
  TiGrade2->AddElement(H, 0.00015);
  TiGrade2->AddElement(N, 0.0003);
  TiGrade2->AddElement(O, 0.0025);
  TiGrade2->AddElement(Ti, 0.99305);

  //==== Torlon ====
  G4Material *Torlon = new G4Material("Torlon", 1.41 * g / cm3, 4, kStateSolid);
  Torlon->AddElement(N, 0.07862);
  Torlon->AddElement(C, 0.70784);
  Torlon->AddElement(O, 0.17960);
  Torlon->AddElement(H, 0.03394);

  //==== Photocathode Aluminium ====
  G4Material *PhotoCathodeAluminium =
      new G4Material("PhotoCathodeAluminium", 8.00 * g / cm3, 1, kStateSolid);
  PhotoCathodeAluminium->AddElement(Al, 1);

  G4double pdPhotoCathodePhotonMomentum[] = {
      1. * eV, 6.9 * eV, 6.91 * eV, 6.98 * eV,
      7.05 * eV};  // SERENA: changed  2.*eV to 1.*eV otherwise it gets stuck
                   // "Out of Range - Attempt to retrieve information below
                   // range!"
  G4double pdPhotoCathodeRefractiveIndex[] = {1.50, 1.50, 1.50, 1.56, 1.60};
  G4double pdPhotoCathodeAbsorbtionLength[] = {1. * nm, 1 * nm, 1. * nm,
                                               1. * nm, 1. * nm};
  G4MaterialPropertiesTable *pPhotoCathodePropertiesTable =
      new G4MaterialPropertiesTable();

  // Masatoshi Kobayashi for ID PMT photocathode:  For debug. Set same RINDEX with LXe to ignore reflection etc between Quatz, photocathode and LXe..
  /*
  pPhotoCathodePropertiesTable->AddProperty(
      "RINDEX", pdLXePhotonMomentum, pdLXeRefractiveIndex,
      iNbEntriesMatch);
  */
  pPhotoCathodePropertiesTable->AddProperty(
      "RINDEX", pdPhotoCathodePhotonMomentum, pdPhotoCathodeRefractiveIndex,
      iNbEntriesMatch);
  pPhotoCathodePropertiesTable->AddProperty(
      "ABSLENGTH", pdPhotoCathodePhotonMomentum, pdPhotoCathodeAbsorbtionLength,
      iNbEntriesMatch);
  PhotoCathodeAluminium->SetMaterialPropertiesTable(
      pPhotoCathodePropertiesTable);

  //==== Photocathode Aluminium (For the case of photocathode reflection)====
  G4Material *PhotoCathodeAluminiumID =
      new G4Material("PhotoCathodeAluminiumID", 8.00 * g / cm3, 1, kStateSolid);
  PhotoCathodeAluminiumID->AddElement(Al, 1);

  //==== Veto PMT Photocathode ====
  G4Material *VetoPMTPhotocathode =
      new G4Material("VetoPMTPhotocathode", 5*g/cm3, 1, kStateSolid);
  VetoPMTPhotocathode->AddElement(K, 1);

  constexpr G4int iNumVetoPMTPhotocathode = 2;
  G4double pdVetoPMTPhotocathodePhotonMomentum[iNumVetoPMTPhotocathode] =
    {1*eV, 5*eV};
  G4double pdVetoPMTPhotocathodeRefractiveIndex[iNumVetoPMTPhotocathode] =
    {2.9, 2.9};
  G4double pdVetoPMTPhotocathodeAbsorptionLength[iNumVetoPMTPhotocathode] =
    {1e-3*nm, 1e-3*nm};

  G4MaterialPropertiesTable* pVetoPMTPhotocathodePropertiesTable =
      new G4MaterialPropertiesTable();
  pVetoPMTPhotocathodePropertiesTable->AddProperty(
      "RINDEX", pdVetoPMTPhotocathodePhotonMomentum,
      pdVetoPMTPhotocathodeRefractiveIndex, iNumVetoPMTPhotocathode);
  pVetoPMTPhotocathodePropertiesTable->AddProperty(
      "ABSLENGTH", pdVetoPMTPhotocathodePhotonMomentum,
      pdVetoPMTPhotocathodeAbsorptionLength, iNumVetoPMTPhotocathode);
  VetoPMTPhotocathode->SetMaterialPropertiesTable(
          pVetoPMTPhotocathodePropertiesTable);

  //==== Grid Mesh Aluminium ====
  G4Material *GridMeshAluminium =
      new G4Material("GridMeshAluminium", 0.174 * g / cm3, 1, kStateSolid);
  GridMeshAluminium->AddElement(Al, 1);

  G4double pdGridMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double *pdGridMeshRefractiveIndex = pdLXeRefractiveIndex;
  // G4double dAbsortionLength = 2.10*mm; // exp(-GridMeshThickness/2.10) = 0.94
  // : works with thickness 0f 0.13 mm
  G4double dAbsortionLength =
      3.2323021424 * mm;  // exp(-GridMeshThickness/dAbsortionLength) = 0.94,
                          // with thickness of 0.2mm
  // G4double dAbsortionLength = 6.5661590*mm; //
  // exp(-GridMeshThickness/dAbsortionLength) = 0.97, with thickness of 0.2mm
  G4double pdGridMeshAbsortionLength[] = {dAbsortionLength, dAbsortionLength,
                                          dAbsortionLength};
  G4MaterialPropertiesTable *pGridMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pGridMeshPropertiesTable->AddProperty("RINDEX", pdGridMeshPhotonMomentum,
                                        pdGridMeshRefractiveIndex, iNbEntries);
  pGridMeshPropertiesTable->AddProperty("ABSLENGTH", pdGridMeshPhotonMomentum,
                                        pdGridMeshAbsortionLength, iNbEntries);
  GridMeshAluminium->SetMaterialPropertiesTable(pGridMeshPropertiesTable);

  //
  // Treating every grid with different transparency. Cyril, June 2014
  //

  //==== Top Screening Mesh ====
  G4Material *TopScreeningMesh =
      new G4Material("TopScreeningMesh", 0.48 * g / cm3, 1, kStateSolid);
  TopScreeningMesh->AddMaterial(SS316Ti,
                                1);  // density is (100.-94.)/100. * 8.g/cm3
  G4double pdTopScreeningMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV,
                                                 7.05 * eV};
  G4double *pdTopScreeningMeshRefractiveIndex = pdGXeRefractiveIndex;
  G4double dTopScreeningMeshAbsortionLength = 3.2323021424 * mm;
  // exp(-TopScreeningMeshThickness/dAbsortionLength) =
  // 0.94, with thickness of 0.2mm
  G4double pdTopScreeningMeshAbsortionLength[] = {
      dTopScreeningMeshAbsortionLength, dTopScreeningMeshAbsortionLength,
      dTopScreeningMeshAbsortionLength};
  G4MaterialPropertiesTable *pTopScreeningMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pTopScreeningMeshPropertiesTable->AddProperty(
      "RINDEX", pdTopScreeningMeshPhotonMomentum,
      pdTopScreeningMeshRefractiveIndex, iNbEntries);
  pTopScreeningMeshPropertiesTable->AddProperty(
      "ABSLENGTH", pdTopScreeningMeshPhotonMomentum,
      pdTopScreeningMeshAbsortionLength, iNbEntries);
  TopScreeningMesh->SetMaterialPropertiesTable(
      pTopScreeningMeshPropertiesTable);

  //==== Bottom Screening Mesh ====
  G4Material *BottomScreeningMesh =
      new G4Material("BottomScreeningMesh", 0.48 * g / cm3, 1, kStateSolid);
  BottomScreeningMesh->AddMaterial(SS316Ti, 1);
  G4double pdBottomScreeningMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV,
                                                    7.05 * eV};
  G4double *pdBottomScreeningMeshRefractiveIndex = pdLXeRefractiveIndex;
  G4double dBottomScreeningMeshAbsortionLength =
      3.2323021424 * mm;  // exp(-BottomScreeningMeshThickness/dAbsortionLength)
                          // = 0.94, with thickness of 0.2mm
  G4double pdBottomScreeningMeshAbsortionLength[] = {
      dBottomScreeningMeshAbsortionLength, dBottomScreeningMeshAbsortionLength,
      dBottomScreeningMeshAbsortionLength};
  G4MaterialPropertiesTable *pBottomScreeningMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pBottomScreeningMeshPropertiesTable->AddProperty(
      "RINDEX", pdBottomScreeningMeshPhotonMomentum,
      pdBottomScreeningMeshRefractiveIndex, iNbEntries);
  pBottomScreeningMeshPropertiesTable->AddProperty(
      "ABSLENGTH", pdBottomScreeningMeshPhotonMomentum,
      pdBottomScreeningMeshAbsortionLength, iNbEntries);
  BottomScreeningMesh->SetMaterialPropertiesTable(
      pBottomScreeningMeshPropertiesTable);

  //==== Cathode Mesh ====
  G4Material *CathodeMesh =
      new G4Material("CathodeMesh", 0.48 * g / cm3, 1, kStateSolid);
  CathodeMesh->AddMaterial(SS316Ti, 1);
  G4double pdCathodeMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double *pdCathodeMeshRefractiveIndex = pdLXeRefractiveIndex;
  G4double dCathodeMeshAbsortionLength =
      3.2323021424 * mm;  // exp(-CathodeMeshThickness/dAbsortionLength) = 0.94,
                          // with thickness of 0.2mm
  G4double pdCathodeMeshAbsortionLength[] = {dCathodeMeshAbsortionLength,
                                             dCathodeMeshAbsortionLength,
                                             dCathodeMeshAbsortionLength};
  G4MaterialPropertiesTable *pCathodeMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pCathodeMeshPropertiesTable->AddProperty(
      "RINDEX", pdCathodeMeshPhotonMomentum, pdCathodeMeshRefractiveIndex,
      iNbEntries);
  pCathodeMeshPropertiesTable->AddProperty(
      "ABSLENGTH", pdCathodeMeshPhotonMomentum, pdCathodeMeshAbsortionLength,
      iNbEntries);
  CathodeMesh->SetMaterialPropertiesTable(pCathodeMeshPropertiesTable);

  //==== Anode Mesh ====
  G4Material *AnodeMesh =
      new G4Material("AnodeMesh", 0.48 * g / cm3, 1, kStateSolid);
  AnodeMesh->AddMaterial(SS316Ti, 1);
  G4double pdAnodeMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double *pdAnodeMeshRefractiveIndex = pdGXeRefractiveIndex;
  G4double dAnodeMeshAbsortionLength =
      3.2323021424 * mm;  // exp(-AnodeMeshThickness/dAbsortionLength) = 0.94,
                          // with thickness of 0.2mm
  G4double pdAnodeMeshAbsortionLength[] = {dAnodeMeshAbsortionLength,
                                           dAnodeMeshAbsortionLength,
                                           dAnodeMeshAbsortionLength};
  G4MaterialPropertiesTable *pAnodeMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pAnodeMeshPropertiesTable->AddProperty("RINDEX", pdAnodeMeshPhotonMomentum,
                                         pdAnodeMeshRefractiveIndex,
                                         iNbEntries);
  pAnodeMeshPropertiesTable->AddProperty("ABSLENGTH", pdAnodeMeshPhotonMomentum,
                                         pdAnodeMeshAbsortionLength,
                                         iNbEntries);
  AnodeMesh->SetMaterialPropertiesTable(pAnodeMeshPropertiesTable);

  //==== Gate Mesh ====
  G4Material *GateMesh =
      new G4Material("GateMesh", 0.48 * g / cm3, 1, kStateSolid);
  GateMesh->AddMaterial(SS316Ti, 1);
  G4double pdGateMeshPhotonMomentum[] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double *pdGateMeshRefractiveIndex = pdLXeRefractiveIndex;
  G4double dGateMeshAbsortionLength =
      3.2323021424 * mm;  // exp(-GateMeshThickness/dAbsortionLength) = 0.94,
                          // with thickness of 0.2mm
  G4double pdGateMeshAbsortionLength[] = {dGateMeshAbsortionLength,
                                          dGateMeshAbsortionLength,
                                          dGateMeshAbsortionLength};
  G4MaterialPropertiesTable *pGateMeshPropertiesTable =
      new G4MaterialPropertiesTable();
  pGateMeshPropertiesTable->AddProperty("RINDEX", pdGateMeshPhotonMomentum,
                                        pdGateMeshRefractiveIndex, iNbEntries);
  pGateMeshPropertiesTable->AddProperty("ABSLENGTH", pdGateMeshPhotonMomentum,
                                        pdGateMeshAbsortionLength, iNbEntries);
  GateMesh->SetMaterialPropertiesTable(pGateMeshPropertiesTable);

  
  //==== ePTFE ==== Expanded PTFE (as Teflon, but lower density, used in the nVeto reflector)
  G4Material *ePTFE = new G4Material("ePTFE", 0.7 * g / cm3, 2, kStateSolid);
  ePTFE->AddElement(C, 0.240183);
  ePTFE->AddElement(F, 0.759817);

  //---- ePTFE-Water Optical Surface ---
  G4MaterialPropertiesTable *pEPTFEWaterPropertiesTable =
      new G4MaterialPropertiesTable();
  // reflectivity 
  // it can be set in the preinit macro
  // (default: 0.99)
  const G4int n_ePTFE = 2;
  G4double dEnergy_ePTFE[n_ePTFE] = {1.*eV, 5.*eV};
  G4double dReflectivity_ePTFE[n_ePTFE] = {pEPTFEReflectivity, pEPTFEReflectivity};
  pEPTFEWaterPropertiesTable->
    AddProperty("REFLECTIVITY", dEnergy_ePTFE, dReflectivity_ePTFE, n_ePTFE);
  // optical surface
  pEPTFEWaterOpticalSurface = new G4OpticalSurface("ePTFEWaterOpticalSurface");
  pEPTFEWaterOpticalSurface->SetType(dielectric_dielectric);
  pEPTFEWaterOpticalSurface->SetModel(unified);
  pEPTFEWaterOpticalSurface->SetFinish(groundfrontpainted);
  pEPTFEWaterOpticalSurface->
    SetMaterialPropertiesTable(pEPTFEWaterPropertiesTable);
  G4cout << "Xenon1tMaterials : ePTFE reflectivity = " << pEPTFEReflectivity << G4endl;

  //==== Teflon ====
  G4Material *Teflon = new G4Material("Teflon", 2.2 * g / cm3, 2, kStateSolid);
  Teflon->AddElement(C, 0.240183);
  Teflon->AddElement(F, 0.759817);

  G4double pdTeflonPhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
                                                 7.05 * eV};
  G4double pdTeflonRefractiveIndex[iNbEntries] = {1.63, 1.61, 1.58};
  G4double pdTeflonReflectivity[iNbEntries] = {0.99, 0.99, 0.99};
  G4double pdTeflonSpecularLobe[iNbEntries] = {0.01, 0.01, 0.01};
  G4double pdTeflonSpecularSpike[iNbEntries] = {0.01, 0.01, 0.01};
  G4double pdTeflonBackscatter[iNbEntries] = {0.01, 0.01, 0.01};
  G4double pdTeflonEfficiency[iNbEntries] = {1.0, 1.0, 1.0};
  G4double pdTeflonAbsorbtionLength[iNbEntries] = {0.1 * cm, 0.1 * cm,
                                                   0.1 * cm};
  G4MaterialPropertiesTable *pTeflonPropertiesTable =
      new G4MaterialPropertiesTable();
  pTeflonPropertiesTable->AddProperty("RINDEX", pdTeflonPhotonMomentum,
                                      pdTeflonRefractiveIndex, iNbEntries);
  pTeflonPropertiesTable->AddProperty("REFLECTIVITY", pdTeflonPhotonMomentum,
                                      pdTeflonReflectivity, iNbEntries);
  pTeflonPropertiesTable->AddProperty("ABSLENGTH", pdTeflonPhotonMomentum,
                                      pdTeflonAbsorbtionLength, iNbEntries);
  pTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT",
                                      pdTeflonPhotonMomentum,
                                      pdTeflonSpecularLobe, iNbEntries);
  pTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT",
                                      pdTeflonPhotonMomentum,
                                      pdTeflonSpecularSpike, iNbEntries);
  pTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT",
                                      pdTeflonPhotonMomentum,
                                      pdTeflonBackscatter, iNbEntries);
  pTeflonPropertiesTable->AddProperty("EFFICIENCY", pdTeflonPhotonMomentum,
                                      pdTeflonEfficiency, iNbEntries);
  
  //==== Default optics if no OpticalSurface is given
  Teflon->SetMaterialPropertiesTable(pTeflonPropertiesTable);
  G4double pdTeflonSufraceTransmittance[iNbEntries] = {1e-12,1e-12,1e-12}; // 1e-12 because Geant4 is stupid
  //==== LXe Teflon ====
  pLXeTeflonOpticalSurface = new G4OpticalSurface("LXeTeflonOpticalSurface", 
       unified, ground, dielectric_dielectric, 0.1);

  G4MaterialPropertiesTable *pLXeTeflonPropertiesTable =
      new G4MaterialPropertiesTable();
  pLXeTeflonPropertiesTable->AddProperty("RINDEX", 
      pTeflonPropertiesTable->GetProperty("RINDEX"));
  pLXeTeflonPropertiesTable->AddProperty("REFLECTIVITY",
      pTeflonPropertiesTable->GetProperty("REFLECTIVITY"));
  pLXeTeflonPropertiesTable->AddProperty("ABSLENGTH", 
      pTeflonPropertiesTable->GetProperty("ABSLENGTH"));
  pLXeTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARLOBECONSTANT"));
  pLXeTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARSPIKECONSTANT"));
  pLXeTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", 
      pTeflonPropertiesTable->GetProperty("BACKSCATTERCONSTANT"));
  pLXeTeflonPropertiesTable->AddProperty("EFFICIENCY", 
      pTeflonPropertiesTable->GetProperty("EFFICIENCY"));
  pLXeTeflonPropertiesTable->AddProperty("TRANSMITTANCE", pdTeflonPhotonMomentum, 
                                        pdTeflonSufraceTransmittance, iNbEntries);  
  pLXeTeflonOpticalSurface->SetMaterialPropertiesTable(
      pLXeTeflonPropertiesTable);
      
  //==== LXe Teflon unpolished ====
  pLXeTeflonUnpolishedOpticalSurface = new G4OpticalSurface("LXeTeflonUnpolishedOpticalSurface", 
       unified, ground, dielectric_dielectric, 0.1);

  G4MaterialPropertiesTable *pLXeTeflonUnpolishedPropertiesTable =
      new G4MaterialPropertiesTable();
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("RINDEX", 
      pTeflonPropertiesTable->GetProperty("RINDEX"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("REFLECTIVITY",
      pTeflonPropertiesTable->GetProperty("REFLECTIVITY"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("ABSLENGTH", 
      pTeflonPropertiesTable->GetProperty("ABSLENGTH"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("SPECULARLOBECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARLOBECONSTANT"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARSPIKECONSTANT"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("BACKSCATTERCONSTANT", 
      pTeflonPropertiesTable->GetProperty("BACKSCATTERCONSTANT"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("EFFICIENCY", 
      pTeflonPropertiesTable->GetProperty("EFFICIENCY"));
  pLXeTeflonUnpolishedPropertiesTable->AddProperty("TRANSMITTANCE", pdTeflonPhotonMomentum, 
                                        pdTeflonSufraceTransmittance, iNbEntries);         
  pLXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(     
      pLXeTeflonUnpolishedPropertiesTable);
  
  //==== GXe Teflon ====
  pGXeTeflonOpticalSurface = new G4OpticalSurface("GXeTeflonOpticalSurface", 
       unified, ground, dielectric_dielectric, 0.1);

  G4MaterialPropertiesTable *pGXeTeflonPropertiesTable =
      new G4MaterialPropertiesTable();
  pGXeTeflonPropertiesTable->AddProperty("RINDEX", 
      pTeflonPropertiesTable->GetProperty("RINDEX"));
  pGXeTeflonPropertiesTable->AddProperty("REFLECTIVITY",
      pTeflonPropertiesTable->GetProperty("REFLECTIVITY"));
  pGXeTeflonPropertiesTable->AddProperty("ABSLENGTH", 
      pTeflonPropertiesTable->GetProperty("ABSLENGTH"));
  pGXeTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARLOBECONSTANT"));
  pGXeTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARSPIKECONSTANT"));
  pGXeTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", 
      pTeflonPropertiesTable->GetProperty("BACKSCATTERCONSTANT"));
  pGXeTeflonPropertiesTable->AddProperty("EFFICIENCY", 
      pTeflonPropertiesTable->GetProperty("EFFICIENCY"));
  pGXeTeflonPropertiesTable->AddProperty("TRANSMITTANCE", pdTeflonPhotonMomentum, 
                                        pdTeflonSufraceTransmittance, iNbEntries);         
  pGXeTeflonOpticalSurface->SetMaterialPropertiesTable(
      pGXeTeflonPropertiesTable);
  
  //==== GXe Teflon unpolished ====
  pGXeTeflonUnpolishedOpticalSurface = new G4OpticalSurface("GXeTeflonUnpolishedOpticalSurface", 
       unified, ground, dielectric_dielectric, 0.1);

  G4MaterialPropertiesTable *pGXeUnpolishedTeflonPropertiesTable =
      new G4MaterialPropertiesTable();
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("RINDEX", 
      pTeflonPropertiesTable->GetProperty("RINDEX"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("REFLECTIVITY",
      pTeflonPropertiesTable->GetProperty("REFLECTIVITY"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("ABSLENGTH", 
      pTeflonPropertiesTable->GetProperty("ABSLENGTH"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("SPECULARLOBECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARLOBECONSTANT"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("SPECULARSPIKECONSTANT", 
      pTeflonPropertiesTable->GetProperty("SPECULARSPIKECONSTANT"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("BACKSCATTERCONSTANT", 
      pTeflonPropertiesTable->GetProperty("BACKSCATTERCONSTANT"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("EFFICIENCY", 
      pTeflonPropertiesTable->GetProperty("EFFICIENCY"));
  pGXeUnpolishedTeflonPropertiesTable->AddProperty("TRANSMITTANCE", pdTeflonPhotonMomentum, 
                                        pdTeflonSufraceTransmittance, iNbEntries);         
  pGXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(
      pGXeUnpolishedTeflonPropertiesTable);

  //---------------Optical surface between quartz and PC----------------
  //2020 Apr., Masatoshi, based on XMASS MC
  thePCEff=0.34;
  pWindowPCOpticalSurface = new G4OpticalSurface
     ("PMTWindowPCOpticalSurface", unified, polished, dielectric_LUT);
	//("PMTWindowPCOpticalSurface", unified, polished, dielectric_PC);
  G4double pmctsurf_USEPCMODEL[PNUM] = {1., 1.};
  G4double pmctsurf_EFF[PNUM] = { thePCEff, thePCEff };
  pmctsurf_mt = new G4MaterialPropertiesTable();
  pmctsurf_mt->AddProperty("USEPCMODEL", pmctsurf_PP, pmctsurf_USEPCMODEL, PNUM);
  pmctsurf_mt->AddProperty("EFFICIENCY", pmctsurf_PP, pmctsurf_EFF, PNUM);
  pWindowPCOpticalSurface ->SetMaterialPropertiesTable(pmctsurf_mt);

 
  // Steel wires in LXe
  G4double pdGXeWirePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
                                                 7.05 * eV};
  G4double pdGXeWireReflectivity[iNbEntries] = {0.20, 0.20, 0.20};
  G4MaterialPropertiesTable *pGXeWirePropertiesTable = 
            new G4MaterialPropertiesTable();
  pGXeWirePropertiesTable->AddProperty("REFLECTIVITY",
            pdGXeWirePhotonMomentum, pdGXeWireReflectivity, iNbEntries);
  
  pGXeWireSurface = new G4OpticalSurface("GXeWireSurface", 
       unified, polished, dielectric_metal, 0.1);
  pGXeWireSurface->SetMaterialPropertiesTable(pGXeWirePropertiesTable);
  // Steel wires in LXe
  G4double pdLXeWirePhotonMomentum[iNbEntries] = {6.91 * eV, 6.98 * eV,
                                                 7.05 * eV};
  G4double pdLXeWireReflectivity[iNbEntries] = {0.05, 0.05, 0.05};
  G4MaterialPropertiesTable *pLXeWirePropertiesTable = 
            new G4MaterialPropertiesTable();
  pLXeWirePropertiesTable->AddProperty("REFLECTIVITY",
        pdLXeWirePhotonMomentum, pdLXeWireReflectivity, iNbEntries);
  
  pLXeWireSurface = new G4OpticalSurface("LXeWireSurface", 
       unified, polished, dielectric_metal, 0.1);   
  pLXeWireSurface->SetMaterialPropertiesTable(pLXeWirePropertiesTable);
  //==== Copper ====
  G4Material *Copper = new G4Material("Copper", 8.92 * g / cm3, 1);
  Copper->AddElement(Cu, 1);

  G4double pdCopperPhotonMomentum[iNbEntries] = {
      1.91 * eV, 6.98 * eV, 7.05 * eV};  //{6.91*eV, 6.98*eV, 7.05*eV};
  G4double pdCopperReflectivity[iNbEntries] = {0.15, 0.2, 0.15};
  G4MaterialPropertiesTable *pCopperPropertiesTable =
      new G4MaterialPropertiesTable();
  pCopperPropertiesTable->AddProperty("REFLECTIVITY", pdCopperPhotonMomentum,
                                      pdCopperReflectivity, iNbEntries);
  Copper->SetMaterialPropertiesTable(pCopperPropertiesTable);

  //==== PMT Ceramic ====
  G4Material *Ceramic = new G4Material("Ceramic", 4. * g / cm3, 2, kStateSolid,
                                       168.15 * kelvin, 1.5 * atmosphere);
  Ceramic->AddElement(Al, 2);
  Ceramic->AddElement(O, 3);

  //==== Ethylene Glycol ====
  G4Material *Glycol =
      new G4Material("Glycol", 1.11 * g / cm3, 3, kStateLiquid);
  Glycol->AddElement(C, 2);
  Glycol->AddElement(O, 2);
  Glycol->AddElement(H, 6);

  //==== Water Glycol Mixture ====
  G4Material *WaterGlycol =
      new G4Material("WaterGlycol", 1.04 * g / cm3, 2, kStateLiquid);
  WaterGlycol->AddMaterial(Water, 0.61855);
  WaterGlycol->AddMaterial(Glycol, 0.38145);

  //==== Deuterium Gas ====
  G4Material *DeuteriumGas =
      new G4Material("DeuteriumGas", 0.08 * g / m3, 2, kStateGas,
                     308.15 * kelvin, 0.0297 * bar);
  DeuteriumGas->AddElement(D, 1);
  DeuteriumGas->AddElement(D, 1);

  //==== Transformer Oil ====
  G4Material *TransformerOil =
      new G4Material("TransformerOil", 0.89 * g / cm3, 2, kStateLiquid);
  TransformerOil->AddElement(H, 2);
  TransformerOil->AddElement(C, 1);

  //==== Getter Disc Alloy ====
  G4Material *Getter_alloy =
      new G4Material("GAlloy", 4.16 * g / cm3, 3, kStateSolid);
  Getter_alloy->AddElement(Zr, 0.70);
  Getter_alloy->AddElement(V, 0.25);
  Getter_alloy->AddElement(Fe, 0.05);

  //==== Titanium ====
  // G4Material *Titanium =
  //     new G4Material("Titanium", 4.506 * g / cm3, 1, kStateSolid);
  // Titanium->AddElement(Ti, 1);

  //==== Polyethilene ====
  G4Material *poly = new G4Material("poly", 0.95 * g / cm3, 2);
  poly->AddElement(C, 1);
  poly->AddElement(H, 2);

  G4Material *B_poly = new G4Material("B_poly", 0.93 * g / cm3, 4,
                                      kStateSolid);  // B-doped, from
  // http://lss.fnal.gov/archive/2000/fn/FN-697.pdf
  B_poly->AddElement(H, 0.116);
  B_poly->AddElement(C, 0.612);
  B_poly->AddElement(B, 0.05);
  B_poly->AddElement(O, 0.222);

  //==== Graphite ====
  // G4Isotope* C12 = new G4Isotope("C12", 6, 12);
  // G4Element* C   = new G4Element("TS_C_of_Graphite","C", 1);
  // C->AddIsotope(C12, 1);
  G4Material *Graphite = new G4Material(
      "Graphite", 2.27 * g / cm3, 1, kStateSolid, 293 * kelvin, 1 * atmosphere);
  Graphite->AddElement(C, 1);
}

G4MaterialPropertiesTable *Xenon1tMaterials::SetWaterOpticalProperties(G4double pWABSL){  
  // Optical properties of Water

  /*
  // Model based on G4 example
  // http://www-pnp.physics.ox.ac.uk/~weber/tmp/v5r26p00n00/Linux-i686/root/montecarlo/g4root/test/exN06/src/ExN06DetectorConstruction.cc
  // Rescaled absorption length to match XENON1T MV data of detected muons
  // Marco, 2009
  const G4int nEntries = 32;
  G4double PhotonEnergy[nEntries] = {
    2.034 * eV, 2.068 * eV, 2.103 * eV, 2.139 * eV, 2.177 * eV, 2.216 * eV,
    2.256 * eV, 2.298 * eV, 2.341 * eV, 2.386 * eV, 2.433 * eV, 2.481 * eV,
    2.532 * eV, 2.585 * eV, 2.640 * eV, 2.697 * eV, 2.757 * eV, 2.820 * eV,
    2.885 * eV, 2.954 * eV, 3.026 * eV, 3.102 * eV, 3.181 * eV, 3.265 * eV,
    3.353 * eV, 3.446 * eV, 3.545 * eV, 3.649 * eV, 3.760 * eV, 3.877 * eV,
    4.002 * eV, 4.136 * eV};
  G4double RefractiveIndex1[nEntries] = {
    1.3435, 1.344,  1.3445, 1.345,  1.3455, 1.346,  1.3465, 1.347,
    1.3475, 1.348,  1.3485, 1.3492, 1.35,   1.3505, 1.351,  1.3518,
    1.3522, 1.3530, 1.3535, 1.354,  1.3545, 1.355,  1.3555, 1.356,
    1.3568, 1.3572, 1.358,  1.3585, 1.359,  1.3595, 1.36,   1.3608};
  G4double Absorption1[nEntries] = {
    3.448 * m,  4.082 * m,  6.329 * m,  9.174 * m,  12.346 * m, 13.889 * m,
    15.152 * m, 17.241 * m, 18.868 * m, 20.000 * m, 26.316 * m, 35.714 * m,
    45.455 * m, 47.619 * m, 52.632 * m, 52.632 * m, 55.556 * m, 52.632 * m,
    52.632 * m, 47.619 * m, 45.455 * m, 41.667 * m, 37.037 * m, 33.333 * m,
    30.000 * m, 28.500 * m, 27.000 * m, 24.500 * m, 22.000 * m, 19.500 * m,
    17.500 * m, 14.500 * m};
  for (Int_t i = 0; i < nEntries;
       ++i) {  // MS170215 to increase the absorption length in Water, to match
               // the real data
    Absorption1[i] = Absorption1[i] * 10.;
  }
  */

  // Model from Super-Kamiokande calibration
  // https://www.sciencedirect.com/science/article/abs/pii/S016890021301646X?via%3Dihub
  // Implemented by Shingo
  const G4int n_Water=56;
  G4double Water_Energy[n_Water] ={  
  1.5708*eV, 1.59068*eV, 1.61108*eV, 1.632*eV, 1.65347*eV,    
  1.67552*eV, 1.69816*eV, 1.72142*eV, 1.74533*eV, 1.76992*eV,    
  1.7952*eV, 1.82122*eV, 1.848*eV, 1.87558*eV, 1.904*eV,    
  1.93329*eV, 1.9635*eV, 1.99467*eV, 2.02684*eV, 2.06007*eV,    
  2.0944*eV, 2.1299*eV, 2.16662*eV, 2.20463*eV, 2.244*eV,    
  2.2848*eV, 2.32711*eV, 2.37102*eV, 2.41662*eV, 2.464*eV,    
  2.51328*eV, 2.56457*eV, 2.618*eV, 2.6737*eV, 2.73183*eV,    
  2.79253*eV, 2.856*eV, 2.92242*eV, 2.992*eV, 3.06498*eV,    
  3.1416*eV, 3.22215*eV, 3.30695*eV, 3.39632*eV, 3.49067*eV,    
  3.5904*eV, 3.696*eV, 3.808*eV, 3.927*eV, 4.05368*eV,    
  4.1888*eV, 4.33324*eV, 4.488*eV, 4.65422*eV, 4.83323*eV,    
  5.02656*eV    
  };    
  // Refractive index
  G4double ARIND = 1.;     
  G4double Water_RIND[n_Water] = {     
  1.32865*ARIND, 1.32885*ARIND, 1.32906*ARIND, 1.32927*ARIND, 1.32948*ARIND,    
  1.3297*ARIND, 1.32992*ARIND, 1.33014*ARIND, 1.33037*ARIND, 1.3306*ARIND,    
  1.33084*ARIND, 1.33109*ARIND, 1.33134*ARIND, 1.3316*ARIND, 1.33186*ARIND,    
  1.33213*ARIND, 1.33241*ARIND, 1.3327*ARIND, 1.33299*ARIND, 1.33329*ARIND,    
  1.33361*ARIND, 1.33393*ARIND, 1.33427*ARIND, 1.33462*ARIND, 1.33498*ARIND,    
  1.33536*ARIND, 1.33576*ARIND, 1.33617*ARIND, 1.3366*ARIND, 1.33705*ARIND,    
  1.33753*ARIND, 1.33803*ARIND, 1.33855*ARIND, 1.33911*ARIND, 1.3397*ARIND,    
  1.34033*ARIND, 1.341*ARIND, 1.34172*ARIND, 1.34248*ARIND, 1.34331*ARIND,    
  1.34419*ARIND, 1.34516*ARIND, 1.3462*ARIND, 1.34733*ARIND, 1.34858*ARIND,    
  1.34994*ARIND, 1.35145*ARIND, 1.35312*ARIND, 1.35498*ARIND, 1.35707*ARIND,    
  1.35943*ARIND, 1.36211*ARIND, 1.36518*ARIND, 1.36872*ARIND, 1.37287*ARIND,    
  1.37776*ARIND    
  };    
  // Absorption length
  // Default = 1 (SK model)
  // Custom scaling factor can be set from preinit
  G4double AABS = pWABSL; 
  G4double Water_ABSL[n_Water] ={  
  0.139683*AABS*m, 0.156176*AABS*m, 0.177083*AABS*m, 0.204455*AABS*m, 0.241834*AABS*m,    
  0.29594*AABS*m, 0.381233*AABS*m, 0.535598*AABS*m, 0.812298*AABS*m, 1.20907*AABS*m,    
  1.60235*AABS*m, 1.93765*AABS*m, 2.1501*AABS*m, 2.27739*AABS*m, 2.4384*AABS*m,    
  2.94021*AABS*m, 3.21627*AABS*m, 3.42786*AABS*m, 3.62798*AABS*m, 3.78008*AABS*m,    
  4.49328*AABS*m, 7.39287*AABS*m, 11.1387*AABS*m, 14.3493*AABS*m, 16.1021*AABS*m,    
  17.6308*AABS*m, 20.9927*AABS*m, 22.9074*AABS*m, 24.2871*AABS*m, 30.4913*AABS*m,    
  48.261*AABS*m, 65.1566*AABS*m, 76.467*AABS*m, 90.8207*AABS*m, 107.806*AABS*m,    
  134.586*AABS*m, 167.696*AABS*m, 208.006*AABS*m, 255.929*AABS*m, 310.919*AABS*m,    
  370.863*AABS*m, 431.61*AABS*m, 487.11*AABS*m, 530.546*AABS*m, 556.33*AABS*m,    
  561.943*AABS*m, 548.529*AABS*m, 519.973*AABS*m, 481.267*AABS*m, 437.106*AABS*m,    
  391.171*AABS*m, 345.988*AABS*m, 303.106*AABS*m, 263.363*AABS*m, 227.13*AABS*m,    
  194.489*AABS*m    
  };    
  // Rayleigh scattering length  
  G4double ARAS = 1.;     
  G4double Water_RAYLEIGH[n_Water] = {     
  4038.69*ARAS*m, 3826.67*ARAS*m, 3623*ARAS*m, 3427.46*ARAS*m, 3239.84*ARAS*m,    
  3059.93*ARAS*m, 2887.52*ARAS*m, 2722.41*ARAS*m, 2564.38*ARAS*m, 2413.24*ARAS*m,    
  2268.8*ARAS*m, 2130.85*ARAS*m, 1999.2*ARAS*m, 1873.67*ARAS*m, 1754.07*ARAS*m,    
  1640.21*ARAS*m, 1531.91*ARAS*m, 1428.99*ARAS*m, 1331.28*ARAS*m, 1238.6*ARAS*m,    
  1150.79*ARAS*m, 1067.67*ARAS*m, 989.081*ARAS*m, 914.859*ARAS*m, 844.845*ARAS*m,    
  778.881*ARAS*m, 716.814*ARAS*m, 658.491*ARAS*m, 603.763*ARAS*m, 552.485*ARAS*m,    
  504.514*ARAS*m, 459.707*ARAS*m, 417.928*ARAS*m, 379.041*ARAS*m, 342.913*ARAS*m,    
  309.415*ARAS*m, 278.42*ARAS*m, 249.803*ARAS*m, 223.443*ARAS*m, 199.22*ARAS*m,    
  177.02*ARAS*m, 156.729*ARAS*m, 138.236*ARAS*m, 121.435*ARAS*m, 106.22*ARAS*m,    
  92.4896*ARAS*m, 80.1458*ARAS*m, 69.0924*ARAS*m, 59.2368*ARAS*m, 50.4893*ARAS*m,    
  42.7636*ARAS*m, 35.9762*ARAS*m, 30.0472*ARAS*m, 24.8998*ARAS*m, 20.4607*ARAS*m,    
  16.6602*ARAS*m    
  };    
  /*G4double AMIE = 1.;     
  G4double Water_MIE[n_GdWater] = {     
  2886.39*AMIE*m, 2885.19*AMIE*m, 2885.17*AMIE*m, 2886.42*AMIE*m, 2889.04*AMIE*m,    
  2893.15*AMIE*m, 2898.87*AMIE*m, 2906.34*AMIE*m, 2915.72*AMIE*m, 2927.18*AMIE*m,    
  2940.93*AMIE*m, 2957.17*AMIE*m, 2976.16*AMIE*m, 2998.19*AMIE*m, 3023.56*AMIE*m,    
  3052.64*AMIE*m, 3085.85*AMIE*m, 3123.66*AMIE*m, 3166.62*AMIE*m, 3215.37*AMIE*m,    
  3270.63*AMIE*m, 3333.28*AMIE*m, 3404.3*AMIE*m, 3484.86*AMIE*m, 3576.37*AMIE*m,    
  3680.43*AMIE*m, 3798.99*AMIE*m, 3934.32*AMIE*m, 4089.13*AMIE*m, 4266.59*AMIE*m,    
  4470.39*AMIE*m, 4704.76*AMIE*m, 4974.4*AMIE*m, 5284.15*AMIE*m, 5638.39*AMIE*m,    
  6039.67*AMIE*m, 6486.11*AMIE*m, 6966.88*AMIE*m, 7455.04*AMIE*m, 7898.48*AMIE*m,    
  8213.09*AMIE*m, 8289.21*AMIE*m, 8025.17*AMIE*m, 7384.75*AMIE*m, 6438.45*AMIE*m,    
  5340.81*AMIE*m, 4256.02*AMIE*m, 3295.93*AMIE*m, 2506.42*AMIE*m, 1886.58*AMIE*m,    
  1413.07*AMIE*m, 1056.65*AMIE*m, 790.192*AMIE*m, 591.39*AMIE*m, 442.979*AMIE*m,    
  331.97*AMIE*m    
  };*/    
  
  G4MaterialPropertiesTable* Water_MPT = new G4MaterialPropertiesTable();     
  Water_MPT->AddProperty("RINDEX", Water_Energy, Water_RIND, n_Water);   
  Water_MPT->AddProperty("ABSLENGTH", Water_Energy, Water_ABSL, n_Water);   
  Water_MPT->AddProperty("RAYLEIGH", Water_Energy, Water_RAYLEIGH, n_Water);   
  //Water_MPT->AddConstProperty("SCINTILLATIONYIELD", 50./MeV);
  
  //G4cout << "Xenon1tMaterials: Water - Optical properties based on Super-Kamiokande model" << G4endl;

  return Water_MPT;
}

G4MaterialPropertiesTable *Xenon1tMaterials::SetGdWaterOpticalProperties(G4double pWABSL){  
  // Optical properties of GdWater (0.2% Gd concentration)

  // Model from Super-Kamiokande calibration
  // https://www.sciencedirect.com/science/article/abs/pii/S016890021301646X?via%3Dihub
  // Implemented by Shingo
  const G4int n_Water=56;
  G4double Water_Energy[n_Water] ={  
  1.5708*eV, 1.59068*eV, 1.61108*eV, 1.632*eV, 1.65347*eV,    
  1.67552*eV, 1.69816*eV, 1.72142*eV, 1.74533*eV, 1.76992*eV,    
  1.7952*eV, 1.82122*eV, 1.848*eV, 1.87558*eV, 1.904*eV,    
  1.93329*eV, 1.9635*eV, 1.99467*eV, 2.02684*eV, 2.06007*eV,    
  2.0944*eV, 2.1299*eV, 2.16662*eV, 2.20463*eV, 2.244*eV,    
  2.2848*eV, 2.32711*eV, 2.37102*eV, 2.41662*eV, 2.464*eV,    
  2.51328*eV, 2.56457*eV, 2.618*eV, 2.6737*eV, 2.73183*eV,    
  2.79253*eV, 2.856*eV, 2.92242*eV, 2.992*eV, 3.06498*eV,    
  3.1416*eV, 3.22215*eV, 3.30695*eV, 3.39632*eV, 3.49067*eV,    
  3.5904*eV, 3.696*eV, 3.808*eV, 3.927*eV, 4.05368*eV,    
  4.1888*eV, 4.33324*eV, 4.488*eV, 4.65422*eV, 4.83323*eV,    
  5.02656*eV    
  };    
  // Refractive index
  G4double ARIND = 1.;     
  G4double Water_RIND[n_Water] = {     
  1.32865*ARIND, 1.32885*ARIND, 1.32906*ARIND, 1.32927*ARIND, 1.32948*ARIND,    
  1.3297*ARIND, 1.32992*ARIND, 1.33014*ARIND, 1.33037*ARIND, 1.3306*ARIND,    
  1.33084*ARIND, 1.33109*ARIND, 1.33134*ARIND, 1.3316*ARIND, 1.33186*ARIND,    
  1.33213*ARIND, 1.33241*ARIND, 1.3327*ARIND, 1.33299*ARIND, 1.33329*ARIND,    
  1.33361*ARIND, 1.33393*ARIND, 1.33427*ARIND, 1.33462*ARIND, 1.33498*ARIND,    
  1.33536*ARIND, 1.33576*ARIND, 1.33617*ARIND, 1.3366*ARIND, 1.33705*ARIND,    
  1.33753*ARIND, 1.33803*ARIND, 1.33855*ARIND, 1.33911*ARIND, 1.3397*ARIND,    
  1.34033*ARIND, 1.341*ARIND, 1.34172*ARIND, 1.34248*ARIND, 1.34331*ARIND,    
  1.34419*ARIND, 1.34516*ARIND, 1.3462*ARIND, 1.34733*ARIND, 1.34858*ARIND,    
  1.34994*ARIND, 1.35145*ARIND, 1.35312*ARIND, 1.35498*ARIND, 1.35707*ARIND,    
  1.35943*ARIND, 1.36211*ARIND, 1.36518*ARIND, 1.36872*ARIND, 1.37287*ARIND,    
  1.37776*ARIND    
  };    
  // Absorption length
  // Default = 1 (SK model)
  // Custom scaling factor can be set from preinit
  G4double AABS = pWABSL; 
  G4double Water_ABSL[n_Water] ={  
  0.139683*AABS*m, 0.156176*AABS*m, 0.177083*AABS*m, 0.204455*AABS*m, 0.241834*AABS*m,    
  0.29594*AABS*m, 0.381233*AABS*m, 0.535598*AABS*m, 0.812298*AABS*m, 1.20907*AABS*m,    
  1.60235*AABS*m, 1.93765*AABS*m, 2.1501*AABS*m, 2.27739*AABS*m, 2.4384*AABS*m,    
  2.94021*AABS*m, 3.21627*AABS*m, 3.42786*AABS*m, 3.62798*AABS*m, 3.78008*AABS*m,    
  4.49328*AABS*m, 7.39287*AABS*m, 11.1387*AABS*m, 14.3493*AABS*m, 16.1021*AABS*m,    
  17.6308*AABS*m, 20.9927*AABS*m, 22.9074*AABS*m, 24.2871*AABS*m, 30.4913*AABS*m,    
  48.261*AABS*m, 65.1566*AABS*m, 76.467*AABS*m, 90.8207*AABS*m, 107.806*AABS*m,    
  134.586*AABS*m, 167.696*AABS*m, 208.006*AABS*m, 255.929*AABS*m, 310.919*AABS*m,    
  370.863*AABS*m, 431.61*AABS*m, 487.11*AABS*m, 530.546*AABS*m, 556.33*AABS*m,    
  561.943*AABS*m, 548.529*AABS*m, 519.973*AABS*m, 481.267*AABS*m, 437.106*AABS*m,    
  391.171*AABS*m, 345.988*AABS*m, 303.106*AABS*m, 263.363*AABS*m, 227.13*AABS*m,    
  194.489*AABS*m    
  };    
  // Rayleigh scattering length  
  G4double ARAS = 1.;     
  G4double Water_RAYLEIGH[n_Water] = {     
  4038.69*ARAS*m, 3826.67*ARAS*m, 3623*ARAS*m, 3427.46*ARAS*m, 3239.84*ARAS*m,    
  3059.93*ARAS*m, 2887.52*ARAS*m, 2722.41*ARAS*m, 2564.38*ARAS*m, 2413.24*ARAS*m,    
  2268.8*ARAS*m, 2130.85*ARAS*m, 1999.2*ARAS*m, 1873.67*ARAS*m, 1754.07*ARAS*m,    
  1640.21*ARAS*m, 1531.91*ARAS*m, 1428.99*ARAS*m, 1331.28*ARAS*m, 1238.6*ARAS*m,    
  1150.79*ARAS*m, 1067.67*ARAS*m, 989.081*ARAS*m, 914.859*ARAS*m, 844.845*ARAS*m,    
  778.881*ARAS*m, 716.814*ARAS*m, 658.491*ARAS*m, 603.763*ARAS*m, 552.485*ARAS*m,    
  504.514*ARAS*m, 459.707*ARAS*m, 417.928*ARAS*m, 379.041*ARAS*m, 342.913*ARAS*m,    
  309.415*ARAS*m, 278.42*ARAS*m, 249.803*ARAS*m, 223.443*ARAS*m, 199.22*ARAS*m,    
  177.02*ARAS*m, 156.729*ARAS*m, 138.236*ARAS*m, 121.435*ARAS*m, 106.22*ARAS*m,    
  92.4896*ARAS*m, 80.1458*ARAS*m, 69.0924*ARAS*m, 59.2368*ARAS*m, 50.4893*ARAS*m,    
  42.7636*ARAS*m, 35.9762*ARAS*m, 30.0472*ARAS*m, 24.8998*ARAS*m, 20.4607*ARAS*m,    
  16.6602*ARAS*m    
  };    
  /*G4double AMIE = 1.;     
  G4double Water_MIE[n_GdWater] = {     
  2886.39*AMIE*m, 2885.19*AMIE*m, 2885.17*AMIE*m, 2886.42*AMIE*m, 2889.04*AMIE*m,    
  2893.15*AMIE*m, 2898.87*AMIE*m, 2906.34*AMIE*m, 2915.72*AMIE*m, 2927.18*AMIE*m,    
  2940.93*AMIE*m, 2957.17*AMIE*m, 2976.16*AMIE*m, 2998.19*AMIE*m, 3023.56*AMIE*m,    
  3052.64*AMIE*m, 3085.85*AMIE*m, 3123.66*AMIE*m, 3166.62*AMIE*m, 3215.37*AMIE*m,    
  3270.63*AMIE*m, 3333.28*AMIE*m, 3404.3*AMIE*m, 3484.86*AMIE*m, 3576.37*AMIE*m,    
  3680.43*AMIE*m, 3798.99*AMIE*m, 3934.32*AMIE*m, 4089.13*AMIE*m, 4266.59*AMIE*m,    
  4470.39*AMIE*m, 4704.76*AMIE*m, 4974.4*AMIE*m, 5284.15*AMIE*m, 5638.39*AMIE*m,    
  6039.67*AMIE*m, 6486.11*AMIE*m, 6966.88*AMIE*m, 7455.04*AMIE*m, 7898.48*AMIE*m,    
  8213.09*AMIE*m, 8289.21*AMIE*m, 8025.17*AMIE*m, 7384.75*AMIE*m, 6438.45*AMIE*m,    
  5340.81*AMIE*m, 4256.02*AMIE*m, 3295.93*AMIE*m, 2506.42*AMIE*m, 1886.58*AMIE*m,    
  1413.07*AMIE*m, 1056.65*AMIE*m, 790.192*AMIE*m, 591.39*AMIE*m, 442.979*AMIE*m,    
  331.97*AMIE*m    
  };*/    
  
  G4MaterialPropertiesTable* GdWater_MPT = new G4MaterialPropertiesTable();     
  GdWater_MPT->AddProperty("RINDEX", Water_Energy, Water_RIND, n_Water);   
  GdWater_MPT->AddProperty("ABSLENGTH", Water_Energy, Water_ABSL, n_Water);   
  GdWater_MPT->AddProperty("RAYLEIGH", Water_Energy, Water_RAYLEIGH, n_Water);   
  GdWater_MPT->AddConstProperty("SCINTILLATIONYIELD", 50./MeV);
  
  //G4cout << "Xenon1tMaterials: GdWater - Optical properties based on Super-Kamiokande model" << G4endl;

  return GdWater_MPT;
}

void Xenon1tMaterials::SetLXeTeflonReflectivity(G4double dReflectivity) {
    G4MaterialPropertiesTable *tmp = 
    	pLXeTeflonOpticalSurface->GetMaterialPropertiesTable();
    
    G4double teflon_PP[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double teflon_REFL[3] = {dReflectivity, dReflectivity, dReflectivity};
    tmp->RemoveProperty("REFLECTIVITY");
	tmp->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);

	pLXeTeflonOpticalSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "Xenon1tMaterials: Setting LXe/Teflon surface reflectivity to " << dReflectivity*100. << "%" << G4endl;    
}

void Xenon1tMaterials::SetGXeTeflonReflectivity(G4double dReflectivity) {
    G4MaterialPropertiesTable *tmp = 
    	pGXeTeflonOpticalSurface->GetMaterialPropertiesTable();
    
    G4double teflon_PP[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double teflon_REFL[3] = {dReflectivity, dReflectivity, dReflectivity};
    tmp->RemoveProperty("REFLECTIVITY");
	tmp->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);

	pGXeTeflonOpticalSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "Xenon1tMaterials: Setting GXe/Teflon surface reflectivity to " << dReflectivity*100. << "%" << G4endl;    
}

void Xenon1tMaterials::SetLXeTeflonUnpolishedReflectivity(G4double dReflectivity) {
    G4MaterialPropertiesTable *tmp = 
    	pLXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();
    
    G4double teflon_PP[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double teflon_REFL[3] = {dReflectivity, dReflectivity, dReflectivity};
    tmp->RemoveProperty("REFLECTIVITY");
	tmp->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);

	pLXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "Xenon1tMaterials: Setting LXe/TeflonUnpolished surface reflectivity to " << dReflectivity*100. << "%" << G4endl;    
}

void Xenon1tMaterials::SetGXeTeflonUnpolishedReflectivity(G4double dReflectivity) {
    G4MaterialPropertiesTable *tmp = 
    	pGXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();
    
    G4double teflon_PP[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
    G4double teflon_REFL[3] = {dReflectivity, dReflectivity, dReflectivity};
    tmp->RemoveProperty("REFLECTIVITY");
	tmp->AddProperty("REFLECTIVITY", teflon_PP, teflon_REFL, 3);

	pGXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(tmp);
	G4cout << "Xenon1tMaterials: Setting GXe/TeflonUnpolished surface reflectivity to " << dReflectivity*100. << "%" << G4endl;    
}

void Xenon1tMaterials::SetTeflonReflectivitySpikeLobeBackscatter(G4String type, G4ThreeVector parameters){
  G4MaterialPropertiesTable *tmp;
  if (type=="LXe"){tmp=pLXeTeflonOpticalSurface->GetMaterialPropertiesTable();}
  else if (type == "GXe" ){tmp=pGXeTeflonOpticalSurface->GetMaterialPropertiesTable();}
  else if (type == "LXeUnpolished"){tmp=pLXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();}
  else if (type == "GXeUnpolished" ){tmp=pGXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();}
  else { 
     G4cout << "Error! Unknown type for PTFE reflector : " << type << G4endl; 
     G4Exception("Xenon1tMaterials", "UknownPTFEtype",  FatalException, "Unknown type of reflector");
  }   
  G4double spike = parameters.x();
  G4double lobe = parameters.y();
  G4double backscatter = parameters.z();
  G4cout << type<<" Teflon reflectivity parameters:  "<<G4endl;
  G4cout << "          spike = "<< spike <<G4endl;
  G4cout << "           lobe = "<< lobe <<G4endl;
  G4cout << "    backscatter = "<< backscatter <<G4endl;
  if ( (spike + lobe + backscatter) > 1){
     G4cout << "ERROR! Total sum of components larger than 1" << G4endl;
     G4Exception("Xenon1tMaterials", "RuntimeErrors",  FatalException, "Total sum of reflection components is larger than 1"); }

  G4double pdTeflonPhotonMomentum[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double pdSpecularSpike[3] = {spike,spike,spike};
  G4double pdSpecularLobe[3] = {lobe, lobe, lobe};
  G4double pdBackscatter[3] = {backscatter,backscatter,backscatter};
  
  tmp->RemoveProperty("SPECULARSPIKECONSTANT");
  tmp->AddProperty("SPECULARSPIKECONSTANT",
                   pdTeflonPhotonMomentum, pdSpecularSpike, 3 );
  tmp->RemoveProperty("SPECULARLOBECONSTANT");
  tmp->AddProperty("SPECULARLOBECONSTANT",
                   pdTeflonPhotonMomentum, pdSpecularLobe, 3 );
  tmp->RemoveProperty("BACKSCATTERCONSTANT");
  tmp->AddProperty("BACKSCATTERCONSTANT",
                   pdTeflonPhotonMomentum, pdBackscatter, 3 );
  //tmp->DumpTable();
  if (type=="LXe"){pLXeTeflonOpticalSurface->SetMaterialPropertiesTable(tmp);}
  else if (type == "GXe" ){pGXeTeflonOpticalSurface->SetMaterialPropertiesTable(tmp);}
  else if (type =="LXeUnpolished"){pLXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(tmp);}
  else if (type == "GXeUnpolished" ){pGXeTeflonUnpolishedOpticalSurface->SetMaterialPropertiesTable(tmp);}
  else { 
     G4cout << "Error! Unknown type for PTFE reflector : " << type << G4endl; 
     G4Exception("Xenon1tMaterials", "UknownPTFEtype",  FatalException, "Unknown type of reflector");
  } 
  //DumpTeflonSurfaceParameters(type);
}
void Xenon1tMaterials::SetWireReflectivity(G4String type, G4double refl_){
  G4MaterialPropertiesTable *tmp;
  if (type=="LXe"){ tmp = pLXeWireSurface->GetMaterialPropertiesTable(); }
  else if (type=="GXe"){ tmp = pGXeWireSurface->GetMaterialPropertiesTable(); }
  else{ 
     G4cout << "Error! Trying to set reflectivity to unknown wire location " << type << G4endl; 
     G4Exception("Xenon1tMaterials", "UnknownWireLocation",  FatalException, "Unknown wire location");
  } 
  G4double pdRPhotonMomentum[3] = {6.91 * eV, 6.98 * eV, 7.05 * eV};
  G4double pdWireReflectivity[3] = {refl_,refl_,refl_};
  G4cout<< "Setting reflectivity for electrode wires in "<<type<<" to "<<100.*refl_<<" %"<<G4endl;
  tmp->RemoveProperty("REFLECTIVITY");
  tmp->AddProperty("REFLECTIVITY",pdRPhotonMomentum,pdWireReflectivity,3 );
  if (type=="LXe"){ pLXeWireSurface->SetMaterialPropertiesTable(tmp); }
  else if (type=="GXe"){ pGXeWireSurface->SetMaterialPropertiesTable(tmp); }
  else{ 
     G4cout << "Error! Trying to set reflectivity to unknown wire location " << type << G4endl; 
     G4Exception("Xenon1tMaterials", "UnknownWireLocation",  FatalException, "Unknown wire location");
  } 
  // G4cout<<"Setting reflectivity of wires in "<<type<<" to "<<refl_<<G4endl;
}


void Xenon1tMaterials::DumpTeflonSurfaceParameters(G4String type){
  G4MaterialPropertiesTable *tmp;
  if (type=="LXe"){tmp=pLXeTeflonOpticalSurface->GetMaterialPropertiesTable();}
  else if (type == "GXe" ){tmp=pGXeTeflonOpticalSurface->GetMaterialPropertiesTable();}
  else if (type =="LXeUnpolished"){tmp=pLXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();}
  else if (type == "GXeUnpolished" ){tmp=pGXeTeflonUnpolishedOpticalSurface->GetMaterialPropertiesTable();}
  else { 
     G4cout << "Error! Unknown type for PTFE reflector : " << type << G4endl; 
     G4Exception("Xenon1tMaterials", "UknownPTFEtype",  FatalException, "Unknown type of reflector");
  }   
  G4cout << "All properties of Teflon suface type : " << type << G4endl;
  tmp->DumpTable();
}

//////////////////////////////////////////////////////////
void Xenon1tMaterials::SetPhCathRef(G4String name )
//////////////////////////////////////////////////////////
{
  // input photocathode reflection and absorption table from database
  //G4String DataBaseDir = getenv("Xenon1tMC_DATABASE_DIR");
  G4String DataBaseDir = "./macros/events/";

  G4double WaveLength[11]={175,175,200,250,300,400,500,550,600,700,700};
  G4double Momentum[11]={8.000*eV,7.085*eV,6.199*eV,4.959*eV,4.133*eV,
			 3.100*eV,2.480*eV,2.254*eV,2.066*eV,1.771*eV,1.600*eV};
  G4double WaveNum[11]={0,1,2,3,4,5,6,7,8,9,10};
  pmctsurf_mt->AddProperty("PHCATHREFMOM", Momentum, WaveNum, 11);

  const G4int ANG_NUM = 200;
  G4double ANG[ANG_NUM];
  G4double Rp[ANG_NUM];
  G4double Rs[ANG_NUM];
  //G4double Tp[ANG_NUM];
  //G4double Ts[ANG_NUM];
  G4double Ap[ANG_NUM];
  G4double As[ANG_NUM];
  
  std::ostringstream wavel;
  std::ostringstream numss;
  G4String PhCathRefFileName;
  G4String PhCathRefRp;
  G4String PhCathRefRs;
  G4String PhCathRefAp;
  G4String PhCathRefAs;

  for (int iwave=0; iwave<11 ;iwave++){
    wavel<<WaveLength[iwave];
    numss<<iwave;

    PhCathRefFileName = DataBaseDir + "/" + name 
      + "/quartz-cathode-" + wavel.str() + "nm.dat" ;
    PhCathRefRp = "PHCATHREFRP_" + numss.str();
    PhCathRefRs = "PHCATHREFRS_" + numss.str();
    PhCathRefAp = "PHCATHREFAP_" + numss.str();
    PhCathRefAs = "PHCATHREFAS_" + numss.str();
    std::ifstream PhCathRefFile(PhCathRefFileName.c_str());
    if(!PhCathRefFile){
      G4cout <<"FileName:"<<PhCathRefFileName<<G4endl;
      G4cout <<"could not be found!"<<G4endl;
      G4cout <<"PhCathRef has not be applied."<<G4endl;
      //G4cout <<"All PMTs have constant QE. The value is "<<thePCEff<<G4endl;
    }
    else{
      G4cout<<"Using DataBase::PMT Photocahode reflection : "<<G4endl;
      G4cout<<"  --->"<<PhCathRefFileName<<G4endl;
      int iNum=0;
      double tmp,tmp2;
      std::string line;
      while(PhCathRefFile && getline(PhCathRefFile,line)){
	if(line[0]!='#' && iNum<ANG_NUM){
	  std::istringstream istr(line);
	  istr>>ANG[iNum]>>Rs[iNum]>>Rp[iNum]>>tmp>>tmp2>>As[iNum]>>Ap[iNum];
	  iNum++;
	}
      }
      PhCathRefFile.close();
      wavel.clear();
      wavel.str("");
      numss.clear();
      numss.str("");

      pmctsurf_mt->AddProperty(PhCathRefRp.c_str(), ANG, Rp, ANG_NUM);
      pmctsurf_mt->AddProperty(PhCathRefRs.c_str(), ANG, Rs, ANG_NUM);
      pmctsurf_mt->AddProperty(PhCathRefAp.c_str(), ANG, Ap, ANG_NUM);
      pmctsurf_mt->AddProperty(PhCathRefAs.c_str(), ANG, As, ANG_NUM);
    }
  }
  //pmctsurf_mt->DumpTable();
}

void Xenon1tMaterials::SetQETable(G4String name, G4int cnbpmts)
{
  // input QE table from database
  G4String DataBaseDir = "./macros/events/";
  G4String QETableFileName = DataBaseDir + "/QEtable_" + name + ".dat";
  std::ifstream QETableFile(QETableFileName.c_str());
  if(!QETableFile){
    G4cout <<"FileName:"<<QETableFileName<<G4endl;
    G4cout <<"could not be found!"<<G4endl;
    G4cout <<"QETable has not be applied."<<G4endl;
    G4cout <<"All PMTs have constant QE. The value is "<<thePCEff<<G4endl;
  }
  else{
	G4int nbpmts;
	if(name=="XENON1T")nbpmts=248;
	else if(name=="XENONnT")nbpmts=494;
	if(cnbpmts!=nbpmts){
		G4cout<<"Number of PMTs doesn't match with File..."<<G4endl;
	}
    const G4int PMT_NUM = 500;
    G4double COPYNO[PMT_NUM];
	for(int i=0;i<PMT_NUM;i++){COPYNO[i]=i;}
    G4double aQE[PMT_NUM]={0,};
    G4cout<<"Using DataBase::PMT QE Table : "<<G4endl;
    G4cout<<"  --->"<<QETableFileName<<G4endl;
    G4int iNum=0;
    std::string tmp1,tmp2;
    while(iNum<PMT_NUM){
        QETableFile>>tmp1>>tmp2;
        aQE[iNum]=std::stod(tmp2);
        iNum++;
    }
    QETableFile.close();
	//for(int i=0;i<PMT_NUM;i++){
    //    G4cout<<i<<" "<<aQE[i]<<G4endl;
    //}

    pmctsurf_mt->AddProperty("XENON1TQETABLE", COPYNO, aQE, PMT_NUM);

    //pmctsurf_mt->DumpTable();
    //rpmctsurf_mt->DumpTable();
  }

}
