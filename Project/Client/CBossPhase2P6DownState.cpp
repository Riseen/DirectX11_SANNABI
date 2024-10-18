#include "pch.h"
#include "CBossPhase2P6DownState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2P6DownState::CBossPhase2P6DownState()
	: m_fDownTime(0.4f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P6DownState::~CBossPhase2P6DownState()
{
}

void CBossPhase2P6DownState::finaltick()
{
	if (m_fAccTime > m_fDownTime)
	{
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		int BossCount = pSelf->GetScript<CBossScript>()->GetCurPatternCount();
		BossCount--;
		if (BossCount > 0)
		{
			ChangeState(L"BossPhase2P6AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(BossCount);
		}
		else
		{
			ChangeState(L"BossPhase2P1AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(2);
		}
	}

	m_fAccTime += DT;
}

void CBossPhase2P6DownState::Enter()
{
}

void CBossPhase2P6DownState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}


