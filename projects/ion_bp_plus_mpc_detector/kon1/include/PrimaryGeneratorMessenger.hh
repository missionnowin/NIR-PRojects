#ifndef H02_PRIMARY_GENERATOR_MESSENGER_H
#define H02_PRIMARY_GENERATOR_MESSENGER_H

#include "globals.hh"
#include "G4UImessenger.hh"

class PrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcommand;
class G4UIcmdWithoutParameter;
class G4UIcmdWithABool;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;

class PrimaryGeneratorMessenger : public G4UImessenger {
public:
	PrimaryGeneratorMessenger(PrimaryGeneratorAction* genaction);
	~PrimaryGeneratorMessenger();

	virtual void SetNewValue(G4UIcommand* command, G4String newValues);
	virtual G4String GetCurrentValue(G4UIcommand* command);

private:
	PrimaryGeneratorAction* fPrimaryAction;

	G4UIdirectory* fDir;
	G4UIcmdWithAString* fSelect;

};

#endif