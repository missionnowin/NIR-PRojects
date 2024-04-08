
#include "EventAction.hh"
#include "Run.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "PrimaryGeneratorAction.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleGun.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
: G4UserEventAction(),
  fEdep(0.)
{} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{    
  fEdep = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event*)
{   
  // accumulate statistics in B1Run
  Run* run 
    = static_cast<Run*>(
        G4RunManager::GetRunManager()->GetNonConstCurrentRun());
  run->AddEdep(fEdep);

  const PrimaryGeneratorAction* generatorAction
   = static_cast<const PrimaryGeneratorAction*>
     (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;

  if (generatorAction)
  {
    G4ParticleGun* particleGun = generatorAction->GetParticleGun();
 
    G4ThreeVector  particlePosition = particleGun-> G4VPrimaryGenerator::GetParticlePosition();
  runCondition = " Current position: ";
    runCondition += G4BestUnit(particlePosition,"Length");
 G4cout << runCondition  << G4endl;
  }




}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
