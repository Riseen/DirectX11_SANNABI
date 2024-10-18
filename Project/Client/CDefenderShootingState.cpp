#include "pch.h"
#include "CDefenderShootingState.h"

#include <Scripts/CBombScript.h>
#include <Scripts/CDefendScript.h>
#include <Scripts/CPlayerScript.h>
#include <Engine/CTimeMgr.h>

CDefenderShootingState::CDefenderShootingState()
	: m_Bomb(nullptr)
	, m_fAttackTime(1.5f)
	, m_fAccTime(0.f)
{
}

CDefenderShootingState::~CDefenderShootingState()
{
}


void CDefenderShootingState::finaltick()
{
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));

	if (pTarget->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::DEATH)
		return;

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();
	Vec3 vPos = pSelf->Transform()->GetRelativePos();

	if (pSelf->GetScript<CDefendScript>()->GetCurState() == ENEMY_STATE::HOLDING)
	{
		ChangeState(L"EnemyHoldingState");
	}

	static bool bAiming = false;

	if(m_fAccTime > m_fAttackTime)
	{
		if (m_Bomb == nullptr)
		{
			

			m_Bomb = new CGameObject;
			m_Bomb->SetName(L"BombBot");

			m_Bomb->AddComponent(new CTransform);
			m_Bomb->AddComponent(new CMeshRender);
			m_Bomb->AddComponent(new CAnimator2D);
			m_Bomb->AddComponent(new CBombScript);
			m_Bomb->AddComponent(new CStateMachine);

			m_Bomb->Transform()->SetRelativePos(Vec3(vPos.x, vPos.y + 40.f, vPos.z));
			m_Bomb->Transform()->SetRelativeScale(Vec3(256.f, 211.f, 1.f));

			m_Bomb->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			m_Bomb->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

			m_Bomb->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"BombFSM"));

			GamePlayStatic::SpawnGameObject(m_Bomb, 21);

			
			//pSelf->AddChild(m_Bomb);
			pSelf->GetScript<CDefendScript>()->SetCurEnemyState(ENEMY_STATE::ALERT);

			bAiming = true;
		}
		else if (m_Bomb != nullptr && m_Bomb->GetName() == L"BombBot" && m_Bomb->GetScript<CBombScript>()->IsDead() && bAiming)
		{
			m_Bomb = nullptr;

			
			Vec3 vTargetPos = pTarget->Transform()->GetRelativePos();

			if (vTargetPos.x >= vPos.x)
				pSelf->GetScript<CDefendScript>()->SetLp(true);
			else
				pSelf->GetScript<CDefendScript>()->SetLp(false);


			pSelf->GetScript<CDefendScript>()->SetCurEnemyState(ENEMY_STATE::SHOOTING);
			m_fAccTime = 0.f;

			bAiming = false;
		}
	}

	m_fAccTime += DT;
}

void CDefenderShootingState::Enter()
{
}

void CDefenderShootingState::Exit()
{
	m_Bomb = nullptr;
	m_fAccTime = 0.f;
}

