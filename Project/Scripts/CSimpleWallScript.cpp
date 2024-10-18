#include "pch.h"
#include "CSimpleWallScript.h"

CSimpleWallScript::CSimpleWallScript()
    : CScript(SIMPLEWALLSCRIPT)
{
}

CSimpleWallScript::~CSimpleWallScript()
{
}


void CSimpleWallScript::begin()
{
}

void CSimpleWallScript::tick()
{
}

void CSimpleWallScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->Gravity())
	{
		_OtherObj->Gravity()->SetOnGround(true);

		Vec2 vObjPos(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y);
		Vec2 vObjScale = _OtherCollider->GetOffsetScale();

		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		m_CurOverlapDir = CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);

		switch (m_CurOverlapDir)
		{
		case OverlapDir::LEFT:
		{
			float fValue = vPos.x + (vObjScale.x / 2.f + vScale.x / 2.f) + 10.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::RIGHT:
		{
			float fValue = vPos.x - (vObjScale.x / 2.f + vScale.x / 2.f) - 10.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::UP:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y += (fValue);

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::DOWN:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y -= (fValue + 5.f);

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		default:
			break;
		}
	}
}

void CSimpleWallScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->Gravity())
	{
		_OtherObj->Gravity()->SetOnGround(true);

		Vec2 vObjPos(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y);
		Vec2 vObjScale = _OtherCollider->GetOffsetScale();

		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		m_CurOverlapDir = CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);

		switch (m_CurOverlapDir)
		{
		case OverlapDir::LEFT:
		{
			float fValue = vPos.x + (vObjScale.x / 2.f + vScale.x / 2.f) + 10.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::RIGHT:
		{
			float fValue = vPos.x - (vObjScale.x / 2.f + vScale.x / 2.f) - 10.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::UP:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y += (fValue);

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::DOWN:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y -= (fValue + 5.f);

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		default:
			break;
		}
	}

}

void CSimpleWallScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->Gravity())
		_OtherObj->Gravity()->SetOnGround(false);
}

OverlapDir CSimpleWallScript::CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    return CScript::CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);
}

void CSimpleWallScript::SaveToFile(FILE* _File)
{
}

void CSimpleWallScript::LoadFromFile(FILE* _File)
{
}


