#include "pch.h"
#include "CBossPhase2P2AlertState.h"

#include <Scripts/CBossP2AlertScript.h>
#include <Scripts/CBossScript.h>
#include <Engine/CTimeMgr.h>
#include <Scripts/CCameraScript.h>

CBossPhase2P2AlertState::CBossPhase2P2AlertState()
	: m_iCol(26)
	, m_iAlertCount(0)
	, m_fTerm(0.04f)
	, m_fAccTime(0.f)
{
}

CBossPhase2P2AlertState::~CBossPhase2P2AlertState()
{
}

void CBossPhase2P2AlertState::finaltick()
{
	if (m_iAlertCount < m_iCol && m_fAccTime > m_fTerm)
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"P2Alert");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CBossP2AlertScript);

		pObj->Transform()->SetRelativePos(Vec3(-950.f + (75.f * m_iAlertCount), -300.f, 500.f));
		pObj->Transform()->SetRelativeScale(Vec3(400.f, 1000.f, 1.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 1);

		m_fAccTime = 0.f;

		m_iAlertCount++;
	}
	else if (m_iAlertCount >= m_iCol)
	{
		ChangeState(L"BossPhase2P2MovingState");
	}

	m_fAccTime += DT;
}

void CBossPhase2P2AlertState::Enter()
{
}

void CBossPhase2P2AlertState::Exit()
{
	m_fAccTime = 0.f;
	m_iAlertCount = 0;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	pSelf->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase2_Pattern2_MOVING);
	pSelf->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase2_Pattern2_MOVING);
	Vec3 vPos = pSelf->Transform()->GetRelativePos();
	pSelf->Transform()->SetRelativePos(Vec3(-1200.f, vPos.y, vPos.z));

	CGameObject* pCamera = ((CGameObject*)GetBlackboardData(L"Camera"));
	pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 2.5f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);

	GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossPopUpPattern2.wav", 1, 0.1f);
}


