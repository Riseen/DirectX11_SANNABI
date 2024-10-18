#include "pch.h"
#include "CBossPhase1P1DownState.h"

#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase1P1DownState::CBossPhase1P1DownState()
	: m_fDownTime(0.5f)
	, m_fAccTime(0.f)
{
}

CBossPhase1P1DownState::~CBossPhase1P1DownState()
{
}

void CBossPhase1P1DownState::finaltick()
{
	
	if (m_fAccTime > m_fDownTime)
	{
		CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		int BossCount = pSelf->GetScript<CBossScript>()->GetCurPatternCount();
		BossCount--;
		if (BossCount > 0)
		{
			ChangeState(L"BossPhase1P1AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(BossCount);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
		else
		{
			ChangeState(L"BossPhase1P2AlertState"); 
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern2_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern2_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(2);
		}
	}

	m_fAccTime += DT;
}

void CBossPhase1P1DownState::Enter()
{
}

void CBossPhase1P1DownState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}

