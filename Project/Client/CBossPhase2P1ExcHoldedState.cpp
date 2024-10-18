#include "pch.h"
#include "CBossPhase2P1ExcHoldedState.h"

CBossPhase2P1ExcHoldedState::CBossPhase2P1ExcHoldedState()
{
}

CBossPhase2P1ExcHoldedState::~CBossPhase2P1ExcHoldedState()
{
}

void CBossPhase2P1ExcHoldedState::finaltick()
{
}

void CBossPhase2P1ExcHoldedState::Enter()
{
}

void CBossPhase2P1ExcHoldedState::Exit()
{
	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
}


