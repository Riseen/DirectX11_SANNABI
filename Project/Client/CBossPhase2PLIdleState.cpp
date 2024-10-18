#include "pch.h"
#include "CBossPhase2PLIdleState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2PLIdleState::CBossPhase2PLIdleState()
	: m_fAttackTime(2.f)
	, m_fAccTime(0.f)
{
}

CBossPhase2PLIdleState::~CBossPhase2PLIdleState()
{
}

void CBossPhase2PLIdleState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	BOSS_STATE BossState = pSelf->GetScript<CBossScript>()->GetCurBossState();

	// 한번만 생성되야함


	// 데미지안입고 일정시간 지나면 Down -> 한번 반복후 -> Pattern2
	if (m_fAccTime > m_fAttackTime)
	{
		ChangeState(L"BossPhase2PLDownState");
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_PatternLast_DOWN);
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_PatternLast_DOWN);
	}

	m_fAccTime += DT;
}

void CBossPhase2PLIdleState::Enter()
{
}

void CBossPhase2PLIdleState::Exit()
{
	m_fAccTime = 0.f;
}

