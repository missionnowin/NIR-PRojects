#include"DetectorConstruction.hh"
#include"SensitiveDetector.hh" 
#include<G4Box.hh>
#include<G4Tubs.hh>
#include<G4LogicalVolume.hh>
#include<G4PVPlacement.hh>
#include<G4SDManager.hh>
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include <G4UserLimits.hh>
#include <G4ProductionCuts.hh>
#include <G4MaterialCutsCouple.hh>

using namespace std;

#define Mat(x) (G4NistManager::Instance()->FindOrBuildMaterial(x))


World::World(double size_x, double size_y, double size_z,  G4Material *mater_): mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{
	//double size05 = size/2;
	solid = new G4Box("world", sizex/2, sizey/2, sizez/2);
	logic = new G4LogicalVolume( solid, mater, "World", 0, 0, 0);
	physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World", 0 , false, 0);             
}

DetectorConstruction::DetectorConstruction()
{
}

DetectorConstruction::~DetectorConstruction()
{
}


G4VPhysicalVolume* DetectorConstruction::Construct()
{

    G4NistManager* nist = G4NistManager::Instance();

    //Worls
    world = new World(350*um, 350*um, 350*um, Mat("G4_Galactic"));
    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateX(-8*degree);

  
    //Elements
    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* Pb = nist->FindOrBuildElement("Pb");
    G4Element* O = nist->FindOrBuildElement("O");

    //Material
    G4double density = 5.8*g/cm3;
    G4Material* SiO2PbO = new G4Material("SiO2PbO", density, 3);
    SiO2PbO -> AddElement(Si,0.23);
    SiO2PbO -> AddElement(Pb, 0.15);
    SiO2PbO -> AddElement(O, 0.62);

    //Box
    G4Box *solidTgt = new G4Box("solidTgt", 100*um, 100*um, 100*um);
    G4LogicalVolume *logiclTgt = new G4LogicalVolume(solidTgt, SiO2PbO, "logiclTgt");
    G4PVPlacement *physilTgt = new G4PVPlacement(rotation, G4ThreeVector(0,0,0*cm), logiclTgt, "physilTgt", world->getLogic(), false, 0);
    G4UserLimits* electronLimits = new G4UserLimits();
    electronLimits->SetUserMinEkine(10. * CLHEP::keV); // Set minimum kinetic energy for electrons
    logiclTgt->SetUserLimits(electronLimits);
    G4VisAttributes* orange = new G4VisAttributes(G4Colour(1.0,0.5,0.0));

    
    //Detector
    SensitiveDetector* detector = new SensitiveDetector("SD");
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(detector);

    orange -> SetForceWireframe(true);
    logiclTgt -> SetVisAttributes(orange);
    int count = 0;

    for (G4int i=-84; i<90; i=i+12)
     {
      for (G4int j=-84, k=-7*2; j<90; j=j+12, k=k+2)
       {
        string nameLogic = "logiclCyl";
        string namePhysics = "physicsCyl";
        string nameSolid = "solidCyl";
        nameLogic.append(to_string(count));
        namePhysics.append(to_string(count));
        nameSolid.append(to_string(count));
        G4Tubs *solidCyl = new G4Tubs(nameSolid, 0, 5*um, 100*um, 0, 2*3.1416);
        G4LogicalVolume *logiclCyl = new G4LogicalVolume(solidCyl, Mat("G4_AIR"), nameLogic);
        G4PVPlacement *physilCyl = new G4PVPlacement(rotation, G4ThreeVector(i*um,j*um,k*um), logiclCyl, namePhysics, world->getLogic(), false, 0);
        G4VisAttributes* purpur = new G4VisAttributes(G4Colour(0.6,0.4,0.8));
        logiclCyl -> SetVisAttributes(purpur);
        count++;
      }
    }

/*    //Detector
      G4Box *solidDet = new G4Box("solidDet", 500*um, 500*um, 100*um);
      G4LogicalVolume *logicDet = new G4LogicalVolume(solidDet, Mat("G4_Si"), "logicDet");
      G4PVPlacement *physiDet = new G4PVPlacement(0, G4ThreeVector(0,0,1.25*mm), logicDet,
                                              "physiDet", world->getLogic(), false, 0);

      SensitiveDetector *detector = new SensitiveDetector("hit there");
  
      G4SDManager* SDman = G4SDManager::GetSDMpointer();
      SDman->AddNewDetector(detector);
      logicDet->SetSensitiveDetector(detector);
    */  
  
        
    SetSensitiveDetector(logiclTgt, detector);
      world->getLogic()->SetVisAttributes (G4VisAttributes::GetInvisible());
      return world->getPhysic();
}
