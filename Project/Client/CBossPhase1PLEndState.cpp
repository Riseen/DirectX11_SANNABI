#include "pch.h"
#include "CBossPhase1PLEndState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

CBossPhase1PLEndState::CBossPhase1PLEndState()
	: m_fEndTime(3.2f)
	, m_fAccTime(0.f)
{
}

CBossPhase1PLEndState::~CBossPhase1PLEndState()
{
}


void CBossPhase1PLEndState::finaltick()
{
	if (m_fAccTime > m_fEndTime)
	{
		ChangeState(L"BossPhase1PNState");
	}

	m_fAccTime += DT;
}

void CBossPhase1PLEndState::Enter()
{
}

void CBossPhase1PLEndState::Exit()
{
	m_fAccTime = 0.f;
	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_NextPhase);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_NextPhase);
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 3.8f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
}

