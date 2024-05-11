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


World::World(double size_x, double size_y, double size_z, G4Material* mater_) : mater(mater_), sizex(size_x), sizey(size_y), sizez(size_z)
{
    //double size05 = size/2;
    solid = new G4Box("world", sizex / 2, sizey / 2, sizez / 2);
    logic = new G4LogicalVolume(solid, mater, "World", 0, 0, 0);
    physic = new G4PVPlacement(0, G4ThreeVector(), logic, "World", 0, false, 0);
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
    world = new World(400 * cm, 400 * cm, 400 * cm, Mat("G4_AIR"));
    G4RotationMatrix* rotation = new G4RotationMatrix();
    rotation->rotateX(-0 * degree);


    //Elements
    G4Element* Si = nist->FindOrBuildElement("Si");
    G4Element* Al = nist->FindOrBuildElement("Al");
    G4Element* Ca = nist->FindOrBuildElement("Ca");
    G4Element* Na = nist->FindOrBuildElement("Na");
    G4Element* K = nist->FindOrBuildElement("K");
    G4Element* Fe = nist->FindOrBuildElement("Fe");
    G4Element* Mn = nist->FindOrBuildElement("Mn");
    G4Element* Cr = nist->FindOrBuildElement("Cr");
    G4Element* Ti = nist->FindOrBuildElement("Ti");
    G4Element* O = nist->FindOrBuildElement("O");
    G4Element* H = nist->FindOrBuildElement("H");
    G4Element* Mg = nist->FindOrBuildElement("Mg");

    //Material granite
    G4double density = 2.65 * g / cm3;
    G4Material* granite = new G4Material("granite", density, 11);


    granite->AddElement(Si, 0.65);
    granite->AddElement(Al, 0.14);
    granite->AddElement(O, 0.16);
    granite->AddElement(Fe, 0.015);
    granite->AddElement(Ca, 0.0045);
    granite->AddElement(Na, 0.0025);
    granite->AddElement(K, 0.002);
    granite->AddElement(Ti, 0.015);
    granite->AddElement(Mg, 0.005);
    granite->AddElement(H, 0.005);
    granite->AddElement(Cr, 0.001);

    //Box
    G4Box* solidTgt = new G4Box("solidTgt", 400 * cm, 400 * cm, 400 * cm);
    G4LogicalVolume* logiclTgt = new G4LogicalVolume(solidTgt, Mat("G4_Galactic"), "logiclTgt");
    G4PVPlacement* physilTgt = new G4PVPlacement(rotation, G4ThreeVector(0, 0, 0 * cm), logiclTgt, "physilTgt", world->getLogic(), false, 0);
    G4VisAttributes* orange = new G4VisAttributes(G4Colour(1.0, 0.5, 0.0));

    //Granite
    G4Box* solidBox = new G4Box("solidBox", 100 * cm, 100 * cm, 100 * cm);
    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, granite, "logicBox");
    G4PVPlacement* physicsBox = new G4PVPlacement(rotation, G4ThreeVector(0, 0, 0), logicBox, "physicsBox", world->getLogic(), false, 0);

    //Detector
    SensitiveDetector* detector = new SensitiveDetector("SD");
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    SDman->AddNewDetector(detector);

    orange->SetForceWireframe(true);
    logiclTgt->SetVisAttributes(orange);
    logicBox -> SetVisAttributes(orange);

    SetSensitiveDetector(logiclTgt, detector);
    world->getLogic()->SetVisAttributes(G4VisAttributes::GetInvisible());
    return world->getPhysic();
}
