
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#include "PrimaryGeneratorAction1.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction1::PrimaryGeneratorAction1(G4ParticleGun* gun)
: fParticleGun(gun)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction1::~PrimaryGeneratorAction1()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction1::GeneratePrimaries(G4Event* anEvent)
{
  const G4double xmax = 2*mm;
  const G4double ymax = 2*mm;   
  const G4double xmax1 = 0.5;
  const G4double ymax1 = 0.5; 
  
  //vertex 1 uniform on plane
  //
 
  G4double x = xmax*(2*G4UniformRand() - 1);  //x uniform in (-xmax, +xmax)
  G4double y = ymax*(2*G4UniformRand() - 1);  //y uniform in (-ymax, +ymax)
  G4double x1 = xmax1*(2*G4UniformRand() - 1);  //x uniform in (-xmax, +xmax)
  G4double y1 = ymax1*(2*G4UniformRand() - 1);  //y uniform in (-ymax, +ymax)

//  G4double x1 = G4UniformRand()/10.;  
//  G4double y1 = G4UniformRand()/10.;  
        
  fParticleGun->SetParticlePosition(G4ThreeVector(0.,0.,-13*cm));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.5,0.5,1));  
//  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x1,y1,1));   
  fParticleGun->SetParticleEnergy(3500*MeV);
  fParticleGun->GeneratePrimaryVertex(anEvent);
  
//   fParticleGun->GeneratePrimaryVertex(anEvent);    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
