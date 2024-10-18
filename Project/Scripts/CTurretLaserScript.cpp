#include "pch.h"
#include "CTurretLaserScript.h"
#include "CTurretBodyScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CTurretLaserScript::CTurretLaserScript()
	: CScript(TURRETLASERSCRIPT)
	, m_CurState(TURRETLASER_STATE::NOT)
	, m_vDestPos{}
	, m_vStartPos{}
{
}

CTurretLaserScript::~CTurretLaserScript()
{
}

void CTurretLaserScript::begin()
{

	GetRenderComponent()->GetDynamicMaterial();

	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Laser 1.png", L"texture\\particle\\Laser 1.png"));
}

void CTurretLaserScript::tick()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	if (m_CurState == TURRETLASER_STATE::AIMMING)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 1);
			
		}

		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

		float fx = pPlayer->Transform()->GetWorldPos().x - m_vStartPos.x;
		float fy = pPlayer->Transform()->GetWorldPos().y - m_vStartPos.y;

		// 물체와 플레이어의 거리
		float fCurDist = sqrtf(pow(fx, 2) + pow(fy, 2));

		// 현재각도
		float fCurAngle = atan2f(fy, fx);

		float fDe = XMConvertToDegrees(fCurAngle);

		SPAWN_DIR SpawnDir = GetOwner()->GetParent()->GetScript<CTurretBodyScript>()->GetSpawnDir();

	
		switch (SpawnDir)
		{
		case SPAWN_DIR::UP:
		{
			fDe -= 180.f;
		}
			break;
		case SPAWN_DIR::DOWN:
		{
			
		}
			break;
		case SPAWN_DIR::LEFT:
		{
			fDe -= 90.f;
		}
			break;
		case SPAWN_DIR::RIGHT:
		{
			fDe += 90.f;
		}
			break;
		default:
			break;
		}

		Transform()->SetRelativeScale(Vec3(fCurDist, 20.f, 1.f));

		// 상수값아닌 출발 - 도착위치의 거리넣어줘야함
		float fRadi = XMConvertToRadians(fDe);
		Transform()->SetRelativePos(Vec3((cosf(fRadi) * (fCurDist / 2.f)),
			(sinf(fRadi) * (fCurDist / 2.f)),
			Transform()->GetRelativePos().z));

		Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
			Transform()->GetRelativeRotation().y,
			XMConvertToRadians(fDe)));
	}
	else if (m_CurState == TURRETLASER_STATE::NOT)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 2);
		}
	}
	else if (m_CurState == TURRETLASER_STATE::SHOT)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 2);
		}
	}
}

void CTurretLaserScript::SaveToFile(FILE* _File)
{
}

void CTurretLaserScript::LoadFromFile(FILE* _File)
{
}


