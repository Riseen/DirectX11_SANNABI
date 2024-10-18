#include "pch.h"
#include "CBossPhase2P1AlertState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

CBossPhase2P1AlertState::CBossPhase2P1AlertState()
	: m_fAlertTime(5.f)
	, m_fAccTime(0.f)
	, m_fSpeed(200.f)
{
}

CBossPhase2P1AlertState::~CBossPhase2P1AlertState()
{
}

void CBossPhase2P1AlertState::finaltick()
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
		ChangeState(L"BossPhase2P1IdleState");
	}
	m_fAccTime += DT;
}

void CBossPhase2P1AlertState::Enter()
{
}

void CBossPhase2P1AlertState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern1_IDLE);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern1_IDLE);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossPopUp.wav", 1, 0.1f);
}


