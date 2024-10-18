#include "pch.h"
#include "CAfterImageManagerScript.h"
#include "CAfterImageScript.h"
#include "CPlayerScript.h"
#include "CArmScript.h"

CAfterImageManagerScript::CAfterImageManagerScript()
	: CScript(AFTERIMAGEMANAGERSCRIPT)
	, m_CurType(AFTERIMAGE_TYPE::NOT)
	, m_PrevType(AFTERIMAGE_TYPE::NOT)
	, m_fAccTime(0.f)
	, m_fTerm(0.01f)
	, m_iMaxSwingDashCount(20)
{
}

CAfterImageManagerScript::~CAfterImageManagerScript()
{
}

void CAfterImageManagerScript::begin()
{
}

void CAfterImageManagerScript::tick()
{
	CreateAfterImage();
	CreateSwingDashImage();

	m_PrevType = m_CurType;
}

void CAfterImageManagerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fTerm, sizeof(float), 1, _File);
	fwrite(&m_iMaxSwingDashCount, sizeof(int), 1, _File);
}

void CAfterImageManagerScript::LoadFromFile(FILE* _File)
{
	fread(&m_fTerm, sizeof(float), 1, _File);
	fread(&m_iMaxSwingDashCount, sizeof(int), 1, _File);
}

void CAfterImageManagerScript::CreateAfterImage()
{
	if (m_PrevType == m_CurType || m_CurType == AFTERIMAGE_TYPE::NOT || m_CurType == AFTERIMAGE_TYPE::SWING_DASH)
		return;

	CGameObject* pPlayer = GetOwner()->GetParent();
	vector<CGameObject*> pChild = pPlayer->GetChild();
	

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"AfterImage");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAfterImageScript);



	float fx = pPlayer->Transform()->GetRelativePos().x - pChild[0]->GetScript<CArmScript>()->GetBeforeHodlingPos().x;
	float fy = pPlayer->Transform()->GetRelativePos().y - pChild[0]->GetScript<CArmScript>()->GetBeforeHodlingPos().y;

	// 현재각도
	float fCurAngle = atan2f(fy, fx);

	pObj->Transform()->SetRelativePos(pChild[0]->GetScript<CArmScript>()->GetBeforeHodlingPos());
	pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));
	pObj->Transform()->SetRelativeRotation(Vec3(0.f,0.f, fCurAngle));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"AfterImageMtrl"));

	pObj->GetScript<CAfterImageScript>()->SetAfterImageState(m_CurType);
	pObj->GetScript<CAfterImageScript>()->SetLp(pPlayer->GetScript<CPlayerScript>()->GetCurLP());

	GamePlayStatic::SpawnGameObject(pObj, 5);
}

void CAfterImageManagerScript::CreateSwingDashImage()
{
	if (m_CurType != AFTERIMAGE_TYPE::SWING_DASH)
	{
		m_fAccTime = 0.f;
		m_iMaxSwingDashCount = 20;
		return;
	}
		


	if (m_fAccTime > m_fTerm && m_iMaxSwingDashCount > 0)
	{
		CGameObject* pPlayer = GetOwner()->GetParent();
		vector<CGameObject*> pChild = pPlayer->GetChild();


		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"AfterImage");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAfterImageScript);

		pObj->Transform()->SetRelativePos(pPlayer->Transform()->GetRelativePos());
		pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));
		pObj->Transform()->SetRelativeRotation(pPlayer->Transform()->GetRelativeRotation());

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"AfterImageMtrl"));

		pObj->GetScript<CAfterImageScript>()->SetAfterImageState(m_CurType);
		pObj->GetScript<CAfterImageScript>()->SetLp(pPlayer->GetScript<CPlayerScript>()->GetCurLP());

		GamePlayStatic::SpawnGameObject(pObj, 5);

		m_fAccTime = 0.f;
		m_iMaxSwingDashCount--;
	}

	m_fAccTime += DT;
}


