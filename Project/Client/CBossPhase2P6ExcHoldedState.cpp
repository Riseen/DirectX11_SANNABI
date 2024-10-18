#include "pch.h"
#include "CBossPhase2P6ExcHoldedState.h"

CBossPhase2P6ExcHoldedState::CBossPhase2P6ExcHoldedState()
{
}

CBossPhase2P6ExcHoldedState::~CBossPhase2P6ExcHoldedState()
{
}


void CBossPhase2P6ExcHoldedState::finaltick()
{
}

void CBossPhase2P6ExcHoldedState::Enter()
{
}

void CBossPhase2P6ExcHoldedState::Exit()
{
	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
}

