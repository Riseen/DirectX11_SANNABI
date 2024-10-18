#include "pch.h"
#include "CChainScript.h"
#include "CGrabScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CChainScript::CChainScript()
	: CScript(CHAINSCRIPT)
	, m_vDestPos{}
	, m_vStartPos{}
{
}

CChainScript::~CChainScript()
{
}

void CChainScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\VFX\\Chain.png", L"texture\\VFX\\Chain.png"));

}

void CChainScript::tick()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	CGameObject* pGrab = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Grab");


	if (pGrab->GetScript<CGrabScript>()->GetGrabState() != GRAB_STATE::NOT)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 4);

		}


		CGameObject* pArm = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ARM");

		float fx = pGrab->Transform()->GetWorldPos().x - pArm->Transform()->GetWorldPos().x;
		float fy = pGrab->Transform()->GetWorldPos().y - pArm->Transform()->GetWorldPos().y;

		// 물체와 플레이어의 거리
		float fCurDist = sqrtf(pow(fx, 2) + pow(fy, 2));

		// 현재각도
		float fCurAngle = atan2f(fy, fx);

		float fDe = XMConvertToDegrees(fCurAngle);


		Transform()->SetRelativeScale(Vec3(fCurDist, 3.f, 1.f));

		float fParentRot = pArm->Transform()->GetRelativeRotation().z;
		float fParentRot1 = pArm->GetParent()->Transform()->GetRelativeRotation().z;

		// 상수값아닌 출발 - 도착위치의 거리넣어줘야함
		float fRadi = XMConvertToRadians(fDe);
		Transform()->SetRelativePos(Vec3((pArm->Transform()->GetWorldPos().x + (cosf(fRadi) * (fCurDist / 2.f))),
			pArm->Transform()->GetWorldPos().y + (sinf(fRadi) * (fCurDist / 2.f)),
			Transform()->GetRelativePos().z));

		Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
			Transform()->GetRelativeRotation().y,
			XMConvertToRadians(fDe)));

	}
	else
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 2);
		}
	}
}

void CChainScript::SaveToFile(FILE* _File)
{
}

void CChainScript::LoadFromFile(FILE* _File)
{
}



