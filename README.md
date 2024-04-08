## Repo now contains:
1. examples <br />
- B1 - basic example from geant4/examples/basic/B1 <br />
- field2 - simple example with particle in e/m field  <br />
- kon1 - basic example with particle passing throught breaking target to some detector(detecting volume)
2. projects <br />
- mpc-detector - microchannel plates detector model

All projects were initialy build on Geant4 v.11.2.1, OS Windows so they may contains some platform specific libraries for C++ + platrom specific .mac files, but they can be easily transfered to any other OS. For some projects additional software may be required (e.g. ROOT) <br />
## Required software:
1. Geant4
2. CMake
3. ROOT (optional)
4. HepRep vis tools (optional)

## Build & run order: 
1. Windows: call geant4.bat  <br />
   Linux: source geant4.sh in ${geant4-install}/bin dir
2. go to ${your_project}
3. cd .. -> mkdir ${your_project}-build -> cd ${your_project}-build
4. cmake ../${your_project}
5. Winows: build via Visual Studio or any other tool  <br />
   Linux: make -j8
6. Linux -> run from same teriminal or new terminal after source geant4.sh  <br />
   Windows -> run from cmd or new terminal after call geant4.bat  <br />
   Or setup proper enviroment with all required imports
