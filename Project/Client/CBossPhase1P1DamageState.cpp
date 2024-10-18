#include "pch.h"
#include "CBossPhase1P1DamageState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>
#include <Scripts/CCameraScript.h>


CBossPhase1P1DamageState::CBossPhase1P1DamageState()
	: m_fDownTime(1.7f)
	, m_fAccTime(0.f)
{
}

CBossPhase1P1DamageState::~CBossPhase1P1DamageState()
{
}

void CBossPhase1P1DamageState::finaltick()
{
	
	

	if (m_fAccTime > m_fDownTime)
	{
		CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		int BossCount = pSelf->GetScript<CBossScript>()->GetCurPatternCount();
		int BossHP = pSelf->GetScript<CBossScript>()->GetHP();
		BossCount--;
		if (BossHP <= 3)
		{
			ChangeState(L"BossPhase1PLAlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_PatternLast_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_PatternLast_ALERT);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
		else if (BossCount > 0)
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

void CBossPhase1P1DamageState::Enter()
{
}

void CBossPhase1P1DamageState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}

