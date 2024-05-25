

#include "PrimaryGeneratorAction.hh"

#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "HepMCG4AsciiReader.hh"

using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
: G4VUserPrimaryGeneratorAction(),
  fEnvelopeBox(0)
{
  fCurrentGenerator = fParticleGun = new G4ParticleGun();
  fCurrentGeneratorName = "particleGun";
  fHepmcAscii = new HepMCG4AsciiReader();

  fGentypeMap["particleGun"] = fParticleGun;
  fGentypeMap["hepmcAscii"] = fHepmcAscii;
  fMessenger = new PrimaryGeneratorMessenger(this);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    if (fCurrentGenerator)
        fCurrentGenerator->GeneratePrimaryVertex(anEvent);
    else
        G4Exception("H02PrimaryGeneratorAction::GeneratePrimaries",
            "InvalidSetup", FatalException,
            "Generator is not instanciated.");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

