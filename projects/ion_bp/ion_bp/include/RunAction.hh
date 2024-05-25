

#ifndef RunAction_h
#define RunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class G4LogicalVolume;
class HistoManager;

/// Run action class

/// In EndOfRunAction(), it calculates energy deposit in the selected sensetive volumes accumulated via stepping and event actions.
/// The total energy deposit is then printed on the screen.

class RunAction : public G4UserRunAction
{
  public:
    RunAction(HistoManager*);
    virtual ~RunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void   EndOfRunAction(const G4Run*);

  private:
    HistoManager* fHistoManager;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

