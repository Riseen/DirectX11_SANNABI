#include "pch.h"
#include "CBombMoveState.h"

#include <Scripts/CBombScript.h>
#include <Scripts/CPlayerScript.h>

CBombMoveState::CBombMoveState()
	: m_fDist(30.f)
{
}

CBombMoveState::~CBombMoveState()
{
}

void CBombMoveState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	if (pTarget->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::DEATH)
		return;

	Vec3 vDir = pTarget->Transform()->GetWorldPos() - pSelf->Transform()->GetWorldPos();

	if (vDir.Length() < m_fDist)
	{
		ChangeState(L"BombExplodeReadyState");
	}


	vDir.Normalize();

	Vec3 vPos = pSelf->Transform()->GetWorldPos();

	vPos += vDir * DT * 300.f;

	pSelf->Transform()->SetRelativePos(vPos);
}

void CBombMoveState::Enter()
{
}

void CBombMoveState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBombScript>()->SetBombState(DefenderBOMB_STATE::EXPLODE_READY);
}


