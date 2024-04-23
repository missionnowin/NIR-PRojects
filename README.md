## Repo now contains:
### 1. examples <br />
- B1 - basic example from geant4/examples/basic/B1 <br />
- field2 - simple example with particle in e/m field  <br />
- kon1 - basic example with particle passing throught breaking target to some detector(detecting volume)
### 2. projects <br />
- mpc-detector - microchannel plates detector model 
- muon-flight - mini-project with simulation of muons flight through atmosphere (20 - 0 km). (Maybe not working now)

### Note: <br />
All projects were initialy build on Geant4 v.11.2.1 + OS Windows so they may contains some platform specific libraries for C++ & platrom-specific .mac files, but they can be easily transfered to any other OS. For some projects additional software may be required (e.g. ROOT) <br />
## Required software:
1. Geant4
2. CMake
3. ROOT (optional)
4. HepRep vis tools (optional)

## Build & run order: 
### 1. Pre-build setup<br />
```
   cd ${geant4-install}/bin
```   
Windows:
```
   call geant4.bat
```
   Linux:
```
   source geant4.sh
```
### 2. Build
```
   cd ${your_project}/
   cd ..
   mkdir ${your_project}-build
   cd ${your_project}-build/
   cmake ../${your_project}
```
### 3. Compile<br />
   Winows: build via Visual Studio or any other tool  <br />
   Linux:  make -j8
### 4. Run<br />
   Linux: run executable from same teriminal or new terminal after source geant4.sh  <br />
   Windows: run executable from sane cmd/shell or new session after call geant4.bat  <br />
   Or setup proper enviroment with all required imports
