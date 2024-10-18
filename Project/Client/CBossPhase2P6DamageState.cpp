#include "pch.h"
#include "CBossPhase2P6DamageState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>
#include <Scripts/CCameraScript.h>

CBossPhase2P6DamageState::CBossPhase2P6DamageState()
	: m_fDamageTime(1.7f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P6DamageState::~CBossPhase2P6DamageState()
{
}

void CBossPhase2P6DamageState::finaltick()
{
	if (m_fAccTime > m_fDamageTime)
	{
		CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		int BossCount = pSelf->GetScript<CBossScript>()->GetCurPatternCount();
		int BossHP = pSelf->GetScript<CBossScript>()->GetHP();
		BossCount--;
		if (BossHP <= 0)
		{
			ChangeState(L"BossPhase2PLAlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_PatternLast_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_PatternLast_ALERT);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
		else if (BossCount > 0)
		{
			ChangeState(L"BossPhase2P6AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(BossCount);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 9.6f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
		else
		{
			ChangeState(L"BossPhase1P1AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(2);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
	}

	m_fAccTime += DT;
}

void CBossPhase2P6DamageState::Enter()
{
}

void CBossPhase2P6DamageState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}


