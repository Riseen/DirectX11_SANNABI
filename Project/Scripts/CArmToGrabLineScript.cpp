#include "pch.h"
#include "CArmToGrabLineScript.h"

#include "CArmScript.h"
#include "CSearchBarScript.h"
#include "CGrabScript.h"
#include "CGrabLineScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CArmToGrabLineScript::CArmToGrabLineScript()
	: CScript(ARMTOGRABLINESCRIPT)
	, m_CurState(ARM2LINE_STATE::NOT)
	, m_PrevState(ARM2LINE_STATE::NOT)
	, m_fTerm(32.f)
	, m_fLineSize(64.f)
{
}

CArmToGrabLineScript::~CArmToGrabLineScript()
{
}


void CArmToGrabLineScript::begin()
{
	
}

void CArmToGrabLineScript::tick()
{
	Vec3 vParentPos = GetOwner()->GetParent()->Transform()->GetWorldPos();
	CGameObject* pSearch = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SearchBar");
	Vec3 vPos = pSearch->GetScript<CSearchBarScript>()->GetSearchObjPos();

	if (vPos == Vec3{})
		m_CurState = ARM2LINE_STATE::NOT;
	else
		m_CurState = ARM2LINE_STATE::ACTIVE;

	ChangeState(vParentPos, vPos);
}

void CArmToGrabLineScript::SaveToFile(FILE* _File)
{
}

void CArmToGrabLineScript::LoadFromFile(FILE* _File)
{
}

void CArmToGrabLineScript::ChangeState(Vec3 _vParent, Vec3 _vDestPos)
{
	if (m_CurState == m_PrevState)
		return;


	if (m_CurState == ARM2LINE_STATE::ACTIVE && m_PrevState == ARM2LINE_STATE::NOT)
	{
		FirstCreate(_vParent, _vDestPos);
	}
	else if (m_CurState == ARM2LINE_STATE::NOT && m_PrevState == ARM2LINE_STATE::ACTIVE)
	{

	}

}

void CArmToGrabLineScript::FirstCreate(Vec3 _vParent, Vec3 _vDestPos)
{
	Vec3 vCurDir = _vDestPos - _vParent;

	float fCurDist = vCurDir.Length();
	fCurDist -= m_fTerm;

	int iCreateCount = 0;
	iCreateCount = fCurDist / (m_fTerm + m_fLineSize);

	float fx = _vDestPos.x - _vParent.x;
	float fy = _vDestPos.y - _vParent.y;

	// 현재각도
	float fCurAngle = atan2f(fy, fx);

	float fDe = XMConvertToDegrees(fCurAngle);
	fDe += 90.f;

	fCurDist -= fCurDist + m_fTerm;

	/*for (int i = 0; i < iCreateCount; ++i)
	{
		CGameObject* pObj = new CGameObject;
		pObj->SetName(L"Line");

		pObj->AddComponent(new CTransform);
		pObj->AddComponent(new CMeshRender);
		pObj->AddComponent(new CAnimator2D);
		pObj->AddComponent(new CGrabLineScript);

		pObj->Transform()->SetRelativeScale(Vec3(64.f, 64.f, 1.f));

		pObj->Transform()->SetRelativePos(Vec3(_vParent.x + cos(fCurAngle) * (fCurDist + (i * (m_fTerm + m_fLineSize))),
			_vParent.y + sin(fCurAngle) * (fCurDist + (i * (m_fTerm + m_fLineSize))),
			Transform()->GetRelativePos().z));

		pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
			Transform()->GetRelativeRotation().y,
			XMConvertToRadians(fDe)));

		pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
		pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
		
		GamePlayStatic::SpawnGameObject(pObj, 1);
	}*/
}
