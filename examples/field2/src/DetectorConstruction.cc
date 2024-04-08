#include"DetectorConstruction.hh"
#include"SensitiveDetector.hh" 
#include<G4NistManager.hh>
#include<G4Box.hh>
#include<G4Tubs.hh>
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include<G4VisAttributes.hh>
#include "G4SystemOfUnits.hh"

#include <G4GlobalMagFieldMessenger.hh>
#include "G4AutoDelete.hh"

#include "FieldSetup.hh"
#include "KonField.hh"

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4MagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4ChordFinder.hh"
#include "G4ClassicalRK4.hh"

#include "G4UserLimits.hh"

using namespace std;

#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x))


World::World(double size_x, double size_y, double size_z,  G4Material *mater_): mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{
	solid = new G4Box("world", sizex/2, sizey/2, sizez/2);
	logic = new G4LogicalVolume( solid, mater, "World", 0, 0, 0);
	physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World",
				   0, false, 0);             
}

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
//------------Elements--------------------
 G4double density, a, z, fractionmass;
 G4int ncomponents;
 G4String name, symbol;

 //Hydrogen
 a = 1.008*g/mole;
 G4Element* elH  = new G4Element(name="Hydrogen",symbol="H" , z= 1., a);
 //Carbon
 a = 12.01*g/mole;
 G4Element* elC  = new G4Element(name="Carbon",symbol="C" , z= 6., a);

//-----------Materials--------------------

 //PLASTIC
 density = 1.032*g/cm3;
 G4Material* Mat1 = new G4Material(name="Plastic",density,ncomponents=2);
 Mat1->AddElement(elH, fractionmass=7.74*perCent);
 Mat1->AddElement(elC, fractionmass=92.26*perCent);

//-----------Volumes----------------------

//  world = new World(40*cm, 50*cm, 60*cm, Mat("G4_Galactic"));
  
// World
  G4Box* solidWorld =  new G4Box("World", 30*cm, 30*cm, 30*cm);    
  G4LogicalVolume* logicWorld =  new G4LogicalVolume(solidWorld, Mat("G4_AIR") , "World");  
  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld,  "World", 0, false, 0);    


// SSD
  G4Box *solidSSD = new G4Box("solidSSD", 15.0*cm, 15.0*cm, 15.0*cm);
  G4LogicalVolume *logicSSD = new G4LogicalVolume(solidSSD, Mat("G4_Galactic"), "logicSSD");
  G4PVPlacement *physSSD = new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), logicSSD,
					      "physSSD", logicWorld, false, 0);
//  G4PVPlacement *physSSD = new G4PVPlacement(0, G4ThreeVector(0,0,0*cm), logicSSD,
//					      "physSSD", world->getLogic(), false, 0); 


// Magnetic field creation
//--------------------------------------

//Way#1

// Create global magnetic field messenger.
// Uniform magnetic field is then created automatically if
// the field value is not zero.

//   G4ThreeVector fieldValue = G4ThreeVector(3*tesla,0,0);
//   G4GlobalMagFieldMessenger *fMagFieldMessenger = new  G4GlobalMagFieldMessenger(fieldValue);
//   fMagFieldMessenger->SetVerboseLevel(1); 
//   G4AutoDelete::Register(fMagFieldMessenger);  // Register the field messenger for deleting

//Way#2

// Uniform global magnetic field is created  using G4FieldManager

/*
   G4UniformMagField  *fMagneticField = new G4UniformMagField(G4ThreeVector(3.0*tesla, 0.0, 0.0));
 
   G4FieldManager * globalFieldManager;
   G4TransportationManager *transportMgr = G4TransportationManager::GetTransportationManager();
   globalFieldManager = transportMgr->GetFieldManager();
// Relative accuracy values:
   G4double minEps= 1.0e-8;  //   Minimum error value for smallest steps
   G4double maxEps= 1.0e-7;  //   Maximum error value for largest steps
   globalFieldManager->SetMinimumEpsilonStep( minEps );
   globalFieldManager->SetMaximumEpsilonStep( maxEps );
   globalFieldManager->SetDeltaOneStep( 0.5e-3 * mm );  

   G4Mag_UsualEqRhs *fEquation = new G4Mag_UsualEqRhs(fMagneticField);
   G4MagIntegratorStepper* fStepper = new G4ClassicalRK4( fEquation );

   G4double fMinStep = 0.25*mm ; // minimal step of 1 mm is default
   G4ChordFinder *fChordFinder = new G4ChordFinder(fMagneticField, fMinStep, fStepper);

   globalFieldManager->SetChordFinder(fChordFinder);
   globalFieldManager->SetDetectorField(fMagneticField);
*/

//Way#3

// Non-uniform global magnetic field is created  using G4FieldManager and myField

   KonField*  myField = new KonField;
 
   G4FieldManager * globalFieldManager;
   G4TransportationManager *transportMgr = G4TransportationManager::GetTransportationManager();
   globalFieldManager = transportMgr->GetFieldManager();
// Relative accuracy values:
   G4double minEps= 1.0e-8;  //   Minimum error value for smallest steps
   G4double maxEps= 1.0e-7;  //   Maximum error value for largest steps
   globalFieldManager->SetMinimumEpsilonStep( minEps );
   globalFieldManager->SetMaximumEpsilonStep( maxEps );
   globalFieldManager->SetDeltaOneStep( 0.5e-3 * mm );  

   G4Mag_UsualEqRhs *fEquation = new G4Mag_UsualEqRhs(myField);
   G4MagIntegratorStepper* fStepper = new G4ClassicalRK4( fEquation );

   G4double fMinStep = 0.25*mm ; // minimal step of 1 mm is default
   G4ChordFinder *fChordFinder = new G4ChordFinder(myField, fMinStep, fStepper);

   globalFieldManager->SetChordFinder(fChordFinder);
   globalFieldManager->SetDetectorField(myField);



//Way#4
//-----------------------------------------------------------------------
// Uniform global and local magnetic fields are created  using class FieldSetup()

//   FieldSetup* fieldSetup = new FieldSetup();
//   G4AutoDelete::Register(fieldSetup);

// Set local field manager and local field in detector and its daughters:
//   G4bool allLocal = true;
//   logicSSD->SetFieldManager(fieldSetup->GetLocalFieldManager(), allLocal );
//---------------------------------------------------------------------------

// Define maximum step for tracking in magnetic field using G4UserLimits 
// and G4StepLimiterPhysics (see field2.cc)

   G4double maxStep = 1*mm;
   G4double maxLength = 1*mm;
   G4UserLimits* fStepLimit = new G4UserLimits();
   fStepLimit->SetMaxAllowedStep(maxStep);
   logicSSD->SetUserLimits(fStepLimit);
   logicWorld->SetUserLimits(fStepLimit);

//Define sensitive detectors

  SensitiveDetector *detector = new SensitiveDetector("hit there");
  
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  SDman->AddNewDetector(detector);
  logicSSD->SetSensitiveDetector(detector);
  logicWorld->SetVisAttributes (G4VisAttributes::GetInvisible());

  return physWorld;
}
