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
    G4ThreeVector momPhoton = preStepPoint->GetMomentum();

    G4double wlen = (1.239841939*eV/momPhoton.mag())*1E+03 ;

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

    man->FillNtupleIColumn(0,0,evt);      //evt = event number
    man->FillNtupleDColumn(0,1,posPhoton[0]);
    man->FillNtupleDColumn(0,2,posPhoton[1]);
    man->FillNtupleDColumn(0,3,posPhoton[2]);
    man->FillNtupleDColumn(0,4,wlen) ;
    man->AddNtupleRow(0);



    man->FillNtupleIColumn(1,0,evt);      //evt = event number
    man->FillNtupleDColumn(1,1,posDetector[0]);
    man->FillNtupleDColumn(1,2,posDetector[1]);
    man->FillNtupleDColumn(1,3,posDetector[2]);
    man->AddNtupleRow(1);
    
   
    
    
    return true;
}