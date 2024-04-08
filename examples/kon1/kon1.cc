#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "SteppingVerbose.hh"

#include<G4RunManager.hh>
#include<G4UImanager.hh>
#include "QBBC.hh"
#include<G4UIterminal.hh>
#include<G4VisExecutive.hh>
#include<G4Material.hh>
#include<G4UserRunAction.hh>
#include<G4Run.hh>
#include<iostream>
#include<string>
#include<CLHEP/Random/Random.h>
#include<time.h>
#include<G4EmLivermorePhysics.hh>
#include<G4EmDNAPhysics.hh>
#include <G4UIExecutive.hh>

using namespace std;

int main(int argc,char** argv)
{
	G4UIExecutive* ui = nullptr;
	if (argc == 1) { 
		ui = new G4UIExecutive(argc, argv); 
	}
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
	G4VModularPhysicsList* physicsList = new QBBC;
	physicsList->SetVerboseLevel(1);
	physicsList->RegisterPhysics(new G4EmLivermorePhysics); 
	physicsList->RegisterPhysics(new G4EmDNAPhysics);
	runManager->SetUserInitialization(physicsList);
  
//33333 Initialize visualization:
	G4VisManager* visManager = new G4VisExecutive;
	visManager->Initialize();
   
//44444 User action initialization
     runManager->SetUserInitialization(new ActionInitialization());

//55555 Initialize G4 kernel:
	runManager->Initialize();

//***** Print all materials
    cout<<"===============================================================";
	cout<<endl;
	cout<< *(G4Material::GetMaterialTable()) << endl;
	cout<<"===============================================================";
	cout<<endl;

//***** Get the pointer to the User Interface manager: 
	G4UImanager* UI = G4UImanager::GetUIpointer();    

//***** Execute macros file:
//        UI->ApplyCommand("/control/execute /home/school01/Kon1/visHEP.mac"); //HEPREP
	UI->ApplyCommand("/control/execute vis1.mac");//OpenGL
	ui->SessionStart();

//***** Job termination
	delete ui;
	delete visManager;
	delete runManager;

	return 0;
}
