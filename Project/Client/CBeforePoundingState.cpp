#include "pch.h"
#include "CBeforePoundingState.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CKeyMgr.h>
#include <Scripts/CBossScript.h>

CBeforePoundingState::CBeforePoundingState()
	: m_fBeforeTime (3.3f)
	, m_fAccTime (0.f)
{
	
}

CBeforePoundingState::~CBeforePoundingState()
{
}

void CBeforePoundingState::finaltick()
{
	if (m_fAccTime > m_fBeforeTime)
	{
		ChangeState(L"1stPoundingState");
	}

	m_fAccTime += DT;
}

void CBeforePoundingState::Enter()
{
}

void CBeforePoundingState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_1stPoundingReady);
}


