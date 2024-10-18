#include "pch.h"
#include "CTurretAimingState.h"

#include <Engine/CGameObject.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>
#include <Engine/CTimeMgr.h>

#include <Scripts/CAimmingRayScript.h>
#include <Scripts/CTurretBodyScript.h>


CTurretAimingState::CTurretAimingState()
	: m_fAimmingTime (3.f)
	, m_fCurAccTime (0.f)
	, m_pRay(nullptr)
{
	
}

CTurretAimingState::~CTurretAimingState()
{
	//delete m_pRay;
}

void CTurretAimingState::finaltick()
{
	
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();

	Vec3 vDir = pTarget->Transform()->GetWorldPos() - pSelf->Transform()->GetWorldPos();
	vDir.Normalize();

	m_fCurAccTime += DT;

	if (m_fAimmingTime < m_fCurAccTime)
	{
		
		CGameObject* pBody = GetFSM()->GetStateMachine()->GetOwner()->GetParent();
		pBody->GetScript<CTurretBodyScript>()->SetCurEnemyState(ENEMY_STATE::SHOOTING);
		ChangeState(L"ShotState");
	}
}

void CTurretAimingState::Enter()
{

}

void CTurretAimingState::Exit()
{
	m_fCurAccTime = 0.f;
}



