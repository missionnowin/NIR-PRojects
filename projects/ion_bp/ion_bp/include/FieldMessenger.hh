#ifndef FieldMessenger_h
#define FieldMessenger_h 1
 
#include "G4UImessenger.hh"
 
 class FieldSetup;
 class G4UIdirectory;
 class G4UIcmdWithAnInteger;
 class G4UIcmdWithADoubleAndUnit;
 class G4UIcmdWithoutParameter;
 
 class FieldMessenger: public G4UImessenger
 {
   public:
     FieldMessenger(FieldSetup* );
     virtual ~FieldMessenger();
  
     virtual void SetNewValue(G4UIcommand*, G4String);
  
   private:
 
     FieldSetup*                fEMfieldSetup;
 
     G4UIdirectory*             fFieldDir;
 
     G4UIcmdWithAnInteger*      fStepperCmd;
     G4UIcmdWithADoubleAndUnit* fMagFieldCmd;
     G4UIcmdWithADoubleAndUnit* fMinStepCmd;
 };
 
 #endif

