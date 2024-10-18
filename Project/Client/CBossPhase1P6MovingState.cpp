#include "pch.h"
#include "CBossPhase1P6MovingState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase1P6MovingState::CBossPhase1P6MovingState()
	: m_fMovingTime(5.f)
	, m_fAccTime(0.f)
	, m_fSpeed(250.f)
{
}

CBossPhase1P6MovingState::~CBossPhase1P6MovingState()
{
}


void CBossPhase1P6MovingState::finaltick()
{
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();

	if (vTargetPos.x > vPos.x)
	{
		vPos.x += m_fSpeed * DT;

		pSelf->Transform()->SetRelativePos(vPos);
	}
	else if (vTargetPos.x < vPos.x)
	{
		vPos.x -= m_fSpeed * DT;

		pSelf->Transform()->SetRelativePos(vPos);
	}
	if (m_fAccTime > m_fMovingTime)
	{
		ChangeState(L"BossPhase1P6GroggyState");
	}
	m_fAccTime += DT;
}

void CBossPhase1P6MovingState::Enter()
{
	
}

void CBossPhase1P6MovingState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern6_GROGGY);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern6_GROGGY);
}

