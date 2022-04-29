#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"
#include "run.cc"
#include "event.hh"
#include "event.cc"
#include "stepping.hh"
#include "stepping.cc"


class MyActionInitialization : public G4VUserActionInitialization
{
public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;             //Each worker thread
    
};

#endif