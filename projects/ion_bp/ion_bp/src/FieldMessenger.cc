#include "FieldMessenger.hh"
#include "FieldSetup.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4SystemOfUnits.hh"
 
 FieldMessenger::FieldMessenger(FieldSetup* fieldSetup)
  : G4UImessenger(),
    fEMfieldSetup(fieldSetup),
    fFieldDir(0),
    fStepperCmd(0),
    fMagFieldCmd(0),
    fMinStepCmd(0)
 {
   fFieldDir = new G4UIdirectory("/field/");
   fFieldDir->SetGuidance("Field tracking control.");
 
   fStepperCmd = new G4UIcmdWithAnInteger("/field/setStepperType",this);
   fStepperCmd->SetGuidance("Select stepper type for magnetic field");
   fStepperCmd->SetParameterName("choice",true);
   fStepperCmd->SetDefaultValue(4);
   fStepperCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 
   fMagFieldCmd = new G4UIcmdWithADoubleAndUnit("/field/setFieldX",this);
   fMagFieldCmd->SetGuidance("Define magnetic field.");
   fMagFieldCmd->SetGuidance("Magnetic field will be in X direction.");
   fMagFieldCmd->SetParameterName("Bx",false,false);
   fMagFieldCmd->SetDefaultUnit("tesla");
   fMagFieldCmd->AvailableForStates(G4State_Idle);
  
   fMinStepCmd = new G4UIcmdWithADoubleAndUnit("/field/setMinStep",this);
   fMinStepCmd->SetGuidance("Define minimal step");
   fMinStepCmd->SetGuidance("Magnetic field will be in X direction.");
   fMinStepCmd->SetParameterName("min step",false,false);
   fMinStepCmd->SetDefaultUnit("mm");
   fMinStepCmd->AvailableForStates(G4State_Idle);
 }
 
  FieldMessenger::~FieldMessenger()
 {
   delete fStepperCmd;
   delete fMagFieldCmd;
   delete fMinStepCmd;
   delete fFieldDir;
 }
 
 void FieldMessenger::SetNewValue( G4UIcommand* command, G4String newValue)
 {
   if( command == fStepperCmd )
     fEMfieldSetup->SetStepperType(fStepperCmd->GetNewIntValue(newValue));
   if( command == fMagFieldCmd )
     fEMfieldSetup->SetFieldValue(fMagFieldCmd->GetNewDoubleValue(newValue));
    G4cout << "Set field value to " <<
      fEMfieldSetup->GetConstantFieldValue() / gauss << " Gauss " << G4endl;
   if( command == fMinStepCmd )
     fEMfieldSetup->SetMinStep(fMinStepCmd->GetNewDoubleValue(newValue));
 }
 
