#include "pch.h"
#include "CCapeScript.h"

CCapeScript::CCapeScript()
	: CScript(CAPESCRIPT)
{

}

CCapeScript::~CCapeScript()
{
}

void CCapeScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Cape.png", L"texture\\Player\\Spr_SNB_Cape.png");
	Animator2D()->Create(L"CAPE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Cape_rp.png", L"texture\\Player\\Spr_SNB_Cape_rp.png");
	Animator2D()->Create(L"CAPE_RP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);


}

void CCapeScript::tick()
{
}

void CCapeScript::SaveToFile(FILE* _File)
{
}

void CCapeScript::LoadFromFile(FILE* _File)
{
}

void CCapeScript::ChangeState(PLAYER_STATE _curPlayerState, PLAYER_STATE _prevPlayerState, bool _bLp, bool _bPrevLp)
{
	if (_curPlayerState == _prevPlayerState && _bLp == _bPrevLp)
		return;

	if (_curPlayerState == PLAYER_STATE::SWING)
	{
		if (_bLp)
			Animator2D()->Play(L"CAPE_LP");
		else
			Animator2D()->Play(L"CAPE_RP");
	}
	else
	{
		Animator2D()->Play(L"NONE");
	}

}


