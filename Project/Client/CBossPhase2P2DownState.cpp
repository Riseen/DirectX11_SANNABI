#include "pch.h"
#include "CBossPhase2P2DownState.h"

#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2P2DownState::CBossPhase2P2DownState()
	: m_fDownTime(0.5f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P2DownState::~CBossPhase2P2DownState()
{
}

void CBossPhase2P2DownState::finaltick()
{
	if (m_fAccTime > m_fDownTime)
	{
		CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		int BossCount = pSelf->GetScript<CBossScript>()->GetCurPatternCount();
		BossCount--;
		if (BossCount > 0)
		{
			ChangeState(L"BossPhase2P2AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern2_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern2_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(BossCount);
		}
		else
		{
			ChangeState(L"BossPhase2P6AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(2);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 9.6f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
	}

	m_fAccTime += DT;
}

void CBossPhase2P2DownState::Enter()
{
}

void CBossPhase2P2DownState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}


