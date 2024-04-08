#include<G4Step.hh>
#include<G4INCLGlobals.hh>
#include<fstream>
#include<iostream>
#include"SensitiveDetector.hh"
#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"
#include "HistoManager.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name)
{
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
 G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

   G4double maxLength = 1*mm;
   step->SetStepLength(maxLength);

  double EnergyDep = step->GetTotalEnergyDeposit();
  G4String volume_sens = step->GetTrack()->GetVolume()->GetName();
  G4int particle_code = step->GetTrack()->GetDynamicParticle()->GetPDGcode();

//  if(particle_code == 2212 && volume_sens == "physSSD" ) {
 if(volume_sens == "physSSD" ) {
	  G4cout<< "Deposit energy of particle = " << G4BestUnit(EnergyDep,"Energy") <<" in volume: " << volume_sens << G4endl;
	  G4ThreeVector VecIn = step->GetPreStepPoint()->GetPosition();
	  G4cout<< "Input point of current step: " << G4BestUnit(VecIn,"Length") <<" in volume: " << volume_sens << G4endl;
	  G4ThreeVector VecOut = step->GetPostStepPoint()->GetPosition();
	  G4cout<< "Output point " << G4BestUnit(VecOut,"Length") <<" in sensitive volume: " << volume_sens << G4endl;
  analysisManager->FillH1(3,EnergyDep);
//step->GetTrack()->SetTrackStatus(fStopAndKill);
  }
   return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}

SensitiveDetector::~SensitiveDetector()
{
}
