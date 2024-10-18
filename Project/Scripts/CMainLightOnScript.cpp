#include "pch.h"
#include "CMainLightOnScript.h"
#include <Engine/CLight2D.h>
#include <Math.h>


CMainLightOnScript::CMainLightOnScript()
	: CScript(MAINLIGHTONSCRIPT)
	, m_fLightSpeed(50.f)
	, m_fLight_B_Speed(30.f)
	, m_vStartColor{ 5.f, 3.f, 3.f }
{
}

CMainLightOnScript::~CMainLightOnScript()
{
}



void CMainLightOnScript::begin()
{

}

void CMainLightOnScript::tick()
{
	Vec4 vColor = GetOwner()->Light2D()->GetLightInfo().vColor;

	if (vColor.x <= 0.f || vColor.y <= 0.f)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}

	float Speed = pow(m_fLightSpeed, 4) * 2e-7 + 1;
	float Speed_B = Speed / (m_fLightSpeed / m_fLight_B_Speed);


	m_fLightSpeed += 0.05f;
	m_fLight_B_Speed += 0.03f;

	vColor -= Vec4(DT * Speed, DT * Speed, DT * Speed_B, vColor.w);


	GetOwner()->Light2D()->SetLightColor(vColor);
}

void CMainLightOnScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fLightSpeed, sizeof(float), 1, _File);
	fwrite(&m_fLight_B_Speed, sizeof(float), 1, _File);
	fwrite(&m_vStartColor, sizeof(Vec3), 1, _File);
}

void CMainLightOnScript::LoadFromFile(FILE* _File)
{
	fread(&m_fLightSpeed, sizeof(float), 1, _File);
	fread(&m_fLight_B_Speed, sizeof(float), 1, _File);
	fread(&m_vStartColor, sizeof(Vec3), 1, _File);
}



bool CMainLightOnScript::IsFinish()
{
	Vec4 vColor = GetOwner()->Light2D()->GetLightInfo().vColor;

	if (vColor.x <= 0.f || vColor.y <= 0.f)
		return true;
	else
		return false;
}
