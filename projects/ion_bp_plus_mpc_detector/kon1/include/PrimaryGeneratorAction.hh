

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"
#include <PrimaryGeneratorMessenger.hh>

class G4ParticleGun;
class G4Event;
class G4Box;
class G4Event;
class G4VPrimaryGenerator;

/// The primary generator action class with particle gun.
///
/// The default kinematic is a 6 MeV gamma, randomly distribued 
/// in front of the phantom across 80% of the (X,Y) phantom size.

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:
    PrimaryGeneratorAction();    
    ~PrimaryGeneratorAction();

    // method from the base class
    virtual void GeneratePrimaries(G4Event* anEvent);

    void SetGenerator(G4VPrimaryGenerator* gen);
    void SetGenerator(G4String genname);
    G4VPrimaryGenerator* GetGenerator() const;
    G4String GetGeneratorName() const;
  
    // method to access particle gun
    const G4ParticleGun* GetParticleGun() const { return fParticleGun; }
  
  private:
    G4ParticleGun*  fParticleGun; // pointer a to G4 gun class
    G4VPrimaryGenerator* fHepmcAscii;
    G4Box* fEnvelopeBox;
    G4VPrimaryGenerator* fCurrentGenerator;
    G4String fCurrentGeneratorName;
    std::map<G4String, G4VPrimaryGenerator*> fGentypeMap;

    PrimaryGeneratorMessenger* fMessenger;
};

inline void PrimaryGeneratorAction::SetGenerator(G4VPrimaryGenerator* gen)
{
    fCurrentGenerator = gen;
}

inline void PrimaryGeneratorAction::SetGenerator(G4String genname)
{
    std::map<G4String, G4VPrimaryGenerator*>::iterator
        pos = fGentypeMap.find(genname);
    if (pos != fGentypeMap.end()) {
        fCurrentGenerator = pos->second;
        fCurrentGeneratorName = genname;
    }
}

inline G4VPrimaryGenerator* PrimaryGeneratorAction::GetGenerator() const
{
    return fCurrentGenerator;
}

inline G4String PrimaryGeneratorAction::GetGeneratorName() const
{
    return fCurrentGeneratorName;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


