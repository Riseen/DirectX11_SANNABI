#include "pch.h"
#include "CTurretBodyScript.h"
#include "CTurretGunScript.h"
#include "CTurretLaserScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>



CTurretBodyScript::CTurretBodyScript()
	: CEnemyScript(TURRETBODYSCRIPT)
	, m_pGun(nullptr)
	, m_pLaser(nullptr)
	, m_CurState(ENEMY_STATE::POPUP)
	, m_PrevState(ENEMY_STATE::POPUP)
	, m_CurSpawnDir(SPAWN_DIR::DOWN)
	, m_fPopUpTime(1.4f)
	, m_fDeadAccTime(0.f)
	, m_fDeadTime(0.7f)
	, m_fAccTime(0.f)

{
	AddScriptParam(SCRIPT_PARAM::INT, "SpawnDir", &m_CurSpawnDir);
}

CTurretBodyScript::~CTurretBodyScript()
{
}


void CTurretBodyScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_Aiming.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_Alert.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_Cooldown.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_Dead.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_ExcHolded.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_PopUp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Turret\\Turret_Body_Shooting.anim");



	
	m_pGun = new CGameObject;
	m_pGun->SetName(L"TurretGun");

	m_pGun->AddComponent(new CTransform);
	m_pGun->AddComponent(new CMeshRender);
	m_pGun->AddComponent(new CAnimator2D);
	m_pGun->AddComponent(new CStateMachine);
	m_pGun->AddComponent(new CTurretGunScript);

	m_pGun->Transform()->SetRelativePos(Vec3{});
	m_pGun->Transform()->SetRelativeScale(Vec3{ 1.f,1.f,1.f });
	m_pGun->Transform()->SetAbsolute(false);

	m_pGun->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	m_pGun->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"EnemyMtrl"));

	m_pGun->StateMachine()->SetFSM(CAssetMgr::GetInst()->FindAsset<CFSM>(L"TurretFSM"));

	GetOwner()->AddChild(m_pGun);

	


	m_pLaser = new CGameObject;
	m_pLaser->SetName(L"Laser");

	m_pLaser->AddComponent(new CTransform);
	m_pLaser->AddComponent(new CMeshRender);
	m_pLaser->AddComponent(new CTurretLaserScript);

	m_pLaser->Transform()->SetRelativePos(Vec3{});
	m_pLaser->Transform()->SetAbsolute(true);
	
	m_pLaser->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	m_pLaser->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"LaserMtrl"));

	GetOwner()->AddChild(m_pLaser);

	Animator2D()->Play(L"Turret_Body_PopUp", false);
	GamePlayStatic::Play2DSound(L"sound\\Enemy\\SFX_Ene_TurretOpening.wav", 1, 0.1f);
}



void CTurretBodyScript::tick()
{
	if (m_CurState == ENEMY_STATE::DEAD)
	{
		m_fDeadAccTime += DT;
	}
	if (m_fDeadAccTime > m_fDeadTime)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}
		

	m_pLaser->GetScript<CTurretLaserScript>()->SetStartPos(Transform()->GetWorldPos());


	if (m_fAccTime > m_fPopUpTime && m_CurState == ENEMY_STATE::POPUP)
	{
		m_CurState = ENEMY_STATE::ALERT;
		m_pGun->StateMachine()->GetFSM()->SetState(L"AlertState");
		m_fAccTime = 0.f;
	}
	else
	{
		m_fAccTime += DT;
	}
	
	ChangeState();

	if (m_pGun)
	{
		m_pGun->GetScript<CTurretGunScript>()->ChangeFSM(m_CurState);
		m_pGun->GetScript<CTurretGunScript>()->ChangeState(m_CurState, m_PrevState);
	}

	Detected();

	SetSpawnDir(m_CurSpawnDir);
	m_PrevState = m_CurState;
}

void CTurretBodyScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CTurretBodyScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CTurretBodyScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}



void CTurretBodyScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fPopUpTime, sizeof(float), 1, _File);
	fwrite(&m_fDeadTime, sizeof(float), 1, _File);
}

void CTurretBodyScript::LoadFromFile(FILE* _File)
{
	fread(&m_fPopUpTime, sizeof(float), 1, _File);
	fread(&m_fDeadTime, sizeof(float), 1, _File);
}

void CTurretBodyScript::ChangeState()
{
	if (m_CurState == m_PrevState)
		return;

	switch (m_CurState)
	{
	case ENEMY_STATE::IDLE:
		break;
	case ENEMY_STATE::ALERT:
		if (m_PrevState == ENEMY_STATE::SHOOTING)
			Animator2D()->PlayToPlay(L"Turret_Body_Cooldown", L"Turret_Body_Alert", false);
		else
			Animator2D()->Play(L"Turret_Body_Alert", false);

		m_pLaser->GetScript<CTurretLaserScript>()->SetLasetState(TURRETLASER_STATE::AIMMING);
		break;
	case ENEMY_STATE::POPUP:
		break;
	case ENEMY_STATE::AIMING:
		Animator2D()->Play(L"Turret_Body_Aiming");
		m_pLaser->GetScript<CTurretLaserScript>()->SetLasetState(TURRETLASER_STATE::AIMMING);
		break;
	case ENEMY_STATE::SHOOTING:
		Animator2D()->Play(L"Turret_Body_Shooting");
		m_pLaser->GetScript<CTurretLaserScript>()->SetLasetState(TURRETLASER_STATE::SHOT);
		break;
	case ENEMY_STATE::HOLDING:
		Animator2D()->Play(L"Turret_Body_ExcHolded", false);
		m_pLaser->GetScript<CTurretLaserScript>()->SetLasetState(TURRETLASER_STATE::NOT);
		break;
	case ENEMY_STATE::DEAD:
		Animator2D()->Play(L"Turret_Body_Dead", false);
		m_pLaser->GetScript<CTurretLaserScript>()->SetLasetState(TURRETLASER_STATE::NOT);
		break;
	default:
		break;
	}
}

bool CTurretBodyScript::IsSpecialState()
{
	if (m_CurState == ENEMY_STATE::DEAD || m_CurState == ENEMY_STATE::IDLE
		|| m_CurState == ENEMY_STATE::HOLDING || m_CurState == ENEMY_STATE::POPUP)
	{
		return true;
	}
	else
		return false;
}

void CTurretBodyScript::SetSpawnDir(SPAWN_DIR _dir)
{
	Vec3 vRot = Transform()->GetRelativeRotation();

	
	switch (_dir)
	{
	case SPAWN_DIR::UP:
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, XMConvertToRadians(180.f)));
		break;
	case SPAWN_DIR::DOWN:
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, 0.f));
		break;
	case SPAWN_DIR::LEFT:
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, XMConvertToRadians(90.f)));
		break;
	case SPAWN_DIR::RIGHT:
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, XMConvertToRadians(270.f)));
		break;
	default:
		break;
	}

	m_CurSpawnDir = _dir;
}

void CTurretBodyScript::SetCurEnemyState(ENEMY_STATE _State)
{
	m_CurState = _State;
}

void CTurretBodyScript::Holding()
{
	m_CurState = ENEMY_STATE::HOLDING;
	m_pGun->StateMachine()->GetFSM()->SetState(L"EnemyHoldingState");
}

void CTurretBodyScript::Dead()
{
	m_CurState = ENEMY_STATE::DEAD;
	Collider2D()->SetOffsetScale(Vec2(0.f, 0.f));
	GamePlayStatic::DestroyGameObject(m_pGun);
}

void CTurretBodyScript::Detected()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	CGameObject* pSearch = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SearchBar");
	if (pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::ENEMY &&
		pSearch->GetScript<CSearchBarScript>()->GetSearchObj() == GetOwner())
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 1);
			if (m_pGun != nullptr && m_pGun->GetLayerIdx() > 0 && m_pGun->GetName() == L"TurretGun")
				m_pGun->GetScript<CTurretGunScript>()->SetOutLine(true);
		}
	}
	else
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 0);
			if (m_pGun != nullptr && m_pGun->GetLayerIdx() > 0 && m_pGun->GetName() == L"TurretGun")
				m_pGun->GetScript<CTurretGunScript>()->SetOutLine(false);
		}
	}
}
