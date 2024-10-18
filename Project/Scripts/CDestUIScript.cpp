#include "pch.h"
#include "CDestUIScript.h"

#include "CSearchBarScript.h"
#include "CGrabScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>


CDestUIScript::CDestUIScript()
	: CScript(DESTUISCRIPT)
{
}

CDestUIScript::~CDestUIScript()
{
}

void CDestUIScript::begin()
{
	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Dest.png", L"texture\\Player\\Dest.png");
	Animator2D()->Create(L"Dest", pAltasTex, Vec2(0.f, 0.f), Vec2(43.f, 44.f), Vec2(0.f, 0.f), Vec2(93.f, 94.f), 1, 10, false);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Dest_Enemy.png", L"texture\\Player\\Dest_Enemy.png");
	Animator2D()->Create(L"Dest_Enemy", pAltasTex, Vec2(0.f, 0.f), Vec2(43.f, 44.f), Vec2(0.f, 0.f), Vec2(93.f, 94.f), 1, 10, false);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);



	Animator2D()->Play(L"Dest");
}

void CDestUIScript::tick()
{
	CGameObject* pSearch = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SearchBar");
	Vec3 vPos = {};
	if (pSearch != nullptr)
		vPos = pSearch->GetScript<CSearchBarScript>()->GetSearchObjPos();
	CGameObject* pGrab = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Grab");

	

	if (vPos == Vec3{} || pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::NOTHING)
	{
		Animator2D()->Play(L"NONE");
	}
	else if (pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::ENEMY)
	{
		Animator2D()->Play(L"Dest_Enemy");
	}
	else if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::NOT&&
		(pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::CARGO || pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::ENABLED))
	{
		Animator2D()->Play(L"Dest");
	}

	Transform()->SetRelativePos(Vec3(vPos));


}

void CDestUIScript::SaveToFile(FILE* _File)
{
}

void CDestUIScript::LoadFromFile(FILE* _File)
{
}


