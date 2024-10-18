#include "pch.h"
#include "CCreateTempLevel.h"


#include <Engine/CCollisionMgr.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>

#include <Scripts/CPlayerScript.h>
#include <Scripts/CBackgroundScript.h>

#include <Engine/CMesh.h>
#include <Engine/CGraphicsShader.h>
#include <Engine/CTexture.h>
#include <Engine/CSetColorShader.h>

#include "CLevelSaveLoad.h"
#include <Scripts/CRedCargoScript.h>
#include <Scripts/CArmScript.h>
#include <Scripts/CCameraScript.h>
#include <Scripts/CCursorScript.h>
#include <Scripts/CGrabScript.h>
#include <Scripts/CTurretBodyScript.h>
#include <Scripts/CDefendScript.h>
#include <Scripts/CBossScript.h>
#include <Scripts/CBombCargoScript.h>
#include <Scripts/CFinalCraneHookScript.h>
#include <Scripts/CDestUIScript.h>
#include <Scripts/CChainScript.h>
#include <Scripts/CLayerMgrScript.h>
#include <Scripts/CGameSystemMgrScript.h>
#include <Scripts/CGamePlayBGScript.h>
#include <Scripts/CButtonScript.h>

#include <Scripts/CMainLogoUI.h>
#include <Scripts/CMenuUIScript.h>
#include <Scripts/CMainUIScript.h>

#include <Engine/CAssetMgr.h>
#include <Engine/CPrefab.h>
#include <Engine/CFSM.h>

#include "CIdleState.h"
#include "CTurretAimingState.h"
#include "CTurretShotState.h"
#include "CTurretAlertState.h"
#include "CDefenderShootingState.h"
#include "CEnemyHoldingState.h"

#include "CBombMoveState.h"
#include "CBombExplodeReadyState.h"

#include "CBossAppearState.h"
#include "CBossInitState.h"
#include "CBossPhase1P1AlertState.h"
#include "CBossPhase1P1IdleState.h"
#include "CBossPhase1P1DownState.h"
#include "CBossPhase1P1DamageState.h"
#include "CBossPhase1P1ExcHoldedState.h"

#include "CBossPhase1P2AlertState.h"
#include "CBossPhase1P2DownState.h"
#include "CBossPhase1P2MovingState.h"

#include "CBossPhase1P6AlertState.h"
#include "CBossPhase1P6DamageState.h"
#include "CBossPhase1P6DownState.h"
#include "CBossPhase1P6ExcHoldedState.h"
#include "CBossPhase1P6GroggyState.h"
#include "CBossPhase1P6MovingState.h"

#include "CBossPhase1PLAlertState.h"
#include "CBossPhase1PLDownState.h"
#include "CBossPhase1PLIdleState.h"
#include "CBossPhase1PLEndState.h"

#include "CBossPhase2P1AlertState.h"
#include "CBossPhase2P1IdleState.h"
#include "CBossPhase2P1DownState.h"
#include "CBossPhase2P1DamageState.h"
#include "CBossPhase2P1ExcHoldedState.h"

#include "CBossPhase2P2AlertState.h"
#include "CBossPhase2P2DownState.h"
#include "CBossPhase2P2MovingState.h"

#include "CBossPhase2P6AlertState.h"
#include "CBossPhase2P6DamageState.h"
#include "CBossPhase2P6DownState.h"
#include "CBossPhase2P6ExcHoldedState.h"
#include "CBossPhase2P6GroggyState.h"
#include "CBossPhase2P6MovingState.h"

#include "CBossPhase2PLAlertState.h"
#include "CBossPhase2PLDownState.h"
#include "CBossPhase2PLIdleState.h"

#include "C1stHookedState.h"
#include "C2ndHookedState.h"
#include "C3rdHookedState.h"
#include "CBeforePoundingState.h"
#include "C1stPoundingState.h"
#include "C2ndPoundingState.h"
#include "C3rdBeforePoundingState.h"
#include "C3rdPoundingState.h"
#include "CBeforeExctionState.h"
#include "CExctionState.h"
#include "CAfterExectionState.h"

#include "CBossPhase1PNState.h"

void CCreateTempLevel::Init()
{
	// Missile Prefab 생성
	/*CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"Missile");
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMissileScript);

	pObj->Transform()->SetRelativeScale(Vec3(50.f, 50.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	Ptr<CPrefab> pMissilePrefab = new CPrefab(pObj);
	CAssetMgr::GetInst()->AddAsset<CPrefab>(L"MissilePrefab", pMissilePrefab.Get());
	

	pMissilePrefab->Save(L"prefab\\missile.pref");*/
	

	// 임시 FSM 객체 에셋 하나 생성하기
	Ptr<CFSM>	pFSM = new CFSM(true);
	
	pFSM->AddState(L"IdleState", new CIdleState);
	pFSM->AddState(L"EnemyHoldingState", new CEnemyHoldingState);
	pFSM->AddState(L"AimingState", new CTurretAimingState);
	pFSM->AddState(L"ShotState", new CTurretShotState);
	pFSM->AddState(L"AlertState", new CTurretAlertState);
	
	
	CAssetMgr::GetInst()->AddAsset<CFSM>(L"TurretFSM", pFSM.Get());

	pFSM = new CFSM(true);
	pFSM->AddState(L"IdleState", new CIdleState);
	pFSM->AddState(L"EnemyHoldingState", new CEnemyHoldingState);
	pFSM->AddState(L"DefenderShootingState", new CDefenderShootingState);


	CAssetMgr::GetInst()->AddAsset<CFSM>(L"DefenderFSM", pFSM.Get());

	pFSM = new CFSM(true);
	pFSM->AddState(L"BombMoveState", new CBombMoveState);
	pFSM->AddState(L"BombExplodeReadyState", new CBombExplodeReadyState);

	CAssetMgr::GetInst()->AddAsset<CFSM>(L"BombFSM", pFSM.Get());

	pFSM = new CFSM(true);
	pFSM->AddState(L"IdleState", new CIdleState);
	pFSM->AddState(L"BossAppearState", new CBossAppearState);
	pFSM->AddState(L"BossInitState", new CBossInitState);

	pFSM->AddState(L"BossPhase1P1AlertState", new CBossPhase1P1AlertState);
	pFSM->AddState(L"BossPhase1P1IdleState", new CBossPhase1P1IdleState);
	pFSM->AddState(L"BossPhase1P1DamageState", new CBossPhase1P1DamageState);
	pFSM->AddState(L"BossPhase1P1DownState", new CBossPhase1P1DownState);
	pFSM->AddState(L"BossPhase1P1ExcHoldedState", new CBossPhase1P1ExcHoldedState);

	pFSM->AddState(L"BossPhase1P2AlertState", new CBossPhase1P2AlertState);
	pFSM->AddState(L"BossPhase1P2DownState", new CBossPhase1P2DownState);
	pFSM->AddState(L"BossPhase1P2MovingState", new CBossPhase1P2MovingState);

	pFSM->AddState(L"BossPhase1P6AlertState", new CBossPhase1P6AlertState);
	pFSM->AddState(L"BossPhase1P6DamageState", new CBossPhase1P6DamageState);
	pFSM->AddState(L"BossPhase1P6DownState", new CBossPhase1P6DownState);
	pFSM->AddState(L"BossPhase1P6ExcHoldedState", new CBossPhase1P6ExcHoldedState);
	pFSM->AddState(L"BossPhase1P6GroggyState", new CBossPhase1P6GroggyState);
	pFSM->AddState(L"BossPhase1P6MovingState", new CBossPhase1P6MovingState);

	pFSM->AddState(L"BossPhase1PLAlertState", new CBossPhase1PLAlertState);
	pFSM->AddState(L"BossPhase1PLDownState", new CBossPhase1PLDownState);
	pFSM->AddState(L"BossPhase1PLIdleState", new CBossPhase1PLIdleState);
	pFSM->AddState(L"BossPhase1PLEndState", new CBossPhase1PLEndState);

	pFSM->AddState(L"BossPhase2P1AlertState", new CBossPhase2P1AlertState);
	pFSM->AddState(L"BossPhase2P1IdleState", new CBossPhase2P1IdleState);
	pFSM->AddState(L"BossPhase2P1DamageState", new CBossPhase2P1DamageState);
	pFSM->AddState(L"BossPhase2P1DownState", new CBossPhase2P1DownState);
	pFSM->AddState(L"BossPhase2P1ExcHoldedState", new CBossPhase2P1ExcHoldedState);

	pFSM->AddState(L"BossPhase2P2AlertState", new CBossPhase2P2AlertState);
	pFSM->AddState(L"BossPhase2P2DownState", new CBossPhase2P2DownState);
	pFSM->AddState(L"BossPhase2P2MovingState", new CBossPhase2P2MovingState);

	pFSM->AddState(L"BossPhase2P6AlertState", new CBossPhase2P6AlertState);
	pFSM->AddState(L"BossPhase2P6DamageState", new CBossPhase2P6DamageState);
	pFSM->AddState(L"BossPhase2P6DownState", new CBossPhase2P6DownState);
	pFSM->AddState(L"BossPhase2P6ExcHoldedState", new CBossPhase2P6ExcHoldedState);
	pFSM->AddState(L"BossPhase2P6GroggyState", new CBossPhase2P6GroggyState);
	pFSM->AddState(L"BossPhase2P6MovingState", new CBossPhase2P6MovingState);

	pFSM->AddState(L"BossPhase2PLAlertState", new CBossPhase2PLAlertState);
	pFSM->AddState(L"BossPhase2PLDownState", new CBossPhase2PLDownState);
	pFSM->AddState(L"BossPhase2PLIdleState", new CBossPhase2PLIdleState);

	pFSM->AddState(L"1stHookedState", new C1stHookedState);
	pFSM->AddState(L"2ndHookedState", new C2ndHookedState);
	pFSM->AddState(L"3rdHookedState", new C3rdHookedState);
	pFSM->AddState(L"BeforePoundingState", new CBeforePoundingState);
	pFSM->AddState(L"1stPoundingState", new C1stPoundingState);
	pFSM->AddState(L"2ndPoundingState", new C2ndPoundingState);
	pFSM->AddState(L"3rdBeforePoundingState", new C3rdBeforePoundingState);
	pFSM->AddState(L"3rdPoundingState", new C3rdPoundingState);
	pFSM->AddState(L"BeforeExctionState", new CBeforeExctionState);
	pFSM->AddState(L"ExctionState", new CExctionState);
	pFSM->AddState(L"AfterExectionState", new CAfterExectionState);

	pFSM->AddState(L"BossPhase1PNState", new CBossPhase1PNState);


	CAssetMgr::GetInst()->AddAsset<CFSM>(L"BOSSFSM", pFSM.Get());
}

void CCreateTempLevel::CreateTempLevel()
{		
	/*Ptr<CMaterial> pBackgroudMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl");
	Ptr<CMaterial> pStd2DMtrl = CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl");

	pBackgroudMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Background.jpg", L"texture\\Background.jpg"));
	pStd2DMtrl->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));*/

	/*CLevel* pLevel = CLevelSaveLoad::LoadLevel(L"level\\temp.lv");
	CLevelMgr::GetInst()->ChangeLevel(pLevel, LEVEL_STATE::STOP);
	return;*/


	CLevel* pTempLevel = new CLevel;
	
	//ShowCursor(false);
	
	
	// Main Camera Object 생성
	CGameObject* pCamObj = new CGameObject;
	pCamObj->SetName(L"MainCamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	pCamObj->AddComponent(new CCameraScript);
	
	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	
	pCamObj->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pCamObj->Camera()->SetCameraPriority(0);
	pCamObj->Camera()->LayerCheckAll();
	pCamObj->Camera()->LayerCheck(31, false);
	
	pTempLevel->AddObject(pCamObj, 0);
	
	// UI 카메라 생성
	pCamObj = new CGameObject;
	pCamObj->SetName(L"UICamera");
	pCamObj->AddComponent(new CTransform);
	pCamObj->AddComponent(new CCamera);
	
	pCamObj->Transform()->SetRelativePos(Vec3(0.5f, 0.f, 0.f));
	pCamObj->Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
	
	pCamObj->Camera()->SetCameraPriority(1);
	pCamObj->Camera()->LayerCheck(31, true);
	
	pTempLevel->AddObject(pCamObj, 0);
	
	// 전역 광원 추가
	CGameObject* pLight = new CGameObject;
	pLight->SetName(L"Directional Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);
	
	pLight->Light2D()->SetLightType(LIGHT_TYPE::DIRECTIONAL);
	pLight->Light2D()->SetAmbient(Vec3(0.4f, 0.4f, 0.4f));
	pTempLevel->AddObject(pLight, 1);
	
	// 전역 광원 추가
	pLight = new CGameObject;
	pLight->SetName(L"Point Light");
	pLight->AddComponent(new CTransform);
	pLight->AddComponent(new CLight2D);

	pLight->Transform()->SetRelativePos(Vec3(-301.f, 54.f, 0.f));

	pLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	pLight->Light2D()->SetLightColor(Vec3(0.8f, 0.9f, 0.9f));
	pLight->Light2D()->SetRadius(600.f);
	pTempLevel->AddObject(pLight, 1);

	
	CGameObject* pObj = nullptr;

	// Backgruond Object 생성
	pObj = new CGameObject;
	pObj->SetName(L"Background");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CBackgroundScript);

	pObj->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));

	pTempLevel->AddObject(pObj, 28, false);

	// MainMenu UI (테두리)
	pObj = new CGameObject;
	pObj->SetName(L"BorderUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMainUIScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(1557.f, 851.f, 1.f));
	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));


	pTempLevel->AddObject(pObj, 3, false);

	// 버튼
	pObj = new CGameObject;
	pObj->SetName(L"ButtonUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CButtonScript);

	pObj->Transform()->SetRelativePos(Vec3(718.f, -112.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(471.f, 81.f, 1.f));

	pObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));


	pTempLevel->AddObject(pObj, 13, false);

	//MainMenu UI (게임 제목)
	pObj = new CGameObject;
	pObj->SetName(L"TitleUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CMenuUIScript);

	pObj->Transform()->SetRelativePos(Vec3(353.f, 236.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(750.f, 350.f, 1.f));
	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TitleMtrl"));

	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Spr_Logo_Kor.png", L"texture\\UI\\Spr_Logo_Kor.png"));
	pTempLevel->AddObject(pObj, 3, false);

	// LogoUI
	pObj = new CGameObject;
	pObj->SetName(L"LogoUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CMainLogoUI);


	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 400.f));
	pObj->Transform()->SetRelativeScale(Vec3(310.f / 2.f, 380.f / 2.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"LogoMtrl"));

	pTempLevel->AddObject(pObj, 3, false);
	
	//// Backgruond Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Background");
	//
	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CBackgroundScript);
	//
	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));
	//
	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"BackgroundMtrl"));
	//
	//Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Sky.png", L"texture\\BossRoom\\Spr_Chap1_Bossroom_Sky.png");
	//pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, pTex);
	//
	//pTempLevel->AddObject(pObj, L"Background", false);
	
	// Player Object 생성
	/*pObj = new CGameObject;
	pObj->SetName(L"Player");
	
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CRigidBody);
	pObj->AddComponent(new CGravity);
	pObj->AddComponent(new CPlayerScript);
	
	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));
	
	pObj->Collider2D()->SetAbsolute(true);
	pObj->Collider2D()->SetOffsetScale(Vec2(27.f, 75.f));
	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
	
	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));
	
	pTempLevel->AddObject(pObj, 11, false);*/
	//
	//// Tile
	//pObj = new CGameObject;
	//pObj->SetName(L"TileMap");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CTileMap);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	////pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	//Ptr<CTexture> pTileAtlas = CAssetMgr::GetInst()->Load<CTexture>(L"TileAtlasTex", L"texture\\Spr_Stage1_Tileset.png");

	//pObj->TileMap()->SetTileAtlas(pTileAtlas, Vec2(16.f, 16.f));
	//pObj->TileMap()->SetFace(6, 6);
	//pObj->TileMap()->SetTileRenderSize(Vec2(32.f, 32.f));


	//pTempLevel->AddObject(pObj, 27, false);

	//

	//// Enemy Object 생성
	////pObj = new CGameObject;
	////pObj->SetName(L"Enemy");
	////
	////pObj->AddComponent(new CTransform);
	////pObj->AddComponent(new CMeshRender);
	////pObj->AddComponent(new CAnimator2D);
	////pObj->AddComponent(new CCollider2D);
	//////pObj->AddComponent(new CStateMachine);
	////pObj->AddComponent(new CTurretBodyScript);
	////
	////pObj->Transform()->SetRelativePos(Vec3(400.f, -300.f, 500.f));
	////pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));
	////
	////pObj->Collider2D()->SetAbsolute(true);
	////pObj->Collider2D()->SetOffsetScale(Vec2(120.f, 120.f));
	////pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
	////
	////pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	////pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	////pObj->MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Fighter.bmp", L"texture\\Fighter.bmp"));
	////
	////pObj->GetScript<CTurretBodyScript>()->SetSpawnDir(SPAWN_DIR::LEFT);
	//////pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"TurretFSM"));

	////pTempLevel->AddObject(pObj, L"Enemy", false);

	//// Enemy2 Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Enemy2");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CTurretBodyScript);

	//pObj->Transform()->SetRelativePos(Vec3(625.f, 108.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(87.f, 120.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 15.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

	//pObj->GetScript<CTurretBodyScript>()->SetSpawnDir(SPAWN_DIR::LEFT);

	//pTempLevel->AddObject(pObj, 8, false);

	//pObj = new CGameObject;
	//pObj->SetName(L"Enemy3");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CTurretBodyScript);

	//pObj->Transform()->SetRelativePos(Vec3(-125.f, 108.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(200.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(87.f, 120.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 15.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

	//pObj->GetScript<CTurretBodyScript>()->SetSpawnDir(SPAWN_DIR::RIGHT);

	//pTempLevel->AddObject(pObj, 8, false);

	//// defender Object 생성
	//pObj = new CGameObject;
	//pObj->SetName(L"Defender");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CStateMachine);
	//pObj->AddComponent(new CDefendScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, -190.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(400.f, 400.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(60.f, 120.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(-25.f, 0.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

	//pObj->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"DefenderFSM"));

	//pTempLevel->AddObject(pObj, 8, false);





	//// Cargo
	//pObj = new CGameObject;
	//pObj->SetName(L"RedCargo");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CRedCargoScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(306.f, 162.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(215.f, 60.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(-10.f, -25.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	//
	//pTempLevel->AddObject(pObj, 23, false);


	// GamePlayBG
	//pObj = new CGameObject;
	//pObj->SetName(L"GamePlayBG");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CGamePlayBGScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 900.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	//pTempLevel->AddObject(pObj, 23, false);

	//// Dest
	//pObj = new CGameObject;
	//pObj->SetName(L"Dest");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CDestUIScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(43.f, 44.f, 1.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	//pTempLevel->AddObject(pObj, 3, false);

	// LayerMgr
	pObj = new CGameObject;
	pObj->SetName(L"LayerMgr");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CLayerMgrScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	pTempLevel->AddObject(pObj, 30, false);

	//pObj = new CGameObject;
	//pObj->SetName(L"GameSysMgr");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CGameSystemMgrScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	//pTempLevel->AddObject(pObj, 30, false);

	//

	//// Cargo
	//pObj = new CGameObject;
	//pObj->SetName(L"RedCargo2");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CRedCargoScript);

	//pObj->Transform()->SetRelativePos(Vec3(-700.f, 100.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(100.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 700.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	//pTempLevel->AddObject(pObj, 23, false);


	//// Cargo
	//pObj = new CGameObject;
	//pObj->SetName(L"RedCargo3");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CRedCargoScript);

	//pObj->Transform()->SetRelativePos(Vec3(700.f, 100.f, 600.f));
	//pObj->Transform()->SetRelativeScale(Vec3(100.f, 200.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(100.f, 700.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	//pTempLevel->AddObject(pObj, 23, false);


	//// Wall
	//pObj = new CGameObject;
	//pObj->SetName(L"Wall");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(1600.f, 1296.f, 1.f));


	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));

	//pTempLevel->AddObject(pObj, 18, false);




	

	// Bombcargo
	//pObj = new CGameObject;
	//pObj->SetName(L"bombCargo");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CBombCargoScript);

	//pObj->Transform()->SetRelativePos(Vec3(0.f, 300.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(340.f, 260.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(171.f, 130.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
	//
	//pObj->GetScript<CBombCargoScript>()->SetStartPos(Vec3(0.f, 600.f, 500.f));
	//pObj->GetScript<CBombCargoScript>()->SetEndPos(Vec3(0.f, 100.f, 500.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	//pTempLevel->AddObject(pObj, L"RedCargo", false);


	//
	//// FNCraneHook
	//pObj = new CGameObject;
	//pObj->SetName(L"finalcraneHook");

	//pObj->AddComponent(new CTransform);
	//pObj->AddComponent(new CMeshRender);
	//pObj->AddComponent(new CCollider2D);
	//pObj->AddComponent(new CAnimator2D);
	//pObj->AddComponent(new CFinalCraneHookScript);

	//pObj->Transform()->SetRelativePos(Vec3(30.f, 600.f, 500.f));
	//pObj->Transform()->SetRelativeScale(Vec3(90.f, 920.f, 1.f));

	//pObj->Collider2D()->SetAbsolute(true);
	//pObj->Collider2D()->SetOffsetScale(Vec2(90.f, 920.f));
	//pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	//pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	//pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	//pTempLevel->AddObject(pObj, L"RedCargo", false);

	// Grab
	/*pObj = new CGameObject;
	pObj->SetName(L"Grab");
	
	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CGrabScript);
	
	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	*/

	//pObj->GrabScript()->SetStartPos(Vec3(0.f, 0.f, 500.f);
	//pObj->GetScript<CGrabScript>()->SetMaxDist(230.f);
	//pObj->GetScript<CGrabScript>()->SetSpeed(1500.f);
	//
	/*pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(64.f, 125.f, 1.f));

	pTempLevel->AddObject(pObj, 9, false);*/

	// cursor
	pObj = new CGameObject;
	pObj->SetName(L"Cursor");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CCursorScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 500.f));
	pObj->Transform()->SetRelativeScale(Vec3(80.f, 80.f, 1.f));

	pObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	pTempLevel->AddObject(pObj, 3, false);

	// 충돌 설정
	/*CCollisionMgr::GetInst()->LayerCheck(5, 23);
	CCollisionMgr::GetInst()->LayerCheck(5, 22);
	CCollisionMgr::GetInst()->LayerCheck(5, 27);

	CCollisionMgr::GetInst()->LayerCheck(20, 17);
	CCollisionMgr::GetInst()->LayerCheck(20, 22);
	CCollisionMgr::GetInst()->LayerCheck(20, 23);
	CCollisionMgr::GetInst()->LayerCheck(20, 24);
	CCollisionMgr::GetInst()->LayerCheck(20, 25);
	CCollisionMgr::GetInst()->LayerCheck(20, 27);

	CCollisionMgr::GetInst()->LayerCheck(21, 5);
	CCollisionMgr::GetInst()->LayerCheck(21, 23);

	CCollisionMgr::GetInst()->LayerCheck(22, 23);

	CCollisionMgr::GetInst()->LayerCheck(1, 23);*/
	
	CLevelMgr::GetInst()->ChangeLevel(pTempLevel, LEVEL_STATE::PLAY);

	CLevelSaveLoad::SaveLevel(pTempLevel, L"level\\temp.lv");	
	//CLevelSaveLoad::LoadLevel(L"level\\Stage1.lv");
	//CLevelMgr::GetInst()->ChangeLevel(CLevelSaveLoad::LoadLevel(L"level\\Stage1.lv"), LEVEL_STATE::STOP);
}