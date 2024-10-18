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

	// �ѹ��� �����Ǿ���


	// ���������԰� �����ð� ������ Down -> �ѹ� �ݺ��� -> Pattern2
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

