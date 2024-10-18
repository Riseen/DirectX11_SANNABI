#include "pch.h"
#include "CGameSystemMgrScript.h"

#include "CLevelChangeEventColScript.h"
#include "CDeathColScript.h"
#include "CCameraScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

LEVEL_LOAD CGameSystemMgrScript::levelLoad = nullptr;

CGameSystemMgrScript::CGameSystemMgrScript()
	: CScript(GAMESYSTEMMGRSCRIPT)
	, m_pEventCol {}
{
}

CGameSystemMgrScript::~CGameSystemMgrScript()
{
}

CLevel* CGameSystemMgrScript::LoadLevel(const wstring& _strFilePath)
{
	return (levelLoad(_strFilePath));
}

void CGameSystemMgrScript::begin()
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pMainCamera->GetScript<CCameraScript>()->CameraMoveDistLock(Vec3(-4016.f, -4338.f, Transform()->GetRelativePos().z), Vec3(3620.f, 2603.f, Transform()->GetRelativePos().z));


		for (int i = 0; i < 5; ++i)
		{
			m_pEventCol[i] = new CGameObject;
			m_pEventCol[i]->SetName(L"EventCol");

			m_pEventCol[i]->AddComponent(new CTransform);
			m_pEventCol[i]->AddComponent(new CCollider2D);
			m_pEventCol[i]->AddComponent(new CEventColScript);

			m_pEventCol[i]->Transform()->SetRelativeScale(Vec3(100.f, 500.f, 1.f));

			m_pEventCol[i]->Collider2D()->SetOffsetScale(Vec2(1.f,1.f));

			GamePlayStatic::SpawnGameObject(m_pEventCol[i], 14);
		}

		m_pEventCol[0]->Transform()->SetRelativePos(Vec3(-1632.f, -3967.f, 500.f));
		m_pEventCol[1]->Transform()->SetRelativePos(Vec3(-421.f, -3730.f, 500.f));
		m_pEventCol[2]->Transform()->SetRelativePos(Vec3(490.f, -2000.f, 500.f));
		m_pEventCol[3]->Transform()->SetRelativePos(Vec3(-1550.f, -694.f, 500.f));
		m_pEventCol[4]->Transform()->SetRelativePos(Vec3(1181.f, 1689.f, 500.f));


		m_pEventCol[0]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(-1514.f, -3540.f, 500.f), SPAWN_DIR::UP, ENEMY_TYPE::TURRET);
		m_pEventCol[0]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(-501.f, -4285.f, 500.f), SPAWN_DIR::LEFT, ENEMY_TYPE::TURRET);

		m_pEventCol[1]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(500.f, -3847.f, 500.f), SPAWN_DIR::UP, ENEMY_TYPE::DEFENDER);

		m_pEventCol[2]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(-739.f, -1770.f, 500.f), SPAWN_DIR::DOWN, ENEMY_TYPE::TURRET);
		m_pEventCol[3]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(-2476.f, -404.f, 500.f), SPAWN_DIR::DOWN, ENEMY_TYPE::TURRET);

		m_pEventCol[4]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(1172.f, 1980.f, 500.f), SPAWN_DIR::RIGHT, ENEMY_TYPE::TURRET);
		m_pEventCol[4]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(2282.f, 1689.f, 500.f), SPAWN_DIR::LEFT, ENEMY_TYPE::TURRET);
		m_pEventCol[4]->GetScript<CEventColScript>()->SetSpawnInfo(Vec3(2505.f, 2329.f, 500.f), SPAWN_DIR::DOWN, ENEMY_TYPE::DEFENDER);

		GamePlayStatic::Play2DBGM(L"sound\\BGM\\BGM_Chap1_MainAlt_Loop.wav", 0.1f);

		
}

void CGameSystemMgrScript::tick()
{
}

void CGameSystemMgrScript::SaveToFile(FILE* _File)
{
}

void CGameSystemMgrScript::LoadFromFile(FILE* _File)
{
}



