#include "pch.h"
#include "CHPUIScript.h"

#include "CPlayerScript.h"

CHPUIScript::CHPUIScript()	
	: CScript(HPUISCRIPT)
	, m_iCurHp(4)
	, m_iPrevHp(4)
	, m_fRecoveryTime (10.f)
	, m_fAccTime(0.f)
	, m_bDamage(false)
	, m_fIdleTime(5.f)
	, m_fidleAccTime(0.f)
	, m_bIdleTurn(false)
{
}

CHPUIScript::~CHPUIScript()
{
}

void CHPUIScript::begin()
{
	Ptr<CTexture> pAltasTex;

	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_4_Mini (lp).png", L"texture\\HUD\\Spr_HUD_HP4_4_Mini (lp).png");
		Animator2D()->Create(L"HP_4_4_MINI", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 1, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_4_Disappear.png", L"texture\\HUD\\Spr_HUD_HP4_4_Disappear.png");
		Animator2D()->Create(L"HP_4_4_DISAPPEAR", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 15, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_4_Idle.png", L"texture\\HUD\\Spr_HUD_HP4_4_Idle.png");
		Animator2D()->Create(L"HP_4_4_IDLE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_4_Restore.png", L"texture\\HUD\\Spr_HUD_HP4_4_Restore.png");
		Animator2D()->Create(L"HP_4_4_RESTORE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);
	}

	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_3_Idle.png", L"texture\\HUD\\Spr_HUD_HP4_3_Idle.png");
		Animator2D()->Create(L"HP_4_3_IDLE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_3_Damaged.png", L"texture\\HUD\\Spr_HUD_HP4_3_Damaged.png");
		Animator2D()->Create(L"HP_4_3_DAMAGED", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);

	/*	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_3_Restore.png", L"texture\\HUD\\Spr_HUD_HP4_3_Restore.png");
		Animator2D()->Create(L"HP_4_3_RESTORE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);*/
	}

	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_2_Idle.png", L"texture\\HUD\\Spr_HUD_HP4_2_Idle.png");
		Animator2D()->Create(L"HP_4_2_IDLE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_2_Damaged.png", L"texture\\HUD\\Spr_HUD_HP4_2_Damaged.png");
		Animator2D()->Create(L"HP_4_2_DAMAGED", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);

	/*	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_2_Restore.png", L"texture\\HUD\\Spr_HUD_HP4_2_Restore.png");
		Animator2D()->Create(L"HP_4_2_RESTORE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);*/
	}

	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_1_Idle.png", L"texture\\HUD\\Spr_HUD_HP4_1_Idle.png");
		Animator2D()->Create(L"HP_4_1_IDLE", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 13, 10, false);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_HUD_HP4_1_Damaged.png", L"texture\\HUD\\Spr_HUD_HP4_1_Damaged.png");
		Animator2D()->Create(L"HP_4_1_DAMAGED", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);
	}

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->Play(L"HP_4_4_MINI");
}

void CHPUIScript::tick()
{
	ChangeHPState();
	RotateReset();
	Recovery();
	TurnIdleMini();

	m_iPrevHp = m_iCurHp;
}


void CHPUIScript::ChangeHPState()
{
	if (m_iCurHp == m_iPrevHp)
		return;


	if (m_iCurHp < m_iPrevHp)
	{
		m_bDamage = true;
		m_fAccTime = 0.f;
	}


	switch (m_iCurHp)
	{
	case 0:
		Animator2D()->Play(L"NONE");
		break;
	case 1:
		if (m_iPrevHp == 2)
			Animator2D()->PlayToPlay(L"HP_4_1_DAMAGED", L"HP_4_1_IDLE");
		break;
	case 2:
		if (m_iPrevHp == 3)
			Animator2D()->PlayToPlay(L"HP_4_2_DAMAGED", L"HP_4_2_IDLE");
		break;
	case 3:
		if (m_iPrevHp == 4)
			Animator2D()->PlayToPlay(L"HP_4_3_DAMAGED", L"HP_4_3_IDLE");
		break;
	case 4:
		if (m_iPrevHp != 4)
		{
			Animator2D()->PlayToPlay(L"HP_4_4_RESTORE", L"HP_4_4_IDLE");
			m_bIdleTurn = true;
		}
		break;
	default:
		break;
	}
}

void CHPUIScript::RotateReset()
{
	Vec3 vRotParent = GetOwner()->GetParent()->Transform()->GetRelativeRotation();

	Vec3 vRot = Transform()->GetRelativeRotation();
	float fCurAngle = 0.f;
	float fDe = 0.f;
	Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, -vRotParent.z));
}

void CHPUIScript::Recovery()
{
	if (!m_bDamage)
		return;

	if (m_fAccTime > m_fRecoveryTime)
	{
		GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetHP(4);
		m_bDamage = false;
		m_fAccTime = 0.f;
		return;
	}

	m_fAccTime += DT;
}

void CHPUIScript::TurnIdleMini()
{
	if (!m_bIdleTurn)
		return;


	if (m_fidleAccTime > m_fIdleTime)
	{
		Animator2D()->PlayToPlay(L"HP_4_4_DISAPPEAR", L"HP_4_4_MINI");
		m_bIdleTurn = false;
		m_fidleAccTime = 0.f;
		return;
	}

	m_fidleAccTime += DT;
}

void CHPUIScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fRecoveryTime, sizeof(float), 1, _File);
	fwrite(&m_fIdleTime, sizeof(float), 1, _File);
	fwrite(&m_bIdleTurn, sizeof(bool), 1, _File);
	fwrite(&m_bDamage, sizeof(bool), 1, _File);
}

void CHPUIScript::LoadFromFile(FILE* _File)
{
	fread(&m_fRecoveryTime, sizeof(float), 1, _File);
	fread(&m_fIdleTime, sizeof(float), 1, _File);
	fread(&m_bIdleTurn, sizeof(bool), 1, _File);
	fread(&m_bDamage, sizeof(bool), 1, _File);
}

