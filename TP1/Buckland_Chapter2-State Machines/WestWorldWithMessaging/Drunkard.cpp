#include "Drunkard.h"

bool Drunkard::HandleMessage(const Telegram& msg)
{
    return d_pStateMachine->HandleMessage(msg);
}


void Drunkard::Update()
{
    SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    d_iThirst += 1;

    d_pStateMachine->Update();
}

bool Drunkard::Drunk()const
{
    if (d_iDrunk >= DrunkardDrunkLevel) { return true; }

    return false;
}

bool Drunkard::Thirsty()const
{
    if (d_iThirst >= DrunkardThirstLevel) { return true; }

    return false;
}

bool Drunkard::Fatigued()const
{
    if (d_iFatigue > DrunkardFatigueLevel)
    {
        return true;
    }

    return false;
}
