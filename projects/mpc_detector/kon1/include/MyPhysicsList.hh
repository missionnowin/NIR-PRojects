#ifndef MyPhysicsList_h
#define MyPhysicsList_h 1

#include <G4VUserPhysicsList.hh>

class MyPhysicsList : public G4VUserPhysicsList {
public:
	MyPhysicsList();
	~MyPhysicsList();
	void ConstructParticle();
	void ConstructProcess();
	void ConstructEM();
	void SetCuts();
};

#endif