#include "pch.h"
#include "CClimbBarScript.h"

#include "CPlayerScript.h"

CClimbBarScript::CClimbBarScript()
	: CScript(CLIMBBARSCRIPT)
	, m_pOverlapObj(nullptr)
{

}

CClimbBarScript::~CClimbBarScript()
{
}

void CClimbBarScript::begin()
{
}

void CClimbBarScript::tick()
{
	if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->GetCurLP())
	{
		float X = Collider2D()->GetOffsetPos().x;
		if (X < 0)
			X *= -1;
		Collider2D()->SetOffsetPos(Vec2(X, Collider2D()->GetOffsetPos().y));
	}
	else
	{
		float X = Collider2D()->GetOffsetPos().x;
		if (X > 0)
			X *= -1;
		Collider2D()->SetOffsetPos(Vec2(X, Collider2D()->GetOffsetPos().y));
	}
}

void CClimbBarScript::SaveToFile(FILE* _File)
{
}

void CClimbBarScript::LoadFromFile(FILE* _File)
{
}



void CClimbBarScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	m_pOverlapObj = _OtherObj;
}

void CClimbBarScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CClimbBarScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

