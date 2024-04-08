#include "FieldSetup.hh"
#include "FieldMessenger.hh"

#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"

#include "G4ExplicitEuler.hh"
#include "G4ImplicitEuler.hh"
#include "G4SimpleRunge.hh"
#include "G4SimpleHeum.hh"
#include "G4ClassicalRK4.hh"
#include "G4HelixExplicitEuler.hh"
#include "G4HelixImplicitEuler.hh"
#include "G4HelixSimpleRunge.hh"
#include "G4CashKarpRKF45.hh"
#include "G4RKG3_Stepper.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

   FieldSetup::FieldSetup()
 : fFieldManager(0),
   fLocalFieldManager(0),
   fChordFinder(0),
   fLocalChordFinder(0),
   fEquation(0),
   fLocalEquation(0),
   fMagneticField(0),
   fLocalMagneticField(0),
   fStepper(0),
   fLocalStepper(0),
   fFieldMessenger(0)
{
  fMagneticField = new G4UniformMagField(G4ThreeVector(0.0*tesla, 0.0, 0.0));
  fLocalMagneticField = new G4UniformMagField(G4ThreeVector(3.0*tesla, 0.0, 0.0));

  fFieldMessenger = new FieldMessenger(this);
 
  fEquation = new G4Mag_UsualEqRhs(fMagneticField);
  fLocalEquation = new G4Mag_UsualEqRhs(fLocalMagneticField);
 
  fMinStep     = 0.25*mm ; // minimal step of 1 mm is default
  fStepperType = 4 ;       // ClassicalRK4 is default stepper

  fFieldManager = GetGlobalFieldManager();
  fLocalFieldManager = new G4FieldManager();

  UpdateField();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

  FieldSetup::~FieldSetup()
{
  delete fMagneticField;
  delete fChordFinder;
  delete fStepper;
  delete fFieldMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FieldSetup::UpdateField()
{
  SetStepper();
  G4cout<<"The minimal step is equal to "<<fMinStep/mm<<" mm"<<G4endl;

  fFieldManager->SetDetectorField(fMagneticField);
  fLocalFieldManager->SetDetectorField(fLocalMagneticField);

  if (fChordFinder) delete fChordFinder;
  if (fLocalChordFinder) delete fLocalChordFinder;

  fChordFinder = new G4ChordFinder(fMagneticField, fMinStep, fStepper);
  fLocalChordFinder = new G4ChordFinder(fLocalMagneticField, fMinStep, fLocalStepper);

  fFieldManager->SetChordFinder(fChordFinder);
  fLocalFieldManager->SetChordFinder(fLocalChordFinder);
  G4double minEps= 1.0e-5;  //   Minimum error value for smallest steps
  G4double maxEps= 1.0e-4;  //   Maximum error value for largest steps
  fFieldManager->SetMinimumEpsilonStep( minEps );
  fFieldManager->SetMaximumEpsilonStep( maxEps );
  fFieldManager->SetDeltaOneStep( 0.5e-3 * mm );  // 0.5 um

}

void FieldSetup::SetStepper()
{
  if (fStepper) delete fStepper;

  switch ( fStepperType )
  {
    case 0:
      fStepper = new G4ExplicitEuler( fEquation );
      fLocalStepper = new G4ExplicitEuler( fLocalEquation );
      G4cout<<"G4ExplicitEuler is called"<<G4endl;
      break;
    case 1:
      fStepper = new G4ImplicitEuler( fEquation );
      fLocalStepper = new G4ImplicitEuler( fLocalEquation );
      G4cout<<"G4ImplicitEuler is called"<<G4endl;
      break;
    case 2:
      fStepper = new G4SimpleRunge( fEquation );
      fLocalStepper = new G4SimpleRunge( fLocalEquation );
      G4cout<<"G4SimpleRunge is called"<<G4endl;
      break;
    case 3:
      fStepper = new G4SimpleHeum( fEquation );
      fLocalStepper = new G4SimpleHeum( fLocalEquation );
      G4cout<<"G4SimpleHeum is called"<<G4endl;
      break;
    case 4:
      fStepper = new G4ClassicalRK4( fEquation );
      fLocalStepper = new G4ClassicalRK4( fLocalEquation );
      G4cout<<"G4ClassicalRK4 (default) is called"<<G4endl;
      break;
    case 5:
      fStepper = new G4HelixExplicitEuler( fEquation );
      fLocalStepper = new G4HelixExplicitEuler( fLocalEquation );
      G4cout<<"G4HelixExplicitEuler is called"<<G4endl;
      break;
    case 6:
      fStepper = new G4HelixImplicitEuler( fEquation );
      fLocalStepper = new G4HelixImplicitEuler( fLocalEquation );
      G4cout<<"G4HelixImplicitEuler is called"<<G4endl;
      break;
    case 7:
      fStepper = new G4HelixSimpleRunge( fEquation );
      fLocalStepper = new G4HelixSimpleRunge( fLocalEquation );
      G4cout<<"G4HelixSimpleRunge is called"<<G4endl;
      break;
    case 8:
      fStepper = new G4CashKarpRKF45( fEquation );
      fLocalStepper = new G4CashKarpRKF45( fLocalEquation );
      G4cout<<"G4CashKarpRKF45 is called"<<G4endl;
      break;
    case 9:
      fStepper = new G4RKG3_Stepper( fEquation );
      fLocalStepper = new G4RKG3_Stepper( fLocalEquation );
      G4cout<<"G4RKG3_Stepper is called"<<G4endl;
      break;
    default: fStepper = 0;
  }
}

 void FieldSetup::SetFieldValue(G4double fieldStrength)
{
  G4ThreeVector fieldSetVec( fieldStrength, 0.0, 0.0);
  SetFieldValue( fieldSetVec );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

 void FieldSetup::SetFieldValue(G4ThreeVector fieldVector)
{
  if(fMagneticField) delete fMagneticField;

  if(fieldVector != G4ThreeVector(0.,0.,0.))
  {
    fMagneticField = new  G4UniformMagField(fieldVector);
  }
  else
  {
    // If the new field's value is Zero, then
    // setting the pointer to zero ensures
    // that it is not used for propagation.
    fMagneticField = 0;
  }

  // Either
  //   - UpdateField() to reset all (ChordFinder, Equation);
  // UpdateField();
  //     or simply update the field manager & equation of motion
  //     with pointer to new field

  GetGlobalFieldManager()->SetDetectorField(fMagneticField);
//  fLocalFieldManager->SetDetectorField(fMagneticField);
  fEquation->SetFieldObj(fMagneticField);
//  fLocalEquation->SetFieldObj(fMagneticField);
}

 G4FieldManager* FieldSetup::GetGlobalFieldManager()
{
  return G4TransportationManager::GetTransportationManager()
                                  ->GetFieldManager();
}

 G4ThreeVector FieldSetup::GetConstantFieldValue()
{
  static G4double fieldValue[6],  position[4];
  position[0] = position[1] = position[2] = position[3] = 0.0;

  fMagneticField->GetFieldValue( position, fieldValue);
  G4ThreeVector fieldVec(fieldValue[0], fieldValue[1], fieldValue[2]);

  return fieldVec;
}

