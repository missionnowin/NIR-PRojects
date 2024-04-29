#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingVerbose.hh"
#include "MyPhysicsList.hh"
#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4UIterminal.hh>
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include<G4UserRunAction.hh>
#include<G4Run.hh>
#include<iostream>
#include<string>
#include<G4EmLivermorePhysics.hh>
#include<CLHEP/Random/Random.h>
#include <G4VModularPhysicsList.hh>
#include <G4EmParameters.hh>
#include<io.h>
#include <QGSP_BERT_HP.hh>
#include <G4EmPenelopePhysics.hh>
#include<time.h>


using namespace CLHEP;
using namespace std;

int main(int argc,char** argv)
{
	G4UIExecutive* ui = nullptr;
	if (argc == 1) { ui = new G4UIExecutive(argc, argv); }

	G4VSteppingVerbose::SetInstance(new SteppingVerbose);

//***** Choose the Seed engine
	CLHEP::HepRandom::setTheSeed(time(0)+getpid());

//***** Construct the default run manager
	G4RunManager * runManager = new G4RunManager;

//***** Set mandatory initialization classes

//11111 Detector construction:
	DetectorConstruction* detector_c = new DetectorConstruction;
	runManager->SetUserInitialization(detector_c);

//22222 Physics list:
	G4VModularPhysicsList* physicsList = new G4VModularPhysicsList();
	physicsList->RegisterPhysics(new G4EmPenelopePhysics);
	// Set electron tracking threshold to 100 keV
	physicsList->SetCutValue(10 * eV, "e+");
	physicsList->SetCutValue(10 * eV, "e-");
	physicsList->SetCutValue(10 * eV, "gamma");
	physicsList->SetDefaultCutValue(10 * eV);

    runManager->SetUserInitialization(physicsList);

  
//33333 Initialize visualization:
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
   
//44444 User action initialization
    runManager->SetUserInitialization(new ActionInitialization());

//55555 Initialize G4 kernel:
	runManager->Initialize();


//***** Get the pointer to the User Interface manager: 
	G4UImanager* UI = G4UImanager::GetUIpointer();
	UI->ApplyCommand("/control/execute vis.mac");
	ui->SessionStart();

//***** Job termination
	delete ui;
	delete visManager;
	delete runManager;

	return 0;
}