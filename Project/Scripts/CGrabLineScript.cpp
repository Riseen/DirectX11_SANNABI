#include "pch.h"
#include "CGrabLineScript.h"

CGrabLineScript::CGrabLineScript()
	: CScript(GRABLINESCRIPT)
{
}

CGrabLineScript::~CGrabLineScript()
{
}

void CGrabLineScript::begin()
{
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\String_Horiz_soft.png", L"texture\\Arm\\String_Horiz_soft.png");
	Animator2D()->Create(L"String_Horiz_soft", pAltasTex, Vec2(0.f, 0.f), Vec2(128.f, 128.f), Vec2(0.f, 0.f), Vec2(178.f, 178.f), 1, 10, false);

	Animator2D()->Play(L"String_Horiz_soft");
}

void CGrabLineScript::tick()
{
}

void CGrabLineScript::SaveToFile(FILE* _File)
{
}

void CGrabLineScript::LoadFromFile(FILE* _File)
{
}

