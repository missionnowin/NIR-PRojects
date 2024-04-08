#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingVerbose.hh"

#include<G4RunManager.hh>
#include<G4UImanager.hh>
#include "QBBC.hh"
#include<G4UIterminal.hh>
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include<G4Material.hh>
#include<G4UserRunAction.hh>
#include<G4Run.hh>
#include<iostream>
#include<string>
#include<CLHEP/Random/Random.h>
#include<io.h>
#include<time.h>
#include<G4EmLivermorePhysics.hh>
#include<G4EmDNAPhysics.hh>
//#include "G4ErrorPropagatorManager.hh"
#include "G4StepLimiterPhysics.hh"

using namespace std;

int main(int argc, char** argv)
{

//***** Choose the Seed engine
	G4UIExecutive* ui = nullptr;
	if (argc == 1) { ui = new G4UIExecutive(argc, argv); }
	CLHEP::HepRandom::setTheSeed(time(0)+getpid());

//***** Construct the default run manager
	G4RunManager * runManager = new G4RunManager;

//***** Set mandatory initialization classes

//11111 Detector construction:
	DetectorConstruction* detector_c = new DetectorConstruction;
	runManager->SetUserInitialization(detector_c);

//22222 Physics list:
        G4VModularPhysicsList* physicsList = new QBBC;
// G4VModularPhysicsList* physicsList = new FTFP_BERT;
        physicsList->SetVerboseLevel(0);
        physicsList->RegisterPhysics(new G4StepLimiterPhysics());
//        physicsList->RegisterPhysics(new G4EmLivermorePhysics); 
//        physicsList->RegisterPhysics(new G4EmDNAPhysics);
        runManager->SetUserInitialization(physicsList);

// G4VModularPhysicsList* physicsList = new FTFP_BERT;


  
//33333 Initialize visualization:
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
   
//44444 User action initialization
       runManager->SetUserInitialization(new ActionInitialization());
//  PrimaryGeneratorAction* prim  = new PrimaryGeneratorAction();
//  runManager->SetUserAction(prim); 

//55555 Initialize G4 kernel:
	runManager->Initialize();

//  G4ErrorPropagatorManager* PropMan = new G4ErrorPropagatorManager();
//  PropMan-> InitGeant4e();



//***** Get the pointer to the User Interface manager: 
	G4UImanager * UI = G4UImanager::GetUIpointer();

//***** Execute macros file:
//        UI->ApplyCommand("/control/execute /home/vpkondratev/geant4/kon3/vis.mac"); 
    UI->ApplyCommand("/control/execute vis1.mac");
	ui->SessionStart();

//***** Job termination
	delete ui;
	delete visManager;
	delete runManager;

	return 0;
}
