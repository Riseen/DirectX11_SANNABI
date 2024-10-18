#include "pch.h"
#include "CBossPhase2P6GroggyState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2P6GroggyState::CBossPhase2P6GroggyState()
	: m_fGroggyTime(3.f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P6GroggyState::~CBossPhase2P6GroggyState()
{
}


void CBossPhase2P6GroggyState::finaltick()
{
	if (m_fAccTime > m_fGroggyTime)
	{
		ChangeState(L"BossPhase2P6DownState");
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern6_DOWN);
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern6_DOWN);
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}


	m_fAccTime += DT;
}

void CBossPhase2P6GroggyState::Enter()
{
}

void CBossPhase2P6GroggyState::Exit()
{
	m_fAccTime = 0.f;
}

