#include "pch.h"
#include "CPlayerEffectScript.h"
#include "CPlayerScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CPlayerEffectScript::CPlayerEffectScript()
	: CScript(PLAYEREFFECTSCRIPT)
	, m_CurEffectType(PlayerEffect_TYPE::NOT)
	, m_PrevEffectType(PlayerEffect_TYPE::NOT)
	, m_fAccTime(0.f)
	, m_fDeleteTime(0.6f)
{
}

CPlayerEffectScript::~CPlayerEffectScript()
{
}

void CPlayerEffectScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_Dash.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_Dash_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_Dust.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ExcBomb.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ExcDash.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_GrabDust.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\SprSht_VfxSNB_Grabhit.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_Jump.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_Landing.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_WallJump.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_WallJump_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_WallClimbDown.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_WallClimbDown_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ShootGas.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ShootGas_rp.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ShootMuzzleFire.anim");
	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ShootMuzzleFire_rp.anim");

	GetRenderComponent()->GetDynamicMaterial();
}

void CPlayerEffectScript::tick()
{
	if (m_fAccTime > m_fDeleteTime)
		GamePlayStatic::DestroyGameObject(GetOwner());

	PlayEffect();

	


	m_PrevEffectType = m_CurEffectType;

	m_fAccTime += DT;
}

void CPlayerEffectScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fDeleteTime, sizeof(float), 1, _File);
}

void CPlayerEffectScript::LoadFromFile(FILE* _File)
{
	fread(&m_fDeleteTime, sizeof(float), 1, _File);
}

void CPlayerEffectScript::PlayEffect()
{
	if (m_PrevEffectType == m_CurEffectType)
		return;

	CGameObject* pObj = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	bool bLp = false;
	if (pObj != nullptr)
		bLp = pObj->GetScript<CPlayerScript>()->GetCurLP();

	switch (m_CurEffectType)
	{
	case PlayerEffect_TYPE::NOT:
		break;
	case PlayerEffect_TYPE::JUMP:
		Animator2D()->Play(L"Sprsht_VfxSNB_Jump");
		break;
	case PlayerEffect_TYPE::LANDING:
		Animator2D()->Play(L"Sprsht_VfxSNB_Landing");
		break;
	case PlayerEffect_TYPE::WALLJUMP:
		if (bLp)
			Animator2D()->Play(L"Sprsht_VfxSNB_WallJump_rp");
		else
			Animator2D()->Play(L"Sprsht_VfxSNB_WallJump");
		break;
	case PlayerEffect_TYPE::WALLSLIDING:
		if (bLp)
			Animator2D()->Play(L"Sprsht_VfxSNB_WallClimbDown");
		else
			Animator2D()->Play(L"Sprsht_VfxSNB_WallClimbDown_rp");
		break;
	case PlayerEffect_TYPE::ATTACKDONUT:
		if (bLp)
			Animator2D()->Play(L"Sprsht_VfxSNB_Dash");
		else
			Animator2D()->Play(L"Sprsht_VfxSNB_Dash_rp");
		break;
	case PlayerEffect_TYPE::GRABSHOTGAS:
		if (bLp)
			Animator2D()->Play(L"Sprsht_VfxSNB_ShootGas_rp");
		else
			Animator2D()->Play(L"Sprsht_VfxSNB_ShootGas");
		break;
	case PlayerEffect_TYPE::GRABSHOTFIRE:
		if (bLp)
			Animator2D()->Play(L"Sprsht_VfxSNB_ShootMuzzleFire");
		else
			Animator2D()->Play(L"Sprsht_VfxSNB_ShootMuzzleFire_rp");
		break;
	case PlayerEffect_TYPE::DAMAGETILE:
		break;
	case PlayerEffect_TYPE::ENEMYATTACK:
			Animator2D()->Play(L"Sprsht_VfxSNB_ExcBomb");
		break;
	default:
		break;
	}
}
