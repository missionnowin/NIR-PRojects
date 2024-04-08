//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "PrimaryGeneratorAction.hh"
#include "PrimaryGeneratorAction1.hh"
#include "PrimaryGeneratorMessenger.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(0),
   fAction1(0),
   fSelectedAction(2),
   fGunMessenger(0)     
{
  // default particle kinematic
  //
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
    
  G4ParticleDefinition* particle
           = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(1000*MeV);        
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -24.*cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1)); 
  
  fAction1 = new PrimaryGeneratorAction1(fParticleGun);
 
  //create a messenger for this class
  fGunMessenger = new PrimaryGeneratorMessenger(this);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fAction1;
  delete fParticleGun;  
  delete fGunMessenger; 
  delete fParticleGun;     
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  switch(fSelectedAction)
  {
   case 1:
    fAction1->GeneratePrimaries(anEvent);
    break;
   case 2:
    fParticleGun->GeneratePrimaryVertex(anEvent);
    break;    
   default:
    G4cerr << "Invalid generator fAction" << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
