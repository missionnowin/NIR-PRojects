
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("kontest")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histograms start values
  const G4int kMaxHisto1 = 10;
  const G4int kMaxHisto2 = 5;
  const G4String id[] = { "0", "1", "2", "3", "4","5","6","7","8","9"};
                        
  const G4String title1[] =
                { "dummy",                                                //0
                  "Number of fired strips as function of theta",          //1
                  "Number of fired strips",                               //2
                  "Energy deposit in SSD",                                //3
                  "Signal distribution in claster of 1 strips",           //4
                  "Signal distribution in claster of 2 strips",           //5 
                  "Signal distribution in claster of 3 strips",           //6 
                  "Signal distribution in claster of 4 strips",           //7 
                  "Signal distribution in claster of 5 strips",           //8 
                  "Signal distribution in claster of 6 strips",           //9 
                };
 const G4String title2[] =
                { "dummy",                                                //0
                  "Number of fired strips as function of theta",          //1
                  "Number of fired strips",                               //2
                  "Energy deposit in SSD",                                //3
                  "dummy",                                                //4
                 };


  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto1; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title1[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, false);
  }
 for (G4int k=0; k<kMaxHisto2; k++) {
    G4int ih = analysisManager->CreateH2(id[k], title2[k], nbins, vmin, vmax, nbins, vmin, vmax);
    analysisManager->SetH2Activation(ih, false);
  } 
}
