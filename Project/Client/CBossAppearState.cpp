#include "pch.h"
#include "CBossAppearState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CCameraScript.h>

CBossAppearState::CBossAppearState()
	: m_fSpeed(1200.f)
	, m_iDir(2)
	, m_fAccTime(0.f)
	, m_fFirstTime(1.2f)
	, m_fSecondTime(3.7f)
	, m_fThirdTime(8.9f)
{
}

CBossAppearState::~CBossAppearState()
{
}
void CBossAppearState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));

	if (m_iDir == 0)
	{
		vPos.x += m_fSpeed * DT;
		vPos.y -= 50.f * DT;
		pSelf->Transform()->SetRelativePos(vPos);
	}
	else if (m_iDir == 1)
	{
		vPos.x += -m_fSpeed * DT;
		vPos.y -= 50.f * DT;
		pSelf->Transform()->SetRelativePos(vPos);
	}


	if (m_fAccTime > m_fFirstTime)
	{
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::APPEAR_SECOND);
		m_fFirstTime = 100.f;
		pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 4.7f, 7.f, CAMERA_SHAKE_TYPE::FOURDIR_TOP);
		pCamera->GetScript<CCameraScript>()->ZoomOutWithTime(0.05f, 4.7f);
		m_iDir = 0;
	}
	else if (m_fAccTime > m_fSecondTime)
	{
		pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::APPEAR_THIRD);
		pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::APPEAR_THIRD);
		m_fSecondTime = 100.f;
		m_iDir = 1;
	}
	else if (m_fAccTime > m_fThirdTime)
	{
		ChangeState(L"BossInitState");
	}



	

	m_fAccTime += DT;


}

void CBossAppearState::Enter()
{
	
}

void CBossAppearState::Exit()
{
	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::BATTLEINIT);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::BATTLEINIT);
	GamePlayStatic::Play2DSound(L"sound\\Boss\\SFX_CHAP1_BossCrash1.wav", 1, 0.1f);

	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 0.2f, 5.f, CAMERA_SHAKE_TYPE::LB_TO_RT);
	pCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.05f, 0.2f);

	m_fAccTime = 0.f;
	m_fSecondTime = 0.f;
	m_fThirdTime = 0.f;
}

