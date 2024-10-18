#include "pch.h"
#include "C1stHookedState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

C1stHookedState::C1stHookedState()
	: m_f1stHookedTime(5.f)
	, m_fAccTime (0.f)
{
}

C1stHookedState::~C1stHookedState()
{
}

void C1stHookedState::finaltick()
{
	if (m_fAccTime > m_f1stHookedTime)
	{
		ChangeState(L"2ndHookedState");
	}

	m_fAccTime += DT;
}

void C1stHookedState::Enter()
{
}

void C1stHookedState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_2ndHooked);
}


