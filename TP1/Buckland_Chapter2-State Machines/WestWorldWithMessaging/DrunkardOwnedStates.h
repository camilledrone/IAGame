#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H

//------------------------------------------------------------------------
//
//  Name:   DrunkardOwnedStates.h
//
//  Desc:   All the states that can be assigned to the  Drunkard class
//
//  Author: Camille Boucher 2022 (camille.boucher3@uqac.ca)
//
//------------------------------------------------------------------------
#include "fsm/State.h"

class Drunkard;


//------------------------------------------------------------------------
//

//------------------------------------------------------------------------
class DrunkardGlobalState : public State<Drunkard>
{
private:

	DrunkardGlobalState() {}

	//copy ctor and assignment should be private
	DrunkardGlobalState(const DrunkardGlobalState&);
	DrunkardGlobalState& operator=(const DrunkardGlobalState&);

public:

	//this is a singleton
	static DrunkardGlobalState* Instance();

	virtual void Enter(Drunkard* drunkard) {}

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard) {}

	virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);
};


//------------------------------------------------------------------------
//Drunkard will drink booze until he is sleepy or drunk
//------------------------------------------------------------------------
class DrinkBooze : public State<Drunkard>
{
private:

	DrinkBooze() {}

	//copy ctor and assignment should be private
	DrinkBooze(const DrinkBooze&);
	DrinkBooze& operator=(const DrinkBooze&);

public:

	//this is a singleton
	static DrinkBooze* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);

};


//------------------------------------------------------------------------
//Drunkard will wander and dance in the saloon 
// He will go to sleep if he is thristy
// He will go back drink booze again if is thirsty
// He will fight if Bob enters the saloon
//------------------------------------------------------------------------
class WanderAndDance : public State<Drunkard>
{
private:

	WanderAndDance() {}

	//copy ctor and assignment should be private
	WanderAndDance(const WanderAndDance&);
	WanderAndDance& operator=(const WanderAndDance&);

public:

	//this is a singleton
	static WanderAndDance* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);

};

//------------------------------------------------------------------------
//Drunkard will fight with Bob if he enters the saloon when the drunkard is in the state WanderAndDance or DrinkBooze
// Drunkard stop fighting when Bob apologizes and go straight to sleep
//------------------------------------------------------------------------
class Fight : public State<Drunkard>
{
private:

	Fight() {}

	//copy ctor and assignment should be private
	Fight(const Fight&);
	Fight& operator=(const Fight&);

public:

	//this is a singleton
	static Fight* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);

};

//------------------------------------------------------------------------
//Drunkard will sleep in the saloon when he is tired
// When he is not tired anymore he will go drink booze
//------------------------------------------------------------------------
class SleepOnTable : public State<Drunkard>
{
private:

	SleepOnTable() {}

	//copy ctor and assignment should be private
	SleepOnTable(const SleepOnTable&);
	SleepOnTable& operator=(const SleepOnTable&);

public:

	//this is a singleton
	static SleepOnTable* Instance();

	virtual void Enter(Drunkard* drunkard);

	virtual void Execute(Drunkard* drunkard);

	virtual void Exit(Drunkard* drunkard);

	virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);

};

#endif