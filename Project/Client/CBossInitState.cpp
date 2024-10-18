#include "pch.h"
#include "CBossInitState.h"

#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>
#include <Scripts/CBossRoomSysMgrScript.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CBossInitState::CBossInitState()
	: m_InitTime(2.4f)
	, m_fRunTime(2.4f)
	, m_fAccTime(0.f)
	, m_bInit(false)
	, m_bRun(false)
{
}

CBossInitState::~CBossInitState()
{
}


void CBossInitState::finaltick()
{
	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));

	if (m_fAccTime > m_InitTime && !m_bInit)
	{
		m_bInit = true;
		pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, m_fRunTime, 15.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);

	}
	if (m_fAccTime > m_InitTime + m_fRunTime && !m_bRun)
	{
		m_bRun = true;

		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::BATTLEINIT_END);
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::BATTLEINIT_END);
		pCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.05f, 0.2f);
	}
	if (m_fAccTime > m_InitTime + m_fRunTime + 2.4f)
	{
		ChangeState(L"BossPhase1P1AlertState");
	}


	m_fAccTime += DT;

}

void CBossInitState::Enter()
{
	
}

void CBossInitState::Exit()
{
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_Pattern1_ALERT);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_Pattern1_ALERT);

	CGameObject* pSysMgr = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"BossSysMgr");
	pSysMgr->GetScript<CBossRoomSysMgrScript>()->SetSysType(SYSMGR_TYPE::SPAWNDOUBLE);

	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);


	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();

	pSelf->Transform()->SetRelativePos(Vec3(vTargetPos.x, vPos.y, vPos.z));

	m_fAccTime = 0.f;
	m_bInit = false;
	m_bRun = false;
}

