#include "pch.h"
#include "CScript.h"

CScript::CScript(UINT _ScriptType)
	: CComponent(COMPONENT_TYPE::SCRIPT)
	, m_iScriptType(_ScriptType)
{
}

CScript::~CScript()
{
}

void CScript::Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _layerIdx)
{
	if (nullptr == _Prefab)
		return;

	CGameObject* pNewObj = _Prefab->Instantiate();

	pNewObj->Transform()->SetRelativePos(_vWorldPos);

	GamePlayStatic::SpawnGameObject(pNewObj, _layerIdx);
}

OverlapDir CScript::CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Vec2 ThisObjMin(-(_Collider->GetOffsetScale().x / 2.f), -(_Collider->GetOffsetScale().y / 2.f));
	Vec2 ThisObjMax(_Collider->GetOffsetScale().x / 2.f, _Collider->GetOffsetScale().y / 2.f);

	Vec2 OtherMin(-(_OtherCollider->GetOffsetScale().x / 2.f), -(_OtherCollider->GetOffsetScale().y / 2.f));
	Vec2 OtherMax(_OtherCollider->GetOffsetScale().x / 2.f, _OtherCollider->GetOffsetScale().y / 2.f);

	Vec3 n = _OtherObj->Transform()->GetWorldPos() - Transform()->GetWorldPos();

	Vec2 extentThis = (ThisObjMax - ThisObjMin) / 2;
	Vec2 extentOther = (OtherMax - OtherMin) / 2;

	double x_overlap = extentThis.x + extentOther.x - abs(n.x);
	double y_overlap = extentThis.y + extentOther.y - abs(n.y);

	if (x_overlap < 0 || y_overlap < 0)
		return OverlapDir::FAILED;

	if (x_overlap < y_overlap)
	{
		if (n.x < 0)
			return OverlapDir::RIGHT;
		else
			return OverlapDir::LEFT;
	}
	else
	{
		if (n.y < 0)
			return OverlapDir::DOWN;
		else
			return OverlapDir::UP;
	}
}

void CScript::SaveToFile(FILE* _File)
{

}

void CScript::LoadFromFile(FILE* _File)
{
}