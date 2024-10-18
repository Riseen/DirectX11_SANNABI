#include "pch.h"
#include "CBombExplodeReadyState.h"

#include <Engine/CTimeMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Scripts/CBombScript.h>
#include <Scripts/CPlayerScript.h>

CBombExplodeReadyState::CBombExplodeReadyState()
	: m_Col(nullptr)
	, m_fExplodeTime(3.f)
	, m_fAccTime(0.f)
	, m_fSoundTime(0.6f)
	, m_fSoundAccTime(0.f)
{
}

CBombExplodeReadyState::~CBombExplodeReadyState()
{
}

void CBombExplodeReadyState::finaltick()
{
	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();

	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));
	if (pTarget->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::DEATH)
		return;

	if(m_fSoundAccTime > m_fSoundTime)
	{
		GamePlayStatic::Play2DSound(L"sound\\Enemy\\SFX_Chap1_FlyingBomb_Alert.wav", 1, 0.5f);
		m_fSoundAccTime = 0.f;
	}
	

	if (m_fAccTime > m_fExplodeTime + 0.4f)
	{
		GamePlayStatic::DestroyGameObject(m_Col);
		m_Col = nullptr;
		pSelf->GetScript<CBombScript>()->SetDead(true);
		m_fAccTime = 0.f;
	}
	else if (m_fAccTime > m_fExplodeTime)
	{
		pSelf->GetScript<CBombScript>()->SetBombState(DefenderBOMB_STATE::EXPLODE);
		Vec3 vPos = pSelf->Transform()->GetWorldPos();

		if (m_Col == nullptr)
		{
			m_Col = new CGameObject;
			m_Col->SetName(L"ExCol");

			m_Col->AddComponent(new CTransform);
			m_Col->AddComponent(new CCollider2D);

			m_Col->Transform()->SetRelativePos(Vec3(vPos));

			pSelf->Transform()->SetRelativeScale(Vec3(640.f, 640.f, 1.f));
			m_Col->Collider2D()->SetOffsetScale(Vec2(100.f, 100.f));

			

			GamePlayStatic::SpawnGameObject(m_Col, 12);
		}
	}
	else
	{
		CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
		

		Vec3 vDir = pTarget->Transform()->GetWorldPos() - pSelf->Transform()->GetWorldPos();

		vDir.Normalize();

		Vec3 vPos = pSelf->Transform()->GetWorldPos();

		vPos += vDir * DT * 300.f;

		pSelf->Transform()->SetRelativePos(vPos);
	}

	m_fAccTime += DT;
	m_fSoundAccTime += DT;
}

void CBombExplodeReadyState::Enter()
{
}

void CBombExplodeReadyState::Exit()
{
	m_fAccTime = 0.f;

}


