#include "pch.h"
#include "CQTEScript.h"

CQTEScript::CQTEScript()
	: CScript(QTESCRIPT)
{
}

CQTEScript::~CQTEScript()
{
}

void CQTEScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\UI\\Spr_UI_QTE_Hold.anim");
	Animator2D()->CreateFromFile(L"animation\\UI\\Spr_UI_QTE_JustClick.anim");


	if (m_Type == QTE_TYPE::HOLD)
	{
		Animator2D()->Play(L"Spr_UI_QTE_Hold");
	}
	else
	{
		Animator2D()->Play(L"Spr_UI_QTE_JustClick");
	}
}

void CQTEScript::tick()
{

}

void CQTEScript::SaveToFile(FILE* _File)
{
}

void CQTEScript::LoadFromFile(FILE* _File)
{
}




