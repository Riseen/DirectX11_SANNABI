#include "pch.h"
#include "CGrabTailScript.h"

CGrabTailScript::CGrabTailScript()
	: CScript(GRABTAILSCRIPT)
	, m_fAccTime(0.f)
	, m_fPlayTime(0.9f)
{

}

CGrabTailScript::~CGrabTailScript()
{
}

void CGrabTailScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->CreateFromFile(L"animation\\VFX\\Sprsht_VfxSNB_ExcDash.anim");

	Animator2D()->Play(L"Sprsht_VfxSNB_ExcDash",false);
}

void CGrabTailScript::tick()
{
	if (m_fAccTime > m_fPlayTime)
		GamePlayStatic::DestroyGameObject(GetOwner());

	m_fAccTime += DT;
}

void CGrabTailScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fPlayTime, sizeof(float), 1, _File);
}

void CGrabTailScript::LoadFromFile(FILE* _File)
{
	fread(&m_fPlayTime, sizeof(float), 1, _File);
}

