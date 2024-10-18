#include "pch.h"
#include "CBombScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CBombScript::CBombScript()
	: CScript(BOMBSCRIPT)
	, m_CurState(DefenderBOMB_STATE::Appear)
	, m_PrevState(DefenderBOMB_STATE::Appear)
	, m_iDir(0)
	, m_fAppearTime(0.7f)
	, m_fAccTime(0.f)
	, m_bDead(false)
{
}

CBombScript::~CBombScript()
{
}



void CBombScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_Appear.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_ExcHolded_Back.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_ExcHolded_Front.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_ExcHolded_Neu.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_ExcHoldedStart.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_Explode.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_Explode_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_Move.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Defender\\Spr_ENE_BoomBot_Move_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_BulletVfx_Explosion.anim");

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pPlayer)
	{
		StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
	}

	Animator2D()->Play(L"Spr_ENE_BoomBot_Appear");
}

void CBombScript::tick()
{
	static Vec3 vPrevPos = {};

	if (m_bDead)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}

	if (m_fAccTime > m_fAppearTime && m_CurState == DefenderBOMB_STATE::Appear)
	{
		StateMachine()->GetFSM()->SetState(L"BombMoveState");
		m_CurState = DefenderBOMB_STATE::MOVE;
	}

	Vec3 vPos = Transform()->GetRelativePos();

	if (vPrevPos.x - vPos.x > 0)
	{
		// right
		m_iDir = 0;
	}
	else
	{
		// left
		m_iDir = 1;
	}


	m_fAccTime += DT;

	ChangeState();

	vPrevPos = vPos;
	m_PrevState = m_CurState;
}

void CBombScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fAppearTime, sizeof(float), 1, _File);
}

void CBombScript::LoadFromFile(FILE* _File)
{
	fread(&m_fAppearTime, sizeof(float), 1, _File);
}

void CBombScript::ChangeState()
{
	if (m_PrevState == m_CurState)
		return;

	switch (m_CurState)
	{
	case DefenderBOMB_STATE::Appear:
		Animator2D()->Play(L"Spr_ENE_BoomBot_Appear", false);
		break;
	case DefenderBOMB_STATE::MOVE:
		if (m_iDir == 0)
			Animator2D()->Play(L"Spr_ENE_BoomBot_Move_rp");
		else
			Animator2D()->Play(L"Spr_ENE_BoomBot_Move");
		break;
	case DefenderBOMB_STATE::EXPLODE_READY:
		if (m_iDir == 0)
			Animator2D()->Play(L"Spr_ENE_BoomBot_Explode_rp");
		else
			Animator2D()->Play(L"Spr_ENE_BoomBot_Explode");
		break;
	case DefenderBOMB_STATE::EXPLODE:
	{
		Animator2D()->Play(L"Sprsht_BulletVfx_Explosion", false);
		GamePlayStatic::Play2DSound(L"sound\\Enemy\\SFX_Chap1_FlyingBomb_Explode (1).wav", 1, 0.1f);
	}
		break;
	default:
		break;
	}
}
