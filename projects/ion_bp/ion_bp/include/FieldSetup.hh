#ifndef FieldSetup_h
#define FieldSetup_h 1

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"

class G4FieldManager;
class G4ChordFinder;
class G4Mag_UsualEqRhs;
class G4MagIntegratorStepper;
class FieldMessenger;

///  A class for setting up the Magnetic Field
///  It also creates the necessary classes to control accuracy of propagation.
///  In this example:
///  There is a global field for most of the setup;
///  A local field overides it for some volume(s) and it assumed to be uniform.

class FieldSetup
{
public:
  FieldSetup();           //  A zero field
  virtual ~FieldSetup();

  void SetStepperType( G4int i ) { fStepperType = i; }

  void SetStepper();

  void SetMinStep(G4double s) { fMinStep = s; }

  void SetFieldValue(G4ThreeVector fieldVector);
  void SetFieldValue(G4double      fieldValue);
  G4ThreeVector GetConstantFieldValue();

  void UpdateField();

  G4FieldManager* GetLocalFieldManager() { return fLocalFieldManager;}

protected:

  // Find the global Field Manager

  G4FieldManager*         GetGlobalFieldManager() ;

  G4FieldManager*         fFieldManager;
  G4FieldManager*         fLocalFieldManager;
  G4ChordFinder*          fChordFinder;
  G4ChordFinder*          fLocalChordFinder;
  G4Mag_UsualEqRhs*       fEquation;
  G4Mag_UsualEqRhs*       fLocalEquation;
  G4MagneticField*        fMagneticField;
  G4MagneticField*        fLocalMagneticField;

  G4MagIntegratorStepper* fStepper;
  G4MagIntegratorStepper* fLocalStepper;
  G4int                   fStepperType;

  G4double                fMinStep;
 
  FieldMessenger*         fFieldMessenger;

};

#endif

