#include "pch.h"
#include "CBossPhase1PLIdleState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase1PLIdleState::CBossPhase1PLIdleState()
	: m_fAttackTime(2.f)
	, m_fAccTime(0.f)
{
}

CBossPhase1PLIdleState::~CBossPhase1PLIdleState()
{
}

void CBossPhase1PLIdleState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	BOSS_STATE BossState = pSelf->GetScript<CBossScript>()->GetCurBossState();

	// 한번만 생성되야함

	
	if (m_fAccTime > m_fAttackTime)
	{
		ChangeState(L"BossPhase1PLDownState");
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_PatternLast_DOWN);
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}

	m_fAccTime += DT;
}

void CBossPhase1PLIdleState::Enter()
{
}

void CBossPhase1PLIdleState::Exit()
{
	m_fAccTime = 0.f;
}


