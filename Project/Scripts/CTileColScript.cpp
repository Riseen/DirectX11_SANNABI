#include "pch.h"
#include "CTileColScript.h"

#include "CPlayerScript.h"

CTileColScript::CTileColScript()
	: CScript(TILECOLSCRIPT)
{
}

CTileColScript::~CTileColScript()
{
}


void CTileColScript::begin()
{
	// 부딪혔을때 타일타입따라 다른 상호작용
	// 위로 걷기 다른것처럼 정교하게 수정해야할듯
}

void CTileColScript::tick()
{
}

void CTileColScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (m_CurType == Tile_TYPE::Damage)
	{
		if (_OtherObj->GetScript<CPlayerScript>())
		{
			_OtherObj->GetScript<CPlayerScript>()->Damage(Transform()->GetWorldPos());
		}
	}
	else if (_OtherObj->GetName() == L"ClimbBar" && !(_OtherObj->GetParent()->Gravity()->IsOnGround())&& m_CurType == Tile_TYPE::Default)
	{
		CGameObject* Player = _OtherObj->GetParent();
		Player->Gravity()->SetSideGround(true);

		Vec2 vPlayerPos(Player->Transform()->GetWorldPos().x, Player->Transform()->GetWorldPos().y);
		Vec2 vPlayerScale(Player->Collider2D()->GetOffsetScale().x, Player->Collider2D()->GetOffsetScale().y);

		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		if (vPos.x + (vScale.x / 2.f) <= vPlayerPos.x)
		{
			float fValue = vPos.x + (vPlayerScale.x / 2.f + vScale.x / 2.f) + 2.f;
			Player->RigidBody()->SetVelocity(Vec2(0.f, Player->RigidBody()->GetVelocity().y));
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}
		else if (vPos.x - (vScale.x / 2.f) >= vPlayerPos.x)
		{
			float fValue = vPos.x - (vPlayerScale.x / 2.f + vScale.x / 2.f) - 2.f;
			Player->RigidBody()->SetVelocity(Vec2(0.f, Player->RigidBody()->GetVelocity().y));
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}

		PLAYER_STATE p = Player->GetScript<CPlayerScript>()->GetCurPlayerState();

		if (Player->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::CLIMB_UP)
		{

		}
		else
		{
			Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
		}

	}
	// player충돌
	else if (_OtherObj->Gravity())
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
			float fValue = vPos.x + (vObjScale.x / 2.f + vScale.x / 2.f) + 2.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
			break;
		case OverlapDir::RIGHT:
		{
			float fValue = vPos.x - (vObjScale.x / 2.f + vScale.x / 2.f) - 2.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
			break;
		case OverlapDir::UP:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y += (fValue);

			if (_OtherObj->Gravity()->IsSideGround())
			{
				_OtherObj->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::IDLE);
			}

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
			break;
		case OverlapDir::DOWN:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			vObjPos = _OtherObj->Transform()->GetRelativePos();
			vObjPos.y -= (fValue + 1.f);

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
			break;
		default:
			break;
		}

	}
}

void CTileColScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetName() == L"ClimbBar" && !(_OtherObj->GetParent()->Gravity()->IsOnGround()) && m_CurType == Tile_TYPE::Default)
	{
		CGameObject* Player = _OtherObj->GetParent();
		Player->Gravity()->SetSideGround(true);

		Vec2 vPlayerPos(Player->Transform()->GetWorldPos().x, Player->Transform()->GetWorldPos().y);
		Vec2 vPlayerScale(Player->Collider2D()->GetOffsetScale().x, Player->Collider2D()->GetOffsetScale().y);

		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		if (vPos.x + (vScale.x / 2.f) <= vPlayerPos.x)
		{
			float fValue = vPos.x + (vPlayerScale.x / 2.f + vScale.x / 2.f) + 2.f;
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}
		else if (vPos.x - (vScale.x / 2.f) >= vPlayerPos.x)
		{
			float fValue = vPos.x - (vPlayerScale.x / 2.f + vScale.x / 2.f) - 2.f;
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}

		if (Player->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::CLIMB_UP)
		{

		}
		else
		{
			Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
		}
	}

	else if (_OtherObj->Gravity())
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
			float fValue = vPos.x + (vObjScale.x / 2.f + vScale.x / 2.f) + 2.f;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::RIGHT:
		{
			float fValue = vPos.x - (vObjScale.x / 2.f + vScale.x / 2.f) - 2.f;



			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::UP:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			if (_OtherObj->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::SWING)
			{
				vObjPos = _OtherObj->Transform()->GetRelativePos();
				vObjPos.y += (fValue + 50.f);
			}
			else
			{
				vObjPos = _OtherObj->Transform()->GetRelativePos();
				vObjPos.y += (fValue);
			}

			if (_OtherObj->Gravity()->IsSideGround())
			{
				_OtherObj->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::IDLE);
			}

			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::DOWN:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

			if (_OtherObj->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::SWING)
			{
				vObjPos = _OtherObj->Transform()->GetRelativePos();
				vObjPos.y += (fValue + 50.f);
			}
			else
			{
				vObjPos = _OtherObj->Transform()->GetRelativePos();
				vObjPos.y -= (fValue + 15.f);
			}


			_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		default:
			break;
		}
	}
}

void CTileColScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->Gravity())
		_OtherObj->Gravity()->SetOnGround(false);
	else if (_OtherObj->GetParent() && _OtherObj->GetParent()->Gravity())
		_OtherObj->GetParent()->Gravity()->SetSideGround(false);
}

OverlapDir CTileColScript::CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	return CScript::CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);
}

void CTileColScript::SaveToFile(FILE* _File)
{
	fwrite(&m_CurType, sizeof(Tile_TYPE), 1, _File);
}

void CTileColScript::LoadFromFile(FILE* _File)
{
	fread(&m_CurType, sizeof(Tile_TYPE), 1, _File);
}

