
#include <iostream>
#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Cons.hh"
#include "Cons.cc"
#include "physics.cc"
#include "action.cc"
#include "generator.cc"

int main(int argc, char** argv)
{
    
    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction()) ;
    runManager->SetUserInitialization(new MyPhysicsList()) ;
    runManager->SetUserInitialization(new MyActionInitialization()) ;
    
    runManager->Initialize();
    
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();
    UImanager->ApplyCommand("/control/execute vis.mac") ;


    ui->SessionStart(); 
    return 0;
}