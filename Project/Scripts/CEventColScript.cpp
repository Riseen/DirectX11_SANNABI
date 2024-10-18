#include "pch.h"
#include "CEventColScript.h"

#include "CDefendScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>


CEventColScript::CEventColScript()
	: CScript(EVENTCOLSCRIPT)
	, m_bSpawn(false)
{
}

CEventColScript::~CEventColScript()
{
}



void CEventColScript::begin()
{
}

void CEventColScript::tick()
{
	
}

void CEventColScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (m_bSpawn)
		return;

	Spawn();

	m_bSpawn = true;
}

void CEventColScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CEventColScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CEventColScript::SaveToFile(FILE* _File)
{
}

void CEventColScript::LoadFromFile(FILE* _File)
{
}

void CEventColScript::Spawn()
{
	for (size_t i = 0; i < m_SpawnEnemy.size(); ++i)
	{
		if (m_SpawnEnemy[i].m_Type == ENEMY_TYPE::TURRET)
		{
			CGameObject* pObj = new CGameObject;
			pObj->SetName(L"Turret");

			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->AddComponent(new CAnimator2D);
			pObj->AddComponent(new CCollider2D);
			pObj->AddComponent(new CTurretBodyScript);

			pObj->Transform()->SetRelativePos(m_SpawnEnemy[i].m_vSpawnPos);
			pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

			pObj->Collider2D()->SetAbsolute(true);
			pObj->Collider2D()->SetOffsetScale(Vec2(87.f, 120.f));
			pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 15.f));

			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

			pObj->GetScript<CTurretBodyScript>()->SetSpawnDir(m_SpawnEnemy[i].m_Dir);

			GamePlayStatic::SpawnGameObject(pObj, 8);
		}
		else if (m_SpawnEnemy[i].m_Type == ENEMY_TYPE::DEFENDER)
		{
			CGameObject* pObj = new CGameObject;
			pObj->SetName(L"Defender");

			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->AddComponent(new CAnimator2D);
			pObj->AddComponent(new CCollider2D);
			pObj->AddComponent(new CStateMachine);
			pObj->AddComponent(new CDefendScript);

			pObj->Transform()->SetRelativePos(m_SpawnEnemy[i].m_vSpawnPos);
			pObj->Transform()->SetRelativeScale(Vec3(400.f, 400.f, 1.f));

			pObj->Collider2D()->SetAbsolute(true);
			pObj->Collider2D()->SetOffsetScale(Vec2(60.f, 120.f));
			pObj->Collider2D()->SetOffsetPos(Vec2(-25.f, 0.f));

			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

			pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"DefenderFSM"));

			GamePlayStatic::SpawnGameObject(pObj, 8);
		}
	}

}

void CEventColScript::SetSpawnInfo(Vec3 _vSpawnPos, SPAWN_DIR _Dir, ENEMY_TYPE _type)
{
	SpawnEnemy SpawnEnemy;
	SpawnEnemy.m_vSpawnPos = _vSpawnPos;
	SpawnEnemy.m_Type = _type;
	SpawnEnemy.m_Dir = _Dir;

	m_SpawnEnemy.push_back(SpawnEnemy);
}
