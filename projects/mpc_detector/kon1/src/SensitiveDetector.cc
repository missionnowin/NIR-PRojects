#include<G4Step.hh>
#include<fstream>
#include<iostream>
#include"SensitiveDetector.hh"
#include <G4SystemOfUnits.hh>
#include "G4UnitsTable.hh"

using namespace std;

SensitiveDetector::SensitiveDetector(G4String name): G4VSensitiveDetector(name),
                                                        HIST_MAX(-100 * um),
                                                        HIST_MIN(100 * um)
{
  for(int i = 0; i<NOBINS; i++)
    histogram[i] = 0;
}

G4bool SensitiveDetector::ProcessHits(G4Step *step, G4TouchableHistory *hist)
{
      double energy_tot = step->GetTrack()->GetDynamicParticle()->GetTotalEnergy();
      double energy_kin = step->GetPreStepPoint()->GetPosition().z();
      double energy_dep = step->GetTotalEnergyDeposit();
      G4String volume_sens = step->GetTrack()->GetVolume()->GetName();
      G4int particle_code = step->GetTrack()->GetDynamicParticle()->GetPDGcode();
      if(volume_sens && particle_code == 11) {
          //G4cout << "Coordinate of electron = " << G4BestUnit(energy_kin, "Energy") << " in sensitive volume: " << volume_sens << G4endl;
          double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
          int index = int(floor((energy_kin - HIST_MIN)/bin_width));
          if (index >= 0 && index < NOBINS) {
              histogram[index]++;
          }
         step->GetTrack()->SetTrackStatus(fStopAndKill);
      }
  return true;
}


void SensitiveDetector::EndOfEvent(G4HCofThisEvent*)
{
}



SensitiveDetector::~SensitiveDetector()
{
  std::ofstream file("spectrum.dat");
  
  double bin_width = (HIST_MAX - HIST_MIN) / NOBINS;
  for(int i = 0; i<NOBINS; i++)
  {
    double energy = i * bin_width + HIST_MIN;
    file << std::setw(15) << energy/um << " "
	 << std::setw(15) << histogram[i] << std::endl;
  }
  file.close();
}