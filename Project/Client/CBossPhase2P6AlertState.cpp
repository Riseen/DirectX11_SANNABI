#include "pch.h"
#include "CBossPhase2P6AlertState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2P6AlertState::CBossPhase2P6AlertState()
	: m_fAlertTime(5.f)
	, m_fAccTime(0.f)
	, m_fSpeed(200.f)
{
}

CBossPhase2P6AlertState::~CBossPhase2P6AlertState()
{
}


void CBossPhase2P6AlertState::finaltick()
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
		m_fAccTime = 0.f;
		ChangeState(L"BossPhase2P6MovingState");
	}
	m_fAccTime += DT;
}

void CBossPhase2P6AlertState::Enter()
{
}

void CBossPhase2P6AlertState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern6_MOVING);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern6_MOVING);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossSpin.wav", 1, 0.1f);
}

