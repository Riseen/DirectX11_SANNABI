#include "pch.h"
#include "CBossPhase1P6DamageState.h"

#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

CBossPhase1P6DamageState::CBossPhase1P6DamageState()
	: m_fDamageTime (1.7f)
	, m_fAccTime (0.f)
{
}

CBossPhase1P6DamageState::~CBossPhase1P6DamageState()
{
}

void CBossPhase1P6DamageState::finaltick()
{
	if (m_fAccTime > m_fDamageTime)
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
			ChangeState(L"BossPhase1P6AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern6_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(BossCount);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 9.6f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
		else
		{
			ChangeState(L"BossPhase1P1AlertState");
			pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern1_ALERT);
			pSelf->GetScript<CBossScript>()->SetPatternCount(2);
			pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		}
	}

	m_fAccTime += DT;
}

void CBossPhase1P6DamageState::Enter()
{
}

void CBossPhase1P6DamageState::Exit()
{
	m_fAccTime = 0.f;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));
}


