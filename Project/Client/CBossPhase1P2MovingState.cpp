#include "pch.h"
#include "CBossPhase1P2MovingState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase1P2MovingState::CBossPhase1P2MovingState()
	: m_fSpeed(400.f)
	, m_fMaxDist(1650.f)
{
}

CBossPhase1P2MovingState::~CBossPhase1P2MovingState()
{
}

void CBossPhase1P2MovingState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	static Vec3 vStartPos = vPos;
	Vec3 vCurDist = vStartPos - vPos;

	if (vCurDist.Length() > m_fMaxDist)
	{
		ChangeState(L"BossPhase1P2DownState");
	} 
	vPos.x += m_fSpeed * DT;

	pSelf->Transform()->SetRelativePos(vPos);
}

void CBossPhase1P2MovingState::Enter()
{
}

void CBossPhase1P2MovingState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern2_DOWN);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern2_DOWN);
}


