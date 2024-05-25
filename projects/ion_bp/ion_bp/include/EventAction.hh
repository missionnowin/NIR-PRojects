
#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
/// Event action class

class HistoManager;

class EventAction : public G4UserEventAction
{
  public:
    EventAction(HistoManager*);
    virtual ~EventAction();
    
    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void AddEdep(G4double edep) { fEdepTot += edep; }
    void GetEdep(G4double edep) { fEdep = edep; }
    void GetPosition(G4ThreeVector pos) { fPosition = pos;} 
    void AddProtons(G4double edep) { fEdepTot += edep; }
    void AddElectronSts1() {++fElectronsSts1;}
    void AddElectronSts2() {++fElectronsSts2;}
    void AddElectronSts3() {++fElectronsSts3;}
    void AddElectronSts4() {++fElectronsSts4;}
    void AddElectronGem1() {++fElectronsGem1;}   
    void AddElectronGem2() {++fElectronsGem2;} 
    void AddElectronGem3() {++fElectronsGem3;} 
    void AddElectronGem4() {++fElectronsGem4;} 
    void AddElectronGem5() {++fElectronsGem5;} 
    void AddElectronGem6() {++fElectronsGem6;} 
    void AddElectronGem7() {++fElectronsGem7;} 

  private:
    HistoManager* fHistoManager;
    G4double  fEdepTot;  //total energy deposit in SPD
    G4double  fEdep;     //energy deposit in SPD during one step
    G4ThreeVector fPosition; // Position of track entering given detector
    G4int fElectronsSts1;     // number of electrons coming to StsSt1
    G4int fElectronsSts2;     // number of electrons coming to StsSt2
    G4int fElectronsSts3;     // number of electrons coming to StsSt3
    G4int fElectronsSts4;     // number of electrons coming to StsSt4 
    G4int fElectronsGem1;     // number of electrons coming to GemSt1
    G4int fElectronsGem2;     // number of electrons coming to GemSt2
    G4int fElectronsGem3;     // number of electrons coming to GemSt3
    G4int fElectronsGem4;     // number of electrons coming to GemSt4
    G4int fElectronsGem5;     // number of electrons coming to GemSt5
    G4int fElectronsGem6;     // number of electrons coming to GemSt6
    G4int fElectronsGem7;     // number of electrons coming to GemSt7
};

#endif

    
