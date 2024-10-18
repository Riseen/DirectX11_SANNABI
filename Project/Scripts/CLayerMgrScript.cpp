#include "pch.h"
#include "CLayerMgrScript.h"

#include <Engine/CLayer.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

#include <Engine/CCollisionMgr.h>

CLayerMgrScript::CLayerMgrScript()
	: CScript(LAYERMGRSCRIPT)
{
}

CLayerMgrScript::~CLayerMgrScript()
{
}


void CLayerMgrScript::begin()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	ShowCursor(false);

	pCurLevel->GetLayer(0)->SetName(L"Camera");
	pCurLevel->GetLayer(1)->SetName(L"Light");
	pCurLevel->GetLayer(2)->SetName(L"Fade");
	pCurLevel->GetLayer(3)->SetName(L"UI");
	pCurLevel->GetLayer(4)->SetName(L"Particle");
	pCurLevel->GetLayer(5)->SetName(L"PlayerEffect");
	pCurLevel->GetLayer(6)->SetName(L"TurretLaser");
	pCurLevel->GetLayer(7)->SetName(L"EnemyWeapon");
	pCurLevel->GetLayer(8)->SetName(L"Enemy");
	pCurLevel->GetLayer(9)->SetName(L"Grab");
	pCurLevel->GetLayer(10)->SetName(L"Arm");
	pCurLevel->GetLayer(11)->SetName(L"Player");
	pCurLevel->GetLayer(12)->SetName(L"EnemyAttack");
	pCurLevel->GetLayer(13)->SetName(L"Button");
	pCurLevel->GetLayer(14)->SetName(L"EventCollsion");
	pCurLevel->GetLayer(15)->SetName(L"ClimbBar");
	pCurLevel->GetLayer(16)->SetName(L"FinalCrane");
	pCurLevel->GetLayer(17)->SetName(L"DefenderShield");
	pCurLevel->GetLayer(18)->SetName(L"InvisibleWall");
	pCurLevel->GetLayer(19)->SetName(L"MapObject");
	pCurLevel->GetLayer(20)->SetName(L"SearchBar");
	pCurLevel->GetLayer(21)->SetName(L"Boss");
	pCurLevel->GetLayer(22)->SetName(L"BossRoomObj");
	pCurLevel->GetLayer(23)->SetName(L"RedCargo");
	pCurLevel->GetLayer(24)->SetName(L"BlueCargo");
	pCurLevel->GetLayer(27)->SetName(L"Tile");
	pCurLevel->GetLayer(28)->SetName(L"Background");
	pCurLevel->GetLayer(30)->SetName(L"GameSysManager");

	CCollisionMgr::GetInst()->LayerCheck(3, 13);

	CCollisionMgr::GetInst()->LayerCheck(8, 16);

	CCollisionMgr::GetInst()->LayerCheck(11, 8);
	CCollisionMgr::GetInst()->LayerCheck(11, 12);
	CCollisionMgr::GetInst()->LayerCheck(11, 14);
	CCollisionMgr::GetInst()->LayerCheck(11, 18);
	CCollisionMgr::GetInst()->LayerCheck(11, 23);
	CCollisionMgr::GetInst()->LayerCheck(11, 24);
	CCollisionMgr::GetInst()->LayerCheck(11, 27);

	CCollisionMgr::GetInst()->LayerCheck(15, 23);
	CCollisionMgr::GetInst()->LayerCheck(15, 24);
	CCollisionMgr::GetInst()->LayerCheck(15, 27);

	CCollisionMgr::GetInst()->LayerCheck(20, 8);
	CCollisionMgr::GetInst()->LayerCheck(20, 17);
	CCollisionMgr::GetInst()->LayerCheck(20, 21);
	CCollisionMgr::GetInst()->LayerCheck(20, 23);
	CCollisionMgr::GetInst()->LayerCheck(20, 24);
	CCollisionMgr::GetInst()->LayerCheck(20, 27);

	CCollisionMgr::GetInst()->LayerCheck(12, 22);


	CCollisionMgr::GetInst()->LayerCheck(12, 18);
	CCollisionMgr::GetInst()->LayerCheck(12, 23);
	CCollisionMgr::GetInst()->LayerCheck(12, 24);
	CCollisionMgr::GetInst()->LayerCheck(12, 27);

	//CCollisionMgr::GetInst()->LayerCheck(22, 23);

	//CCollisionMgr::GetInst()->LayerCheck(1, 23);
}

void CLayerMgrScript::tick()
{
	if (KEY_TAP(KEY::NUM7))
	{
		CLevelMgr::GetInst()->SetLevelType(LEVEL_TYPE::MAIN);
		CLevelMgr::GetInst()->ChangeLevel(CLevelMgr::GetInst()->LoadLevel(L"level\\Main.lv"), LEVEL_STATE::PLAY);
	}
	if (KEY_TAP(KEY::NUM8))
	{
		CLevelMgr::GetInst()->SetLevelType(LEVEL_TYPE::STAGE1);
		CLevelMgr::GetInst()->ChangeLevel(CLevelMgr::GetInst()->LoadLevel(L"level\\Stage1_7.lv"), LEVEL_STATE::PLAY);
	}
	if (KEY_TAP(KEY::NUM9))
	{
		CLevelMgr::GetInst()->SetLevelType(LEVEL_TYPE::BOSS);
		CLevelMgr::GetInst()->ChangeLevel(CLevelMgr::GetInst()->LoadLevel(L"level\\Boss.lv"), LEVEL_STATE::PLAY);
	}


}

void CLayerMgrScript::SaveToFile(FILE* _File)
{

	size_t LSize = sizeof(CLayer) * LAYER_MAX;
	fwrite(&m_matrix, sizeof(LSize), 1, _File);
	size_t mSize = sizeof(UINT) * LAYER_MAX;
	fwrite(&m_arrLayer, sizeof(mSize), 1, _File);
}

void CLayerMgrScript::LoadFromFile(FILE* _File)
{
	size_t LSize = sizeof(CLayer) * LAYER_MAX;
	fread(&m_matrix, sizeof(LSize), 1, _File);
	size_t mSize = sizeof(UINT) * LAYER_MAX;
	fread(&m_arrLayer, sizeof(mSize), 1, _File);
}



