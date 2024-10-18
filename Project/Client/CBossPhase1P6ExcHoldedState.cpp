#include "pch.h"
#include "CBossPhase1P6ExcHoldedState.h"

#include <Scripts/CBossScript.h>

CBossPhase1P6ExcHoldedState::CBossPhase1P6ExcHoldedState()
{
}

CBossPhase1P6ExcHoldedState::~CBossPhase1P6ExcHoldedState()
{
}


void CBossPhase1P6ExcHoldedState::finaltick()
{
}

void CBossPhase1P6ExcHoldedState::Enter()
{
}

void CBossPhase1P6ExcHoldedState::Exit()
{
	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
}

