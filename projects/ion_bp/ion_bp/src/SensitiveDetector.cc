#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include"SensitiveDetector.hh"
#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"
#include "HistoManager.hh"
#include "EventAction.hh"
#include "G4EventManager.hh"
#include <G4AnalysisManager.hh>

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name)
{
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory*)
{
  double energy_dep = step->GetTotalEnergyDeposit();
  G4String volume_sens = step->GetTrack()->GetVolume()->GetName();
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4int particle_code = step->GetTrack()->GetDynamicParticle()->GetPDGcode();

  if(particle_code == 2212) {
//  G4cout<< "Energy of proton deposited in sensitive volume " << volume_sens << " :" << G4BestUnit(energy_dep,"Energy") << G4endl;
  }
 
// Accumulate energy deposit in given modules

  if(volume_sens=="physBp1") edep_det[1] += energy_dep;  
//  if(volume_mother=="physDet2") edep_mod[2] += energy_dep;
//  if(volume_mother=="physDet3") edep_mod[3] += energy_dep;

//  edep_sum += energy_dep;  
  return true;
}

void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
//  edep_sum /= 1000. ; // Express energy in GeV
//  G4cout << " Total energy deposited in beam pipe: " << G4BestUnit(edep_det[1],"Energy") << G4endl; 
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  for(int i = 1; i<3; i++) analysisManager->FillH1(i,edep_det[i]*1000);   

// Pass the the energy deposit in sensitive volumes for this event to the method of the event 
// aciton to fill histograms 
  EventAction* myAction = (EventAction*)(G4EventManager::GetEventManager()->GetUserEventAction()); 
  if(myAction) myAction->GetEdep(edep_det[1]); 

// Clear the values   
   edep_sum = 0.;
   for(int i = 0; i<n_det; i++) edep_det[i]=0;

}

SensitiveDetector::~SensitiveDetector()
{
  std::ofstream file("spectrum.dat");
  for(int i = 0; i<n_det; i++) 
  {
   file << " Module: " << std::setw(10) << i << " E deposit: " << std::setw(10) << edep_det[i] << std::endl;
  }
}
