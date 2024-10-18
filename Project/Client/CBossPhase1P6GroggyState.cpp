#include "pch.h"
#include "CBossPhase1P6GroggyState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase1P6GroggyState::CBossPhase1P6GroggyState()
	: m_fGroggyTime (3.f)
	, m_fAccTime (0.f)
{
}

CBossPhase1P6GroggyState::~CBossPhase1P6GroggyState()
{
}


void CBossPhase1P6GroggyState::finaltick()
{
	if (m_fAccTime > m_fGroggyTime)
	{
		ChangeState(L"BossPhase1P6DownState");
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern6_DOWN);
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}


	m_fAccTime += DT;
}

void CBossPhase1P6GroggyState::Enter()
{
}

void CBossPhase1P6GroggyState::Exit()
{
	m_fAccTime = 0.f;
}

