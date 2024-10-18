#include "pch.h"
#include "CTurretShotState.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CGameObject.h>
#include <Engine/CTransform.h>
#include <Engine/CCollider2D.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CMeshRender.h>
#include <Scripts/CBulletScript.h>
#include <Scripts/CTurretBodyScript.h>
#include <Scripts/CTurretGunScript.h>
#include <Scripts/CPlayerScript.h>


CTurretShotState::CTurretShotState()
	: m_fTerm(0.1f)
	, m_fCurAccTime(0.f)
	, m_iBulletCount(10)
{
}

CTurretShotState::~CTurretShotState()
{
}


void CTurretShotState::finaltick()
{
	m_fCurAccTime += DT;

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));

	if (pTarget->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::DEATH)
		return;


	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();

	Vec3 vDir = pTarget->Transform()->GetWorldPos() - pSelf->Transform()->GetWorldPos();
	vDir.Normalize();

	Vec3 v1 = pTarget->Transform()->GetWorldPos();
	Vec3 v = pSelf->Transform()->GetWorldPos();
	

	Vec3 vT = pSelf->GetScript<CTurretGunScript>()->GetShotPos();

	if (m_fTerm < m_fCurAccTime)
	{
		// 추후 프리펩으로 생성

		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"Bullet");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CCollider2D);
		pObj->AddComponent(new CBulletScript);

		pObj->Transform()->SetRelativePos(Vec3(v.x + pSelf->GetScript<CTurretGunScript>()->GetShotPos().x,
			v.y + pSelf->GetScript<CTurretGunScript>()->GetShotPos().y,
			500.f));
		pObj->Transform()->SetRelativeScale(Vec3(100.f, 100.f, 1.f));

		pObj->GetScript<CBulletScript>()->SetDir(vDir);

		pObj->Collider2D()->SetAbsolute(true);
		pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));


		GamePlayStatic::SpawnGameObject(pObj, 12);
		GamePlayStatic::Play2DSound(L"sound//Enemy//SFX_Ene_Turret_Shot (1).wav", 1, 0.1f, true);

		m_iBulletCount--;
		m_fCurAccTime = 0.f;
	}
	if (m_iBulletCount <= 0)
	{
		m_iBulletCount = 10;
		CGameObject* pBody = GetFSM()->GetStateMachine()->GetOwner()->GetParent();
		pBody->GetScript<CTurretBodyScript>()->SetCurEnemyState(ENEMY_STATE::ALERT);
		ChangeState(L"AlertState");
	}
}

void CTurretShotState::Enter()
{
	
}

void CTurretShotState::Exit()
{
	m_fCurAccTime = 0.f;
}

