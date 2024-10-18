#include "pch.h"
#include "CDropRedCargoScript.h"

#include "CPlayerScript.h"
#include "CBossRoomSysMgrScript.h"
#include "CDropRedCargoColScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CDropRedCargoScript::CDropRedCargoScript()
    : CScript(DROPREDCARGOSCRIPT)
	, m_fDownSpeed(200.f)
	, m_bDown(false)
	, m_CurState(DROPREDCARGO_STATE::SPAWN)
	, m_PrevState(DROPREDCARGO_STATE::SPAWN)
	, m_fAccTime(0.f)
	, m_fSpawnTime(1.4f)
{
}

CDropRedCargoScript::~CDropRedCargoScript()
{
}

void CDropRedCargoScript::begin()
{
    GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Stepped.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Idle.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Destroy.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Respawn.anim");

    Animator2D()->Play(L"Spr_WOE_BrokenCargoDroneBlue_A_Respawn");

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"CargoCOl");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CDropRedCargoColScript);

	pObj->Transform()->SetRelativePos(Vec3{});
	pObj->Transform()->SetRelativeScale(Vec3{1.f,1.f,1.f});

	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, -14.f));
	pObj->Collider2D()->SetOffsetScale(Vec2(271.f, 90.f));

	GetOwner()->AddChild(pObj);
}

void CDropRedCargoScript::tick()
{
	if (m_fAccTime > m_fSpawnTime)
	{
		m_CurState = DROPREDCARGO_STATE::IDLE;
	}
	else
	{
		m_fAccTime += DT;
	}

	if (m_bDown)
	{
		Vec3 vPos = Transform()->GetRelativePos();

		vPos.y -= m_fDownSpeed * DT;

		Transform()->SetRelativePos(vPos);
	}

	ChangeState();

	m_PrevState = m_CurState;
	
}

void CDropRedCargoScript::SaveToFile(FILE* _File)
{
    fwrite(&m_fDownSpeed, sizeof(float), 1, _File);
}

void CDropRedCargoScript::LoadFromFile(FILE* _File)
{
    fread(&m_fDownSpeed, sizeof(float), 1, _File);
}



void CDropRedCargoScript::ChangeState()
{
	if (m_CurState == m_PrevState)
		return;

	switch (m_CurState)
	{
	case DROPREDCARGO_STATE::NOT:
		break;
	case DROPREDCARGO_STATE::SPAWN:
		Animator2D()->Play(L"Spr_WOE_BrokenCargoDroneBlue_A_Respawn", false);
		break;
	case DROPREDCARGO_STATE::IDLE:
		Animator2D()->Play(L"Spr_WOE_BrokenCargoDroneBlue_A_Idle");
		break;
	case DROPREDCARGO_STATE::STEPPED:
		Animator2D()->PlayToPlay(L"Spr_WOE_BrokenCargoDroneBlue_A_Stepped", L"Spr_WOE_BrokenCargoDroneBlue_A_Idle");
		break;
	case DROPREDCARGO_STATE::DESTROY:
		Animator2D()->Play(L"Spr_WOE_BrokenCargoDroneBlue_A_Destroy", false);
		break;
	default:
		break;
	}
}


void CDropRedCargoScript::Destroy()
{
	m_CurState = DROPREDCARGO_STATE::DESTROY;
	CGameObject* pSysMgr = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"BossSysMgr");

	if (m_iDir == 0)
	{
		pSysMgr->GetScript<CBossRoomSysMgrScript>()->SetSysType(SYSMGR_TYPE::LEFTCARGOSPAWN);
	}
	else if (m_iDir == 1)
	{
		pSysMgr->GetScript<CBossRoomSysMgrScript>()->SetSysType(SYSMGR_TYPE::RIGHTCARGOSPAWN);
	}

	GamePlayStatic::DestroyGameObject(GetOwner());
}


