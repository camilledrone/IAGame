#include "DrunkardOwnedStates.h"
#include "MinerOwnedStates.h"
#include "Drunkard.h"
#include "Locations.h"
#include "Time/CrudeTimer.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "EntityNames.h"

#include <iostream>
using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-----------------------------------------------------------------------Global state

DrunkardGlobalState* DrunkardGlobalState::Instance()
{
    static DrunkardGlobalState instance;

    return &instance;
}


void DrunkardGlobalState::Execute(Drunkard* drunkard)
{
}

bool DrunkardGlobalState::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

    switch (msg.Msg)
    {
    case Msg_BobIsEnteringTheSaloon:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(drunkard->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if ((drunkard->GetFSM()->isInState(*WanderAndDance::Instance())|| drunkard->GetFSM()->isInState(*DrinkBooze::Instance()))) {
            cout << "\n" << GetNameOfEntity(drunkard->ID()) <<
                ": Look at this weirdo entering my saloon ! ";

            drunkard->GetFSM()->ChangeState(Fight::Instance());

        }
        
    }

    return true;

    }//end switch

    return false;
}

//-------------------------------------------------------------------------DrinkBooze

DrinkBooze* DrinkBooze::Instance()
{
    static DrinkBooze instance;

    return &instance;
}


void DrinkBooze::Enter(Drunkard* drunkard)
{
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I am thirsty ! Time to Drink some booze !";
}


void DrinkBooze::Execute(Drunkard* drunkard)
{
    // The drunkard is drinking a booze until he gets drunk and go wandering and dancing.
    // If he gets sleepy he will drink another booze and go to sleep on a table of the saloon.
    drunkard->DrinkABooze();
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": glouglou !";
    drunkard->IncreaseFatigue();

    if (drunkard->Drunk())
    {
        drunkard->GetFSM()->ChangeState(WanderAndDance::Instance());
    }
    if (drunkard->Fatigued())
    {
        drunkard->GetFSM()->ChangeState(SleepOnTable::Instance());
    }

}

void DrinkBooze::Exit(Drunkard* drunkard)
{
}

bool DrinkBooze::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
    return false;
}


//-------------------------------------------------------------------------WanderAndDance

WanderAndDance* WanderAndDance::Instance()
{
    static WanderAndDance instance;

    return &instance;
}


void WanderAndDance::Enter(Drunkard* drunkard)
{
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I am a bit tipsy ! Let's go on the dancefloor !";
}


void WanderAndDance::Execute(Drunkard* drunkard)
{
    //The drunkard is wandering and dancing in the saloon until he gets thirsty or tired.
    //If Bob enters the saloon, the drunkard will receive a meessage and start a fight (see the method OnMessage)
    drunkard->DecreaseDrunk();
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": lets dance !";
    drunkard->IncreaseFatigue();

    if (drunkard->Thirsty())
    {
        drunkard->GetFSM()->ChangeState(DrinkBooze::Instance());
    }
    if (drunkard->Fatigued())
    {
        drunkard->GetFSM()->ChangeState(SleepOnTable::Instance());
    }
}

void WanderAndDance::Exit(Drunkard* drunkard)
{
}

bool WanderAndDance::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
    return false; //send message to global message handler
}


//-------------------------------------------------------------------------Fight

Fight* Fight::Instance()
{
    static Fight instance;

    return &instance;
}


void Fight::Enter(Drunkard* drunkard)
{
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Let's fight !";
    Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
        drunkard->ID(),               //sender ID
        ent_Miner_Bob,             //receiver ID
        Msg_Fight, //msg  TO CHANGE TO FIGHT
        NO_ADDITIONAL_INFO);
}



void Fight::Execute(Drunkard* drunkard)
{
    //The drunkard is fighting with bob until bob apologizes.
    drunkard->DecreaseDrunk();
    drunkard->IncreaseFatigue();
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": figth !";

}

void Fight::Exit(Drunkard* drunkard)
{
}

bool Fight::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
    
    SetTextColor(BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    switch (msg.Msg)
    {
    case Msg_IApologize:
    {
        cout << "\nMessage handled by " << GetNameOfEntity(drunkard->ID()) << " at time: "
            << Clock->GetCurrentTime();

        SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        if (drunkard->GetFSM()->isInState(*Fight::Instance())) {
            cout << "\n" << GetNameOfEntity(drunkard->ID())
                << ": I accept your apologize weirdo ..";

            drunkard->GetFSM()->ChangeState(SleepOnTable::Instance());
        }

    }
    return true;
    }
    
    return false; //send message to global message handler
}

//-------------------------------------------------------------------------SleepOnTable

SleepOnTable* SleepOnTable::Instance()
{
    static SleepOnTable instance;

    return &instance;
}


void SleepOnTable::Enter(Drunkard* drunkard)
{
    cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Oh man I am sure tired, let's sleep a bit on this table !";
}


void SleepOnTable::Execute(Drunkard* drunkard)
{
    //if the drunkard is not tired anymore, he starts drinking again.
    if (!drunkard->Fatigued())
    {
        cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": "
            << "All mah fatigue has drained away. Time to drink some booze !";
        drunkard->GetFSM()->ChangeState(DrinkBooze::Instance());
    }

    else
    {
        //sleep
        drunkard->DecreaseFatigue();
        cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": " << "ZZZZ... ";
    }
}

void SleepOnTable::Exit(Drunkard* drunkard)
{
}

bool SleepOnTable::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
    return false;
}
