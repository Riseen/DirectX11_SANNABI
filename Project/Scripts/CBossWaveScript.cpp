#include "pch.h"
#include "CBossWaveScript.h"

CBossWaveScript::CBossWaveScript()
	: CScript(BOSSWAVESCRIPT)
	, m_fAccTime (0.f)
	, m_fAliveTime (1.f)
{
}

CBossWaveScript::~CBossWaveScript()
{
}


void CBossWaveScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Wave_Splash.anim");

	Animator2D()->Play(L"Spr_WOE_Wave_Splash");
}

void CBossWaveScript::tick()
{
	if (m_fAccTime >= m_fAliveTime)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}


	m_fAccTime += DT;
}

void CBossWaveScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBossWaveScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBossWaveScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBossWaveScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fAliveTime, sizeof(float), 1, _File);
}

void CBossWaveScript::LoadFromFile(FILE* _File)
{
	fread(&m_fAliveTime, sizeof(float), 1, _File);
}



