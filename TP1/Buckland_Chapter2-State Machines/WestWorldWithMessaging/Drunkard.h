#ifndef DRUNKARD_H
#define DRUNKARD_H

//------------------------------------------------------------------------
//
//  Name:   Drunkard.h
//
//  Desc:   class to implement Drunkard class
//
//  Author: Camille Boucher 2022(camille.boucher3@uqac.ca)
//
//------------------------------------------------------------------------
#include <string>
#include <cassert>
#include <iostream>

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DrunkardOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"


template <class entity_type> class State;
struct Telegram;

//the amount of booze a drunkard must have before he feels drunk
const int DrunkardDrunkLevel = 3;
//above this value a drunkard is thirsty
const int DrunkardThirstLevel = 5;
//above this value a drunkard is sleepy
const int DrunkardFatigueLevel= 5;

class Drunkard : public BaseGameEntity
{
private:

    //an instance of the state machine class
    StateMachine<Drunkard>* d_pStateMachine;

    //how many boozes the drunkard has drunk
    int                   d_iDrunk;

    //the higher the value, the thirstier the drunkard
    int                   d_iThirst;

    //the higher the value, the more tired the drunkard
    int                   d_iFatigue;

public:

    Drunkard(int id) :d_iDrunk(0),
        d_iThirst(0),
        d_iFatigue(0),
        BaseGameEntity(id)

    {
        //set up state machine
        d_pStateMachine = new StateMachine<Drunkard>(this);

        d_pStateMachine->SetCurrentState(SleepOnTable::Instance());

        d_pStateMachine->SetGlobalState(DrunkardGlobalState::Instance());
    }

    ~Drunkard() { delete d_pStateMachine; }

    //this must be implemented
    void Update();

    //so must this
    virtual bool  HandleMessage(const Telegram& msg);


    StateMachine<Drunkard>* GetFSM()const { return d_pStateMachine; }



    //-------------------------------------------------------------accessors
    bool          Drunk()const;
    void          DecreaseDrunk() { d_iDrunk -= 1; }
    void          IncreaseDrunk() { d_iDrunk += 1; }

    bool          Fatigued()const;
    void          DecreaseFatigue() { d_iFatigue -= 2; }
    void          IncreaseFatigue() { d_iFatigue += 1; }

    bool          Thirsty()const;
    void          DrinkABooze() { d_iThirst = 0; IncreaseDrunk(); }
    void          IncreaseThirst() { d_iThirst += 1; }

};

#endif
