#include "pch.h"
#include "CBossPhase1PNState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

CBossPhase1PNState::CBossPhase1PNState()
	: m_fNextPhaseTime(8.f)
	, m_fAccTime(0.f)
{
}

CBossPhase1PNState::~CBossPhase1PNState()
{
}


void CBossPhase1PNState::finaltick()
{
	if (m_fAccTime > m_fNextPhaseTime)
	{
		// 2Æä
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_NextPhase_END);
	}
	if (m_fAccTime > m_fNextPhaseTime + 0.8f)
	{
		// 2Æä
		ChangeState(L"BossPhase2P1AlertState");
	}

	m_fAccTime += DT;
}

void CBossPhase1PNState::Enter()
{
}

void CBossPhase1PNState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern1_ALERT);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern1_ALERT);
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
}

