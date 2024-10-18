#include "pch.h"
#include "CBossPhase2P2MovingState.h"

#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>

CBossPhase2P2MovingState::CBossPhase2P2MovingState()
	: m_fSpeed(400.f)
	, m_fMaxDist(1650.f)
{
}

CBossPhase2P2MovingState::~CBossPhase2P2MovingState()
{
}

void CBossPhase2P2MovingState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	static Vec3 vStartPos = vPos;
	Vec3 vCurDist = vStartPos - vPos;

	if (vCurDist.Length() > m_fMaxDist)
	{
		ChangeState(L"BossPhase2P2DownState");
	}
	vPos.x += m_fSpeed * DT;

	pSelf->Transform()->SetRelativePos(vPos);
}

void CBossPhase2P2MovingState::Enter()
{
}

void CBossPhase2P2MovingState::Exit()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern2_DOWN);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern2_DOWN);
}


