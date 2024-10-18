#include "pch.h"
#include "C3rdBeforePoundingState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

C3rdBeforePoundingState::C3rdBeforePoundingState()
	: m_fPoundingTime(2.f)
	, m_fAccTime (0.f)
{
}

C3rdBeforePoundingState::~C3rdBeforePoundingState()
{
}


void C3rdBeforePoundingState::finaltick()
{
	if (m_fAccTime > m_fPoundingTime)
	{
		ChangeState(L"3rdPoundingState");
	}


	m_fAccTime += DT;
}

void C3rdBeforePoundingState::Enter()
{
}

void C3rdBeforePoundingState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_3rdPoundingReady);
}

