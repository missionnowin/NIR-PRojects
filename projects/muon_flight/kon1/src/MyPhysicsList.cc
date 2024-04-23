#include "MyPhysicsList.hh"
#include <G4EmParameters.hh>
#include <G4VUserPhysicsList.hh>
#include<G4UAtomicDeexcitation.hh>
#include<G4GenericIon.hh>
#include<G4Proton.hh>
#include<G4Positron.hh>
#include<G4Electron.hh>
#include<G4Gamma.hh>
#include <G4RayleighScattering.hh>
#include <G4ComptonScattering.hh>
#include <G4PhotoElectricEffect.hh>
#include <G4GammaConversion.hh>
#include<G4PhysicsListHelper.hh>
#include <G4eplusAnnihilation.hh>
#include <G4PenelopeRayleighModel.hh>
#include <G4PenelopeComptonModel.hh>
#include <G4PenelopePhotoElectricModel.hh>
#include <G4PenelopeGammaConversionModel.hh>
#include <G4eMultipleScattering.hh>
#include <G4UrbanMscModel.hh>
#include <G4eIonisation.hh>
#include <G4PenelopeIonisationModel.hh>
#include <G4eBremsstrahlung.hh>
#include <G4PenelopeBremsstrahlungModel.hh>
#include <G4PenelopeAnnihilationModel.hh>

using namespace CLHEP;

MyPhysicsList::MyPhysicsList()
{

	G4EmParameters* param = G4EmParameters::Instance();
	param->SetApplyCuts(true);
	SetDefaultCutValue(100 * eV);
	SetVerboseLevel(2);

	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100 * eV, 10 * GeV);
}

MyPhysicsList::~MyPhysicsList()
{}

// //define all particles: e-, e+, n, gamma, p
void MyPhysicsList::ConstructParticle()
{
	G4Electron::ElectronDefinition();
	G4Gamma::GammaDefinition();
	G4Positron::PositronDefinition();
	G4Proton::ProtonDefinition();
	G4ParticleDefinition* particle = G4GenericIon::GenericIon();

}
void MyPhysicsList::ConstructProcess()
{

	AddTransportation();

	ConstructEM();

	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100 * eV, 10 * GeV);
}

void MyPhysicsList::ConstructEM()
{
	G4PhysicsListHelper* ph = G4PhysicsListHelper::GetPhysicsListHelper();

	G4ParticleDefinition* ion = G4GenericIon::GenericIon();
	G4ParticleDefinition* gamma = G4Gamma::GammaDefinition();
	G4ParticleDefinition* electron = G4Electron::ElectronDefinition();
	G4ParticleDefinition* positron = G4Positron::PositronDefinition();

	//gamma

	G4RayleighScattering* rs = new G4RayleighScattering;
	rs->SetEmModel(new G4PenelopeRayleighModel()); 
	G4ComptonScattering* cs = new G4ComptonScattering;
	cs->SetEmModel(new G4PenelopeComptonModel()); 
	G4PhotoElectricEffect* pe = new G4PhotoElectricEffect;
	pe->SetEmModel(new G4PenelopePhotoElectricModel());
	G4GammaConversion* gc = new G4GammaConversion;
	gc->SetEmModel(new G4PenelopeGammaConversionModel());
	ph->RegisterProcess(new G4PhotoElectricEffect(), gamma);
	ph->RegisterProcess(new G4ComptonScattering(), gamma);
	ph->RegisterProcess(new G4GammaConversion(), gamma);
	ph->RegisterProcess(new G4RayleighScattering(), gamma);

	//electron

	//multiple scattering

	G4eMultipleScattering* msc = new G4eMultipleScattering;
	msc->SetEmModel(new G4UrbanMscModel()); 
	G4EmParameters* param = G4EmParameters::Instance();
	G4eIonisation* eion = new  G4eIonisation;
	eion->SetEmModel(new  G4PenelopeIonisationModel()); 
	G4eBremsstrahlung* ebr = new G4eBremsstrahlung;
	ebr->SetEmModel(new G4PenelopeBremsstrahlungModel()); 
	ph->RegisterProcess(new G4eMultipleScattering(), electron);
	ph->RegisterProcess(new G4eBremsstrahlung(), electron);
	ph->RegisterProcess(new G4eIonisation(), electron);

	G4eMultipleScattering* mscp = new G4eMultipleScattering;
	mscp->SetEmModel(new G4UrbanMscModel());
	G4eIonisation* epion = new  G4eIonisation;
	epion->SetEmModel(new  G4PenelopeIonisationModel()); //penelope
	G4eBremsstrahlung* epbr = new G4eBremsstrahlung;
	epbr->SetEmModel(new G4PenelopeBremsstrahlungModel()); //penelope
	G4eplusAnnihilation* eann = new G4eplusAnnihilation;
	eann->SetEmModel(new G4PenelopeAnnihilationModel()); //penelope
	ph->RegisterProcess(new G4eMultipleScattering(), positron);
	ph->RegisterProcess(new G4eBremsstrahlung(), positron);
	ph->RegisterProcess(new G4eIonisation(), positron);
	ph->RegisterProcess(new G4eplusAnnihilation(), positron);
	G4ProductionCutsTable::GetProductionCutsTable()->SetEnergyRange(100 * eV, 10 * GeV);
}

void MyPhysicsList::SetCuts()
{
	G4VUserPhysicsList::SetCuts();
	G4double NewCutValue = 100 * eV;
	G4VUserPhysicsList::SetDefaultCutValue(NewCutValue);
	G4VUserPhysicsList::SetCutValue(NewCutValue, "gamma");
	G4VUserPhysicsList::SetCutValue(NewCutValue, "e+");
	G4VUserPhysicsList::SetCutValue(NewCutValue, "e-");
}