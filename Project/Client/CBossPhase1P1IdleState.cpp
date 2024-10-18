#include "pch.h"
#include "CBossPhase1P1IdleState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

/*
	�켱 ����

	- ExcHolded
	
	DAMAGE, DOWN -> next pattern

*/

CBossPhase1P1IdleState::CBossPhase1P1IdleState()
	: m_fAttackTime(2.f)
	, m_fAccTime(0.f)
{

}

CBossPhase1P1IdleState::~CBossPhase1P1IdleState()
{
}


void CBossPhase1P1IdleState::finaltick()
{
	// Collosion ���� & ����� ����

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	BOSS_STATE BossState = pSelf->GetScript<CBossScript>()->GetCurBossState();

	// �ѹ��� �����Ǿ���
	
	 
	// ���������԰� �����ð� ������ Down -> �ѹ� �ݺ��� -> Pattern2
	if (m_fAccTime > m_fAttackTime)
	{
		ChangeState(L"BossPhase1P1DownState");
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern1_DOWN);
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}

	m_fAccTime += DT;
}

void CBossPhase1P1IdleState::Enter()
{
	
}

void CBossPhase1P1IdleState::Exit()
{
	m_fAccTime = 0.f;
}

