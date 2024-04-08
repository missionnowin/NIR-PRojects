
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo...... 

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class PrimaryGeneratorAction1;
class PrimaryGeneratorMessenger;

class G4ParticleGun;
class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
   ~PrimaryGeneratorAction();

  public:
    virtual void GeneratePrimaries(G4Event*);

  public:
   G4ParticleGun* GetParticleGun() const{ return fParticleGun; };
    
    void SelectAction(G4int i) { fSelectedAction = i; };    
    G4int GetSelectedAction()  { return fSelectedAction; };    
    PrimaryGeneratorAction1*  GetAction1() { return fAction1; };
     
  private:
    G4ParticleGun*           fParticleGun;
    PrimaryGeneratorAction1* fAction1;
    G4int                    fSelectedAction;
        
    PrimaryGeneratorMessenger* fGunMessenger;     
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
