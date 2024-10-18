#include "pch.h"
#include "CTurretAlertState.h"

#include <Engine/CTimeMgr.h>

#include <Scripts/CTurretBodyScript.h>

CTurretAlertState::CTurretAlertState()
	: m_fAlertTime(0.4f)
	, m_fCooldownTime(0.9f)
	, m_fAccTime(0.f)
	, m_prevState(ENEMY_STATE::IDLE)
{
}

CTurretAlertState::~CTurretAlertState()
{
}


void CTurretAlertState::finaltick()
{

	if (m_prevState == ENEMY_STATE::SHOOTING)
	{
		if (m_fAccTime > m_fAlertTime + m_fCooldownTime)
		{
			CGameObject* pBody = GetFSM()->GetStateMachine()->GetOwner()->GetParent();
			pBody->GetScript<CTurretBodyScript>()->SetCurEnemyState(ENEMY_STATE::AIMING);
			ChangeState(L"AimingState");
		}
	}
	else if (m_fAccTime > m_fAlertTime)
	{
		CGameObject* pBody = GetFSM()->GetStateMachine()->GetOwner()->GetParent();
		pBody->GetScript<CTurretBodyScript>()->SetCurEnemyState(ENEMY_STATE::AIMING);
		ChangeState(L"AimingState");
	}


	m_fAccTime += DT;
}

void CTurretAlertState::Enter()
{

}

void CTurretAlertState::Exit()
{
	m_fAccTime = 0.f;
}

