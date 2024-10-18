#include "pch.h"
#include "CDeathColScript.h"

#include "CPlayerScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CDeathColScript::CDeathColScript()
	: CScript(DEATHCOLSCRIPT)
{
}

CDeathColScript::~CDeathColScript()
{
}

void CDeathColScript::begin()
{
}

void CDeathColScript::tick()
{
}

void CDeathColScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	pPlayer->GetScript<CPlayerScript>()->SetHP(0);

}

void CDeathColScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDeathColScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CDeathColScript::SaveToFile(FILE* _File)
{
}

void CDeathColScript::LoadFromFile(FILE* _File)
{
}



