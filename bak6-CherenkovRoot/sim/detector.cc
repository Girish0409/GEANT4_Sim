#include "detector.hh"
#include "G4String.hh"
#include "G4RunManager.hh"

MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{

}

MySensitiveDetector::~MySensitiveDetector()
{

}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep,G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();
    track->SetTrackStatus(fStopAndKill);
    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();
    G4ThreeVector posPhoton = preStepPoint->GetPosition();
    //G4cout << "Photon Position:  " << posPhoton << G4endl ;
    
    //Access to our detector position for cherenkov angle
    //Touchable is the access to logical detector 
    
    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();
    //G4cout << "Copy Number : " << touchable->GetCopyNumber() << G4endl;

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    G4cout << "Detector Position: " << posDetector << G4endl;
    
    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0,evt);      //evt = event number
    man->FillNtupleDColumn(1,posDetector[0]);
    man->FillNtupleDColumn(2,posDetector[1]);
    man->FillNtupleDColumn(3,posDetector[2]);
    man->AddNtupleRow();
    
   
    
    
    return true;
}