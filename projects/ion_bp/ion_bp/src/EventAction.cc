
#include "EventAction.hh"
#include "Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"
#include <G4AnalysisManager.hh>

#include "HistoManager.hh"

#include <iostream>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(HistoManager* histo)
: G4UserEventAction(),fHistoManager(histo),
  fEdep(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
  fEdepTot = 0.;
  fElectronsGem1 = 0;
  fElectronsGem2 = 0;
  fElectronsGem3 = 0;
  fElectronsGem4 = 0;
  fElectronsGem5 = 0;
  fElectronsGem6 = 0;
  fElectronsGem7 = 0;
  fElectronsSts1 = 0;
  fElectronsSts2 = 0;
  fElectronsSts3 = 0;
  fElectronsSts4 = 0;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{   
  // Get statistics in given event
  Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);
   G4cout.precision(6); 

  G4cout << " Number of electrons in StsSt1: " << fElectronsSts1 << G4endl; 
  G4cout << " Number of electrons in StsSt2: " << fElectronsSts2 << G4endl; 
  G4cout << " Number of electrons in StsSt3: " << fElectronsSts3 << G4endl; 
  G4cout << " Number of electrons in StsSt4: " << fElectronsSts4 << G4endl; 
  G4cout << " Number of electrons in GemSt1: " << fElectronsGem1 << G4endl; 
  G4cout << " Number of electrons in GemSt2: " << fElectronsGem2 << G4endl; 
  G4cout << " Number of electrons in GemSt3: " << fElectronsGem3 << G4endl; 
  G4cout << " Number of electrons in GemSt4: " << fElectronsGem4 << G4endl;   
  G4cout << " Number of electrons in GemSt5: " << fElectronsGem5 << G4endl; 
  G4cout << " Number of electrons in GemSt6: " << fElectronsGem6 << G4endl; 
  G4cout << " Number of electrons in GemSt7: " << fElectronsGem7 << G4endl; 

// Fill G4 histograms
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  

// Fill ROOT tree and histograms
 fHistoManager->FillTree(fElectronsSts1,fElectronsSts2,fElectronsSts3,fElectronsSts4,
fElectronsGem1,fElectronsGem2,fElectronsGem3,fElectronsGem4,fElectronsGem5,fElectronsGem6,fElectronsGem7);
 fHistoManager->FillHisto(1,fElectronsSts1);
 fHistoManager->FillHisto(2,fElectronsSts2); 
 fHistoManager->FillHisto(3,fElectronsSts3);
 fHistoManager->FillHisto(4,fElectronsSts4); 
 fHistoManager->FillHisto(5,fElectronsGem1);
 fHistoManager->FillHisto(6,fElectronsGem2);
 fHistoManager->FillHisto(7,fElectronsGem3);
 fHistoManager->FillHisto(8,fElectronsGem4);
 fHistoManager->FillHisto(9,fElectronsGem5);
 fHistoManager->FillHisto(10,fElectronsGem6);
 fHistoManager->FillHisto(11,fElectronsGem7);

// Clear parameters
 
  fEdepTot=0.;
  fElectronsGem1 = 0;
  fElectronsGem2 = 0;
  fElectronsGem3 = 0;
  fElectronsGem4 = 0;
  fElectronsGem5 = 0;
  fElectronsGem6 = 0;
  fElectronsGem7 = 0;
  fElectronsSts1 = 0;
  fElectronsSts2 = 0;
  fElectronsSts3 = 0;
  fElectronsSts4 = 0;
  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
