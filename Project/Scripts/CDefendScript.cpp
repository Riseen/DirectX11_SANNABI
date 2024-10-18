#include "pch.h"
#include "CDefendScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CDefendScript::CDefendScript()
	: CEnemyScript(DEFENDSCRIPT)
	, m_Shield(nullptr)
	, m_CurState(ENEMY_STATE::POPUP)
	, m_PrevState(ENEMY_STATE::POPUP)
	, m_fAppearTime(2.4f)
	, m_bCurLp(false)
	, m_bDead(false)
{
}

CDefendScript::~CDefendScript()
{
}


void CDefendScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Appear.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Appear_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Attack.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Attack_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Cooltime.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Cooltime_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Deadpng.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Deadpng_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_ExcHolded.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_ExcHolded_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Idle.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_Idle_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_TurnEnd.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_Defender_TurnStart.anim");

	m_Shield = new CGameObject;
	m_Shield->SetName(L"Shield");

	m_Shield->AddComponent(new CTransform);
	m_Shield->AddComponent(new CCollider2D);

	m_Shield->Transform()->SetRelativePos(Vec3{30.f,0.f,0.f});
	m_Shield->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	m_Shield->Collider2D()->SetOffsetPos(Vec2{});
	m_Shield->Collider2D()->SetOffsetScale(Vec2(40.f, 120.f));

	GetOwner()->AddChild(m_Shield);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(m_Shield, 17);

	if (StateMachine())
	{
		// 플레이어를 찾아서 Object 타입으로 블랙보드에 기록한다.
		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer)
		{
			StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
		}
	}


	Animator2D()->Play(L"Spr_ENE_Defender_Appear_rp");
	GamePlayStatic::Play2DSound(L"sound\\Enemy\\SFX_CHAP1_DefenderShield.wav", 1, 0.1f);

	ChangeShieldPos();
}

void CDefendScript::tick()
{

	if (m_fDeadAccTime > m_fDeadTime)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}
	else if(m_bDead)
	{
		m_fDeadAccTime += DT;
	}

	static float fAcc = 0.f;
	vector<CGameObject*> pGun = GetOwner()->GetChild();

	if (fAcc > m_fAppearTime && m_CurState == ENEMY_STATE::POPUP)
	{
		m_CurState = ENEMY_STATE::SHOOTING;
		StateMachine()->GetFSM()->SetState(L"DefenderShootingState");
	}
	
	fAcc += DT;
	
	Detected();

	ChangeState();

	m_PrevState = m_CurState;
	m_bPrevLp = m_bCurLp;
}

void CDefendScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDefendScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDefendScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDefendScript::SetCurEnemyState(ENEMY_STATE _State)
{
	m_CurState = _State;
}

void CDefendScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fAppearTime, sizeof(float), 1, _File);
}

void CDefendScript::LoadFromFile(FILE* _File)
{
	fread(&m_fAppearTime, sizeof(float), 1, _File);
}

void CDefendScript::ChangeState()
{
	if (m_PrevState == m_CurState && m_bCurLp == m_bPrevLp)
		return;

	if (m_bCurLp != m_bPrevLp)
		ChangeShieldPos();

	switch (m_CurState)
	{
	case ENEMY_STATE::IDLE:
		break;
	case ENEMY_STATE::POPUP:
	{
		Animator2D()->Play(L"Spr_ENE_Defender_Appear");
		
	}
		break;
	case ENEMY_STATE::ALERT:
		if (m_bCurLp)
			Animator2D()->Play(L"Spr_ENE_Defender_Cooltime");
		else
			Animator2D()->Play(L"Spr_ENE_Defender_Cooltime_rp");
		break;
	case ENEMY_STATE::AIMING:
		break;
	case ENEMY_STATE::SHOOTING:
	{
		if (m_bCurLp)
			Animator2D()->PlayToPlay(L"Spr_ENE_Defender_Idle", L"Spr_ENE_Defender_Attack");
		else
			Animator2D()->PlayToPlay(L"Spr_ENE_Defender_Idle_rp", L"Spr_ENE_Defender_Attack_rp");
		
		GamePlayStatic::Play2DSound(L"sound\\Enemy\\SFX_Chap1_Defender_Shoot.wav", 1, 0.1f);
	}
		break;
	case ENEMY_STATE::HOLDING:
		if (m_bCurLp)
			Animator2D()->Play(L"Spr_ENE_Defender_ExcHolded", false);
		else
			Animator2D()->Play(L"Spr_ENE_Defender_ExcHolded_rp", false);
		break;
	case ENEMY_STATE::DEAD:
		if (m_bCurLp)
			Animator2D()->Play(L"Spr_ENE_Defender_Deadpng", false);
		else
			Animator2D()->Play(L"Spr_ENE_Defender_Deadpng_rp", false);

		m_bDead = true;
		break;
	default:
		break;
	}
}

void CDefendScript::ChangeShieldPos()
{
	Vec2 vOffPos = Collider2D()->GetOffsetPos();

	vOffPos *= -1;
	Collider2D()->SetOffsetPos(vOffPos);


	Vec3 vShieldPos = m_Shield->Transform()->GetRelativePos();
	vShieldPos *= -1;
	m_Shield->Transform()->SetRelativePos(vShieldPos);
}



void CDefendScript::Holding()
{
	m_CurState = ENEMY_STATE::HOLDING;
}

void CDefendScript::Dead()
{
	m_CurState = ENEMY_STATE::DEAD;
	Collider2D()->SetOffsetScale(Vec2(0.f, 0.f));
	m_Shield->Collider2D()->SetOffsetScale(Vec2(0.f, 0.f));
}

void CDefendScript::Detected()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	CGameObject* pSearch = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SearchBar");
	if (pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::ENEMY &&
		pSearch->GetScript<CSearchBarScript>()->GetSearchObj() == GetOwner())
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
