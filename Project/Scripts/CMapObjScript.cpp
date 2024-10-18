#include "pch.h"
#include "CMapObjScript.h"

CMapObjScript::CMapObjScript()
	: CScript(MAPOBJSCRIPT)
{
	AddScriptParam(SCRIPT_PARAM::INT, "MAPOBJ_TYPE", &m_CurMapObjType);
}

CMapObjScript::~CMapObjScript()
{
}

void CMapObjScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	SetTexture();
}

void CMapObjScript::tick()
{
}

void CMapObjScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CurMapObjType, sizeof(MAPOBJ_TYPE), 1, _File);
}

void CMapObjScript::LoadFromFile(FILE* _File)
{
	fread(&m_CurMapObjType, sizeof(MAPOBJ_TYPE), 1, _File);
}


void CMapObjScript::SetTexture()
{
	if (MeshRender()->GetMaterial() == nullptr)
		return;

	switch (m_CurMapObjType)
	{
	case MAPOBJ_TYPE::BACKBUILDING1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_BG_C1_BackBuilding1.png", 
			L"texture\\MapObject\\Spr_BG_C1_BackBuilding1.png"));
		break;
	case MAPOBJ_TYPE::BACKBUILDING2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_BG_C1_BackBuilding2.png",
			L"texture\\MapObject\\Spr_BG_C1_BackBuilding2.png"));
		break;
	case MAPOBJ_TYPE::BACKBUILDING3:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_BG_C1_BackBuilding3.png",
			L"texture\\MapObject\\Spr_BG_C1_BackBuilding3.png"));
		break;
	case MAPOBJ_TYPE::BACKBUILDING4:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_BG_C1_BackBuilding4.png",
			L"texture\\MapObject\\Spr_BG_C1_BackBuilding4.png"));
		break;
	case MAPOBJ_TYPE::BACKBUILDING6:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_BG_C1_BackBuilding6.png",
			L"texture\\MapObject\\Spr_BG_C1_BackBuilding6.png"));
		break;
	case MAPOBJ_TYPE::BARICATE1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Barricate01.png",
			L"texture\\MapObject\\Spr_C1_Prop_Barricate01.png"));
		break;
	case MAPOBJ_TYPE::BARICATE2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Barricate02.png",
			L"texture\\MapObject\\Spr_C1_Prop_Barricate02.png"));
		break;
	case MAPOBJ_TYPE::BASKET:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Basket01.png",
			L"texture\\MapObject\\Spr_C1_Prop_Basket01.png"));
		break;
	case MAPOBJ_TYPE::CYCLE:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Bicycle.png",
			L"texture\\MapObject\\Spr_C1_Prop_Bicycle.png"));
		break;
	case MAPOBJ_TYPE::BOARD:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Board02.png",
			L"texture\\MapObject\\Spr_C1_Prop_Board02.png"));
		break;



	case MAPOBJ_TYPE::BUSSTATION1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_BusStation02.png",
			L"texture\\MapObject\\Spr_C1_Prop_BusStation02.png"));
		break;
	case MAPOBJ_TYPE::BUSSTATION2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_BusStation03.png",
			L"texture\\MapObject\\Spr_C1_Prop_BusStation03.png"));
		break;
	case MAPOBJ_TYPE::CAR1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Car04.png",
			L"texture\\MapObject\\Spr_C1_Prop_Car04.png"));
		break;
	case MAPOBJ_TYPE::CAR2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Car06.png",
			L"texture\\MapObject\\Spr_C1_Prop_Car06.png"));
		break;
	case MAPOBJ_TYPE::DONOTENTER:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_DoNotEnter01.png",
			L"texture\\MapObject\\Spr_C1_Prop_DoNotEnter01.png"));
		break;
	case MAPOBJ_TYPE::STUFF:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Stuff02.png",
			L"texture\\MapObject\\Spr_C1_Prop_Stuff02.png"));
		break;
	case MAPOBJ_TYPE::TRUCK:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Truck02.png",
			L"texture\\MapObject\\Spr_C1_Prop_Truck02.png"));
		break;
	case MAPOBJ_TYPE::POLE:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Spr_C1_Prop_Utilitypole04.png",
			L"texture\\MapObject\\Spr_C1_Prop_Utilitypole04.png"));
		break;
	case MAPOBJ_TYPE::FRONT1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_01.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_01.png"));
		break;
	case MAPOBJ_TYPE::FRONT2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_02.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_02.png"));
		break;
	case MAPOBJ_TYPE::FRONT3:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_03.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_03.png"));
		break;
	case MAPOBJ_TYPE::FRONT4:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_04.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_04.png"));
		break;
	case MAPOBJ_TYPE::FRONT5:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_05.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_05.png"));
		break;
	case MAPOBJ_TYPE::FRONT6:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_06.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_06.png"));
		break;
	case MAPOBJ_TYPE::FRONT7:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_06-1.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_06-1.png"));
		break;
	case MAPOBJ_TYPE::FRONT8:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_07.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_07.png"));
		break;
	case MAPOBJ_TYPE::FRONT9:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_07-1.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_07-1.png"));
		break;
	case MAPOBJ_TYPE::FRONT10:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\MapObject\\Stage1_City_BG_Front_08.png",
			L"texture\\MapObject\\Stage1_City_BG_Front_08.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_FRONT:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Front.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Front.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid1.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid1.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid2.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid2.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID3:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid3.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid3.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID4:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid4.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid4.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID5:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid5.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid5.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID6:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid6.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid6.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID7:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid7.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid7.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID8:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid8.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid8.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_MID9:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid9.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Mid9.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Wall.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Wall.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL_LEFT:
		
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL_RIGHT:
		
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL_WIDE:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_Bossroom_Wall_Wide.png",
			L"texture\\BossRoom\\Spr_Chap1_Bossroom_Wall_Wide.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL_WIDE_LEFT:
	
		break;
	case MAPOBJ_TYPE::BOSSROOM_WALL_WIDE_RIGHT:
	
		break;
	case MAPOBJ_TYPE::BOSSROOM_LOOP_MID1:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid01.png",
			L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid01.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_LOOP_MID2:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid02.png",
			L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid02.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_LOOP_MID3:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid03.png",
			L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid03.png"));
		break;
	case MAPOBJ_TYPE::BOSSROOM_LOOP_MID4:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid04.png",
			L"texture\\BossRoom\\Spr_Chap1_BossroomLoop_Mid04.png"));
		break;
	default:
		break;
	}


}