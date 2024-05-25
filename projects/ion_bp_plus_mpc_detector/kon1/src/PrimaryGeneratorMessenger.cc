#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIparameter.hh"
#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorMessenger::PrimaryGeneratorMessenger
(PrimaryGeneratorAction* genaction)
    : G4UImessenger(),
    fPrimaryAction(genaction)
{
    fDir = new G4UIdirectory("/generator/");
    fDir->SetGuidance("Control commands for primary generator");

    //verbose= new G4UIcmdWithAnInteger("/generator/verbose", this);
    //verbose-> SetGuidance("set verbose level (0,1,2)");
    //verbose-> SetParameterName("verbose", false, false);
    //verbose-> SetDefaultValue(0);
    //verbose-> SetRange("verbose>=0 && verbose<=2");

    fSelect = new G4UIcmdWithAString("/generator/select", this);
    fSelect->SetGuidance("fSelect generator type");
    fSelect->SetParameterName("generator_type", false, false);
    fSelect->SetCandidates("particleGun pythia hepmcAscii");
    fSelect->SetDefaultValue("particleGun");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
    //delete verbose;
    delete fSelect;

    delete fDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,
    G4String newValues)
{
    if (command == fSelect) {
        fPrimaryAction->SetGenerator(newValues);
        G4cout << "current generator type: "
            << fPrimaryAction->GetGeneratorName() << G4endl;
    }
    else {
    }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4String PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand* command)
{
    G4String cv, st;
    if (command == fSelect) {
        cv = fPrimaryAction->GetGeneratorName();
    }

    return cv;
}
