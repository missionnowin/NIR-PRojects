

#include "PrimaryGeneratorMessenger.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::PrimaryGeneratorMessenger(
                                             PrimaryGeneratorAction* Gun)
:G4UImessenger(),
 Action(Gun),
 fDir(0),       
 fSelectActionCmd(0)
{
  fDir = new G4UIdirectory("/gunExample/");
  fDir->SetGuidance("this example");
    
  fSelectActionCmd = new G4UIcmdWithAnInteger("/gunExample/selectGunAction",this);
  fSelectActionCmd->SetGuidance("Select primary generator action");
  fSelectActionCmd->SetGuidance("id=1 Generate several vertices and particles per event");
  fSelectActionCmd->SetGuidance("id=2 Show how to sample a tabulated function");  
  fSelectActionCmd->SetGuidance("id=3 Divergent beam in an arbitrary direction");
  fSelectActionCmd->SetGuidance("id=4 In spherical coordinates with rotation matrix");
  fSelectActionCmd->SetParameterName("id",false);
  fSelectActionCmd->SetRange("id>0 && id<5");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorMessenger::~PrimaryGeneratorMessenger()
{
  delete fSelectActionCmd;
  delete fDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorMessenger::SetNewValue(G4UIcommand* command,
                                               G4String newValue)
{ 
  if (command == fSelectActionCmd)
    Action->SelectAction(fSelectActionCmd->GetNewIntValue(newValue));      
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

