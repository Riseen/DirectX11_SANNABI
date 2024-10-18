#include "pch.h"
#include "CCursorScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CEngine.h>

CCursorScript::CCursorScript()
	: CScript(CURSORSCRIPT)
{
}

CCursorScript::~CCursorScript()
{
}

void CCursorScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Cursor.png", L"texture\\UI\\Cursor.png");
	Animator2D()->Create(L"CURSOR", pAltasTex, Vec2(0.f, 0.f), Vec2(138.f, 139.f), Vec2(0.f, 0.f), Vec2(188.f, 189.f), 1, 10, false);

	Animator2D()->Play(L"CURSOR");
}

void CCursorScript::tick()
{
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

	Vec3 vPos = pMainCamera->Transform()->GetRelativePos()
		+ Vec3(CKeyMgr::GetInst()->GetMousePos().x, -CKeyMgr::GetInst()->GetMousePos().y, 0.f) 
		+ Vec3(-(CEngine::GetInst()->GetResolution().x / 2.f), (CEngine::GetInst()->GetResolution().y / 2.f), 0.f);
	Transform()->SetRelativePos(vPos);
}

void CCursorScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CCursorScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CCursorScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CCursorScript::SaveToFile(FILE* _File)
{
}

void CCursorScript::LoadFromFile(FILE* _File)
{
}




