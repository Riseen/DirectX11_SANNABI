#include "pch.h"
#include "CMainFlashScript.h"

CMainFlashScript::CMainFlashScript()
	: CScript(MAINFLASHSCRIPT)
{
}

CMainFlashScript::~CMainFlashScript()
{
}

void CMainFlashScript::begin()
{
}

void CMainFlashScript::tick()
{
	Vec4 vColor = GetOwner()->Light2D()->GetLightInfo().vColor;



	if (vColor.x <= 0.f || vColor.y <= 0.f)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}




	vColor -= Vec4(1000.f * DT, 1000.f * DT, 666.6f * DT, vColor.w);


	GetOwner()->Light2D()->SetLightColor(vColor);
}

void CMainFlashScript::SaveToFile(FILE* _File)
{
}

void CMainFlashScript::LoadFromFile(FILE* _File)
{
}


bool CMainFlashScript::IsFinish()
{
	Vec4 vColor = GetOwner()->Light2D()->GetLightInfo().vColor;

	if (vColor.x <= 0.f || vColor.y <= 0.f)
		return true;
	else
		return false;
}