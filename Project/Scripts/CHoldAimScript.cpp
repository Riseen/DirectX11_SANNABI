#include "pch.h"
#include "CHoldAimScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CHoldAimScript::CHoldAimScript()
	: CScript(HOLDAIMSCRIPT)
	, m_bHolding(false)
	, m_bPrevHolding(false)
	, m_vDir {}
{
}

CHoldAimScript::~CHoldAimScript()
{
}


void CHoldAimScript::begin()
{
	Ptr<CTexture> pAltasTex;

	Animator2D()->CreateFromFile(L"animation\\HUD\\Sprsht_HUD_Aim_Aimming.anim");
	Animator2D()->CreateFromFile(L"animation\\HUD\\Sprsht_HUD_Aim_AimStart.anim");

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->Play(L"NONE");
}

void CHoldAimScript::tick()
{
	CGameObject* pCursor = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Cursor");


	m_vDir = pCursor->Transform()->GetWorldPos() - GetOwner()->GetParent()->Transform()->GetWorldPos();
	m_vDir.Normalize();
	float fCosTheta = m_vDir.Dot(Vec3(0.f, 1.f, 0.f));
	float fRadian = acosf(fCosTheta);




	if (m_vDir.x >= 0)
		fRadian *= -1;

	Transform()->SetRelativePos(Vec3(m_vDir.x * 30.f,
		m_vDir.y * 30.f,
		Transform()->GetRelativePos().z));

	Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
		Transform()->GetRelativeRotation().y,
		fRadian));

	if (m_bHolding != m_bPrevHolding)
	{
		if (m_bHolding)
			Animator2D()->PlayToPlay(L"Sprsht_HUD_Aim_AimStart", L"Sprsht_HUD_Aim_Aimming");
		else
			Animator2D()->Play(L"NONE");
	}


	m_bPrevHolding = m_bHolding;
}

void CHoldAimScript::SaveToFile(FILE* _File)
{
}

void CHoldAimScript::LoadFromFile(FILE* _File)
{
}



