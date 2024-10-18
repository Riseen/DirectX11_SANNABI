#include "pch.h"
#include "CBossRoomSysMgrScript.h"

#include "CBossScript.h"
#include "CCameraScript.h"
#include "CDropRedCargoScript.h"
#include "CFinalCraneHookScript.h"
#include "CBombCargoScript.h"
#include "CDestUIScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CBossRoomSysMgrScript::CBossRoomSysMgrScript()
	: CScript(BOSSROOMSYSMGRSCRIPT)
	, m_CurType(SYSMGR_TYPE::NOT)
	, m_PrevType(SYSMGR_TYPE::NOT)
	, m_fBossSpawnTime(6.f)
	, m_fBossSpawnCameraMoveTime(3.f)
	, m_fAccTime(0.f)
	, m_iPrevBossHP(7)
	, m_bBossSpawn(false)
	, m_bBossCamera(false)
	, m_bBGMCHANGE(false)
{
	AddScriptParam(SCRIPT_PARAM::INT, "CurSYSType", &m_CurType);
}

CBossRoomSysMgrScript::~CBossRoomSysMgrScript()
{
}



void CBossRoomSysMgrScript::begin()
{
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Dest");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CDestUIScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(43.f, 44.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GamePlayStatic::SpawnGameObject(pObj, 3);

	GamePlayStatic::Play2DBGM(L"sound\\BGM\\BGM_Chap1_Boss_Intro.wav", 0.f);


	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pMainCamera->GetScript<CCameraScript>()->CameraMoveDistLock(Vec3(-300.f, -300.f, Transform()->GetRelativePos().z), Vec3(258.f, 143.f, Transform()->GetRelativePos().z));
	
}

void CBossRoomSysMgrScript::tick()
{
	if (m_fAccTime > m_fBossSpawnCameraMoveTime&& !m_bBossCamera)
	{
		m_CurType = SYSMGR_TYPE::BOSSSPAWNCAMERAMOVE;
		m_bBossCamera = true;;
	}
	if (m_fAccTime > m_fBossSpawnTime&& !m_bBossSpawn)
	{
		m_CurType = SYSMGR_TYPE::BOSSSPAWN;
		m_bBossSpawn = true;
	}
	if (m_fAccTime > m_fBossSpawnCameraMoveTime + 120.f && !m_bBGMCHANGE)
	{
		GamePlayStatic::Play2DBGM(L"sound\\BGM\\BGM_Chap1_Boss_Loop.wav", 0.1f);
		m_bBGMCHANGE = true;
	}

	CGameObject* pBoss = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Boss");
	if (pBoss != nullptr)
	{
		if (pBoss->GetScript<CBossScript>()->GetHP() == 3 && m_iPrevBossHP > 3)
		{
			m_CurType = SYSMGR_TYPE::BOMBCARGOSPAWN;
		}
		else if (pBoss->GetScript<CBossScript>()->GetHP() <= 0)
		{
			m_CurType = SYSMGR_TYPE::FINALCRANESPAWN;
		}
	}
	

	SysMgr();

	m_PrevType = m_CurType;
	if (pBoss != nullptr)
		m_iPrevBossHP = pBoss->GetScript<CBossScript>()->GetHP();
	m_fAccTime += DT;
}

void CBossRoomSysMgrScript::SaveToFile(FILE* _File)
{
}

void CBossRoomSysMgrScript::LoadFromFile(FILE* _File)
{
}


void CBossRoomSysMgrScript::SysMgr()
{
	if (m_CurType == m_PrevType)
		return;

	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

	
	switch (m_CurType)
	{
	case SYSMGR_TYPE::NOT:
		break;
	case SYSMGR_TYPE::BOSSSPAWNCAMERAMOVE:
	{
		GamePlayStatic::Play2DBGM(L"sound\\BGM\\BGM_Chap1_Boss_Intro.wav", 0.1f);
		pMainCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 3.f, 1.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.05f, 3.f);
	}
		break;
	case SYSMGR_TYPE::BOSSSPAWN:
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"Boss");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CStateMachine);
		pObj->AddComponent(new CBossScript);

		pObj->Transform()->SetRelativePos(Vec3(218.f, -261.f, 575.f));
		pObj->Transform()->SetRelativeScale(Vec3(651.f, 688.f, 1.f));


		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

		pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"BOSSFSM"));

		GamePlayStatic::SpawnGameObject(pObj, 21);
	}
		break;
	case SYSMGR_TYPE::LEFTCARGOSPAWN:
		{
			CGameObject* pObj = new CGameObject;
			pObj->SetName(L"LEFTCARGO");

			pObj->AddComponent(new CTransform);
			pObj->AddComponent(new CMeshRender);
			pObj->AddComponent(new CAnimator2D);
			pObj->AddComponent(new CDropRedCargoScript);

			pObj->Transform()->SetRelativePos(Vec3(-540.f, 55.f, 491.f));
			pObj->Transform()->SetRelativeScale(Vec3(670.f, 367.f, 1.f));

			pObj->GetScript<CDropRedCargoScript>()->SetDir(0);

			pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
			pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

			GamePlayStatic::SpawnGameObject(pObj, 23);
		}
		break;
	case SYSMGR_TYPE::RIGHTCARGOSPAWN:
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"RIGHTCARGO");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);		
		pObj->AddComponent(new CDropRedCargoScript);

		pObj->Transform()->SetRelativePos(Vec3(540.f, 55.f, 491.f));
		pObj->Transform()->SetRelativeScale(Vec3(670.f, 367.f, 1.f));

		pObj->GetScript<CDropRedCargoScript>()->SetDir(1);

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 23);
	}
		break;
	case SYSMGR_TYPE::SPAWNDOUBLE:
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"LEFTCARGO");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CDropRedCargoScript);

		pObj->Transform()->SetRelativePos(Vec3(-540.f, 55.f, 491.f));
		pObj->Transform()->SetRelativeScale(Vec3(670.f, 367.f, 1.f));

		pObj->GetScript<CDropRedCargoScript>()->SetDir(0);

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 23);

		pObj = new CGameObject;
		pObj->SetName(L"RIGHTCARGO");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CDropRedCargoScript);

		pObj->Transform()->SetRelativePos(Vec3(540.f, 55.f, 491.f));
		pObj->Transform()->SetRelativeScale(Vec3(670.f, 367.f, 1.f));

		pObj->GetScript<CDropRedCargoScript>()->SetDir(1);

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 23);
	}
		break;
	case SYSMGR_TYPE::BOMBCARGOSPAWN:
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"BOMBCARGO");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CBombCargoScript);

		pObj->Transform()->SetRelativePos(Vec3(0.f, -261.f, 491.f));
		pObj->Transform()->SetRelativeScale(Vec3(450.f, 342.1f, 1.f));

		pObj->GetScript<CBombCargoScript>()->SetStartPos(Vec3(0.f, 100.f, 500.f));
		pObj->GetScript<CBombCargoScript>()->SetEndPos(Vec3(0.f, -400.f, 500.f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 23);
	}
		break;
	case SYSMGR_TYPE::FINALCRANESPAWN:
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"FNCRANE");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CCollider2D);
		pObj->AddComponent(new CFinalCraneHookScript);

		pObj->Transform()->SetRelativePos(Vec3(0.f, 600.f, 491.f));
		pObj->Transform()->SetRelativeScale(Vec3(390.f, 600.f, 1.f));

		pObj->Collider2D()->SetOffsetScale(Vec2(0.25f, 0.8f));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

		GamePlayStatic::SpawnGameObject(pObj, 22);
	}
		break;
	default:
		break;
	}
}
