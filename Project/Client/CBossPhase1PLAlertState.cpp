#include "pch.h"
#include "CBossPhase1PLAlertState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase1PLAlertState::CBossPhase1PLAlertState()
	: m_fAlertTime(5.f)
	, m_fAccTime(0.f)
	, m_fSpeed(200.f)
{
}

CBossPhase1PLAlertState::~CBossPhase1PLAlertState()
{
}


void CBossPhase1PLAlertState::finaltick()
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
		ChangeState(L"BossPhase1PLIdleState");
	}
	m_fAccTime += DT;
}

void CBossPhase1PLAlertState::Enter()
{
}

void CBossPhase1PLAlertState::Exit()
{
 	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_PatternLast_IDLE);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossPopUp.wav", 1, 0.1f);
}
