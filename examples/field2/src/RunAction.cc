
#include "RunAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "DetectorConstruction.hh"
#include "Run.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "HistoManager.hh"
#include "G4ParticleGun.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction()
: G4UserRunAction()
{
// Book predefined histograms
  fHistoManager = new HistoManager();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{ 
delete fHistoManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{
  return new Run; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run* run)
{ 
  //inform the runManager to save random number seed
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);
  G4cout << "### Run " << run->GetRunID() << " start." << G4endl;

  //histograms
         
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
  } 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run* run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0) return;
  
  const Run* b1Run = static_cast<const Run*>(run);

  // Compute energy deposit
  //
  G4double edep  = b1Run->GetEdep();
 
  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;

  if (generatorAction)
  {
    G4ParticleGun* particleGun = generatorAction->GetParticleGun();
 

    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy,"Energy");
   G4ThreeVector  particlePosition = particleGun-> G4VPrimaryGenerator::GetParticlePosition();
  runCondition += " Start proton position: ";
    runCondition += G4BestUnit(particlePosition,"Length");

  }


 // save histograms
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {    
    analysisManager->Write();
    analysisManager->CloseFile();
  }  
       
  // Print
    
  if (IsMaster()) {
    G4cout
     << "\n--------------------End of Global Run-----------------------";
  }
  else {
    G4cout
     << "\n--------------------End of Local Run------------------------";
  }
  
  G4cout
     << "\n The run consists of " << nofEvents << " "
<< runCondition
     << "\n Enery deposited in sensitive volume SSD: " << G4BestUnit(edep,"Energy") 
     << "\n------------------------------------------------------------\n"
     << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
