#include "pch.h"
#include "CBossPhase2P1IdleState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase2P1IdleState::CBossPhase2P1IdleState()
	: m_fAttackTime(2.f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P1IdleState::~CBossPhase2P1IdleState()
{
}


void CBossPhase2P1IdleState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	BOSS_STATE BossState = pSelf->GetScript<CBossScript>()->GetCurBossState();

	// �ѹ��� �����Ǿ���


	// ���������԰� �����ð� ������ Down -> �ѹ� �ݺ��� -> Pattern2
	if (m_fAccTime > m_fAttackTime)
	{
		ChangeState(L"BossPhase2P1DownState");
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern1_DOWN);
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern1_DOWN);
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}

	m_fAccTime += DT;
}

void CBossPhase2P1IdleState::Enter()
{
}

void CBossPhase2P1IdleState::Exit()
{
	m_fAccTime = 0.f;
}

