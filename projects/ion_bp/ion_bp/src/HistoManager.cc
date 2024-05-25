
#include "HistoManager.hh"
#include "G4UnitsTable.hh"

#include <CLHEP/Units/SystemOfUnits.h>
#include <G4AnalysisManager.hh>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("bp_vac_hist_torr"),fRootFile(0), 
 fNtuple1(0), fVar1(0), fVar2(0)
{
  BookHistos(); // for G4AnalysisManager
  fNtuple1 = 0; //tree
  for (G4int k=0; k<MaxHisto; k++) fHisto[k] = 0; //histos  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
  if ( fRootFile ) delete fRootFile;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::BookTree()
{ 
}

void HistoManager::FillTree(G4double var1, G4double var2, G4double var3, G4double var4,
G4double var5, G4double var6, G4double var7, G4double var8, G4double var9, G4double var10, G4double var11)
{
 fVar1 = var1;
 fVar2 = var2;
 fVar3 = var3;
 fVar4 = var4;
 fVar5 = var5;
 fVar6 = var6;
 fVar7 = var7;
 fVar8 = var8;
 fVar6 = var9;
 fVar7 = var10;
 fVar8 = var11;

}

void HistoManager::FillHisto(G4int ih, G4double xbin, G4double weight)
{
}

void HistoManager::SaveTree()
{ 
  G4String fileName = "bp_vac_tree_torr.root";
}

void HistoManager::BookHistos()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histograms start values
  const G4int kMaxHistoH1 = 25;
  const G4int kMaxHistoH2 = 20;
  const G4String id1[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "10", "11", "12", "13", "14", "15", "16", "17", "18", "19",
                           "20", "21", "22", "23", "24"};      // H1-histos
  const G4String id2[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                           "10", "11", "12", "13", "14", "15", "16", "17", "18", "19"};    // H2-histos
  const G4String title1[] =
                { "Dummy",                                                  //0
                  "Energy deposit in detector#1",                           //1
                  "Energy deposit in detector#2",                           //2   
                  "Energy deposit in detector#3",                           //3
                  "Energy deposit in detector#4",                           //4
                  "Energy deposit in detector#5",                           //5
                  "Energy deposit in detector#6",                           //6
                  "dummy","dummy","dummy","dummy","dummy","dummy","dummy",  //7-13                      
                  "dummy","dummy","dummy","dummy","dummy","dummy","dummy",  //14-20
                  "dummy","dummy","dummy","dummy"                           //21-24
               };
 const G4String title2[] =
                { "XY-distribution of beam particles",                    //0
                  "XY-distribution of electrons through Sts1",            //1 
                  "XY-distribution of electrons through Sts2",            //2 
                  "XY-distribution of electrons through Sts3",            //3 
                  "XY-distribution of electrons through Sts4",            //4  
                  "dummy","dummy","dummy","dummy","dummy","dummy",        //5-10
                  "XY-distribution of electrons through Gem1",            //11 
                  "XY-distribution of electrons through Gem2",            //12 
                  "XY-distribution of electrons through Gem3",            //13 
                  "XY-distribution of electrons through Gem4",            //14 
                  "XY-distribution of electrons through Gem5",            //15 
                  "XY-distribution of electrons through Gem6",            //16 
                  "XY-distribution of electrons through Gem7",            //17 
                  "dummy","dummy","dummy"                                 //18-20
                };

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Default values (to be reset via /analysis/h2/set command)               
  G4int nbins1 = 100;
  G4double vmin1 = 0.;
  G4double vmax1 = 100.;
  G4int nbins2 = 100;
  G4double vmin2 = 0.;
  G4double vmax2 = 100.;
  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHistoH1; k++) {
    G4int ih1 = analysisManager->CreateH1(id1[k], title1[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih1, false);
  }
  for (G4int k=0; k<kMaxHistoH2; k++) {
    G4int ih2 = analysisManager->CreateH2(id2[k], title2[k], nbins1, vmin1, vmax1, nbins2, vmin2, vmax2);
    analysisManager->SetH2Activation(ih2, false);
  }
}
