#include "pch.h"
#include "CBossPhase2PLAlertState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2PLAlertState::CBossPhase2PLAlertState()
	: m_fAlertTime(5.f)
	, m_fAccTime(0.f)
	, m_fSpeed(200.f)
{
}

CBossPhase2PLAlertState::~CBossPhase2PLAlertState()
{
}

void CBossPhase2PLAlertState::finaltick()
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
	if (m_fAccTime > m_fAlertTime)
	{
		ChangeState(L"BossPhase2PLIdleState");
	}
	m_fAccTime += DT;
}

void CBossPhase2PLAlertState::Enter()
{
}

void CBossPhase2PLAlertState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_PatternLast_IDLE);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_PatternLast_IDLE);
}


