#include "pch.h"
#include "CTurretGunScript.h"
#include "CTurretBodyScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CTurretGunScript::CTurretGunScript()
	: CEnemyScript(TURRETGUNSCRIPT)
	, m_fDegree(0.f)
	, m_fDist(30.f)
	, m_vCurPlayerDir {}
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Degree", &m_fDegree);
}

CTurretGunScript::~CTurretGunScript()
{
}


void CTurretGunScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Gun_Aiming.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Gun_Alert.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Gun_Cooldown.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Gun_Shooting.anim");


	if (StateMachine())
	{
		// 플레이어를 찾아서 Object 타입으로 블랙보드에 기록한다.
		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
		}

		if (nullptr != StateMachine()->GetFSM())
		{
			StateMachine()->GetFSM()->SetState(L"IdleState");
		}
	}
}



void CTurretGunScript::tick()
{
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");

	Vec3 v = Transform()->GetWorldPos();
	
	float fx = pPlayer->Transform()->GetWorldPos().x - v.x;
	float fy = pPlayer->Transform()->GetWorldPos().y - v.y;
	m_vCurPlayerDir = pPlayer->Transform()->GetWorldPos() - v;
	m_vCurPlayerDir.Normalize();

	// 현재각도
	float fCurAngle = atan2f(fy, fx);

	m_fDegree = XMConvertToDegrees(fCurAngle);
	
	m_vShotPos = m_vCurPlayerDir * m_fDist;

	SPAWN_DIR curDir = GetOwner()->GetParent()->GetScript<CTurretBodyScript>()->GetSpawnDir();

	switch (curDir)
	{
	case SPAWN_DIR::UP:
	{
		m_fDegree += 90.f;
	}
		break;
	case SPAWN_DIR::DOWN:
	{
		m_fDegree -= 90.f;
	}
		break;
	case SPAWN_DIR::LEFT:
	{
		m_fDegree -= 180.f;
	}
		break;
	case SPAWN_DIR::RIGHT:
	{
		//m_fDegree += 180.f;
	}
		break;
	default:
		break;
	}

	Detected();

	Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
		Transform()->GetRelativeRotation().y,
		XMConvertToRadians(m_fDegree)));
}



void CTurretGunScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fDist, sizeof(float), 1, _File);
}

void CTurretGunScript::LoadFromFile(FILE* _File)
{
	fread(&m_fDist, sizeof(float), 1, _File);
}


void CTurretGunScript::ChangeFSM(ENEMY_STATE _CurState)
{
	
}


void CTurretGunScript::ChangeState(ENEMY_STATE _CurState, ENEMY_STATE _PrevState)
{
	switch (_CurState)
	{
	case ENEMY_STATE::IDLE:
		Animator2D()->Play(L"NONE");
		break;
	case ENEMY_STATE::POPUP:
		Animator2D()->Play(L"NONE");
		break;
	case ENEMY_STATE::ALERT:
		if(_PrevState == ENEMY_STATE::SHOOTING)
			Animator2D()->PlayToPlay(L"Turret_Gun_Cooldown", L"Turret_Gun_Alert");
		else
			Animator2D()->Play(L"Turret_Gun_Alert");
		break;
	case ENEMY_STATE::AIMING:
		Animator2D()->Play(L"Turret_Gun_Aiming");
		break;
	case ENEMY_STATE::SHOOTING:
		Animator2D()->Play(L"Turret_Gun_Shooting");
		break;
	case ENEMY_STATE::HOLDING:
		Animator2D()->Play(L"NONE",false);
		break;
	case ENEMY_STATE::DEAD:
		//Animator2D()->Play(L"NONE");
		break;
	default:
		break;
	}
}

void CTurretGunScript::Detected()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	if (m_bOutLineOn)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 1);
		}
	}
	else
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 0);
		}
	}
}
