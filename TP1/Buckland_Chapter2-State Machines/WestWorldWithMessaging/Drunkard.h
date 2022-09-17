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

#include "fsm/State.h"
#include "BaseGameEntity.h"
#include "Locations.h"
#include "DrunkardOwnedStates.h"
#include "misc/ConsoleUtils.h"
#include "Miner.h"
#include "fsm/StateMachine.h"
#include "misc/Utils.h"

class Drunkard : public BaseGameEntity
{
};

#endif