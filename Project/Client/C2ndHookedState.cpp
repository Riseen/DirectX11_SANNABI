#include "pch.h"
#include "C2ndHookedState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

C2ndHookedState::C2ndHookedState()
	: m_f2ndHookedTime(5.f)
	, m_fAccTime(0.f)
{
}

C2ndHookedState::~C2ndHookedState()
{
}


void C2ndHookedState::finaltick()
{
	if (m_fAccTime > m_f2ndHookedTime)
	{
		ChangeState(L"3rdHookedState");
	}

	m_fAccTime += DT;
}

void C2ndHookedState::Enter()
{
}

void C2ndHookedState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_3rdHooked);
}

