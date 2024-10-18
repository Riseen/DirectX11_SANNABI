#include "pch.h"
#include "CBossP2AlertScript.h"

CBossP2AlertScript::CBossP2AlertScript()
	: CScript(BOSSP2ALERTSCRIPT)
	, m_fAccTime(0.f)
	, m_fAliveTime(2.f)
{

}

CBossP2AlertScript::~CBossP2AlertScript()
{
}

void CBossP2AlertScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_VFX_Pattern2_Alert.anim");

	Animator2D()->Play(L"Spr_WOE_VFX_Pattern2_Alert", false);
}

void CBossP2AlertScript::tick()
{
	if (m_fAccTime >= m_fAliveTime)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}



	m_fAccTime += DT;
}

void CBossP2AlertScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fAliveTime, sizeof(float), 1, _File);
}

void CBossP2AlertScript::LoadFromFile(FILE* _File)
{
	fread(&m_fAliveTime, sizeof(float), 1, _File);
}




