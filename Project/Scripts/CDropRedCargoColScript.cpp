#include "pch.h"
#include "CDropRedCargoColScript.h"
#include "CDropRedCargoScript.h"

#include "CPlayerScript.h"

CDropRedCargoColScript::CDropRedCargoColScript()
	: CScript(DROPREDCARGOCOLSCRIPT)
{
}

CDropRedCargoColScript::~CDropRedCargoColScript()
{
}

void CDropRedCargoColScript::begin()
{
}

void CDropRedCargoColScript::tick()
{
	Vec3 vPos = Transform()->GetWorldPos();

	if (vPos.y < -600.f)
	{
		GetOwner()->GetParent()->GetScript<CDropRedCargoScript>()->Destroy();
	}

}

void CDropRedCargoColScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetName() == L"Boss AT")
	{
		GetOwner()->GetParent()->GetScript<CDropRedCargoScript>()->Destroy();
	}

		if (_OtherObj->GetName() == L"ClimbBar" && !(_OtherObj->GetParent()->Gravity()->IsOnGround()))
		{
			CGameObject* Player = _OtherObj->GetParent();
			Player->Gravity()->SetSideGround(true);

			GetOwner()->GetParent()->GetScript<CDropRedCargoScript>()->SetDown(true);

			Vec2 vPlayerPos(Player->Transform()->GetWorldPos().x, Player->Transform()->GetWorldPos().y);
			Vec2 vPlayerScale(Player->Collider2D()->GetOffsetScale().x, Player->Collider2D()->GetOffsetScale().y);

			Vec2 vOffsetPos = _Collider->GetOffsetPos();
			Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
			Vec2 vScale = _Collider->GetOffsetScale();

			if (vPos.x + (vScale.x / 2.f) <= vPlayerPos.x)
			{
				float fValue = vPos.x + (vPlayerScale.x / 2.f + vScale.x / 2.f) + 2.f + vOffsetPos.x;

				Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
				Player->RigidBody()->SetVelocity(Vec2(0.f, Player->RigidBody()->GetVelocity().y));
				Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
			}
			else if (vPos.x - (vScale.x / 2.f) >= vPlayerPos.x)
			{
				float fValue = vPos.x - (vPlayerScale.x / 2.f + vScale.x / 2.f) - 2.f + vOffsetPos.x;


				Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
				Player->RigidBody()->SetVelocity(Vec2(0.f, Player->RigidBody()->GetVelocity().y));
				Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
			}

		}
	// playerÃæµ¹
		else if (_OtherObj->Gravity())
		{
			_OtherObj->Gravity()->SetOnGround(true);

			GetOwner()->GetParent()->GetScript<CDropRedCargoScript>()->SetDown(true);

			Vec2 vObjPos(_OtherObj->Transform()->GetWorldPos().x, _OtherObj->Transform()->GetWorldPos().y);
			Vec2 vObjScale = _OtherCollider->GetOffsetScale();
			Vec2 vOffsetPos = _Collider->GetOffsetPos();

			Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
			Vec2 vScale = _Collider->GetOffsetScale();

			m_CurOverlapDir = CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);

			switch (m_CurOverlapDir)
			{
			case OverlapDir::LEFT:
			{
				float fValue = (vPos.x) + (vObjScale.x / 2.f + vScale.x / 2.f) + 2.f + vOffsetPos.x;

				_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
			}
			break;
			case OverlapDir::RIGHT:
			{
				float fValue = (vPos.x) - (vObjScale.x / 2.f + vScale.x / 2.f) - 2.f + vOffsetPos.x;

				_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
			}
			break;
			case OverlapDir::UP:
			{
				float fLen = abs((vObjPos.y) - vPos.y);
				float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen + vOffsetPos.y;

				vObjPos = _OtherObj->Transform()->GetRelativePos();
				vObjPos.y += (fValue);

				if (_OtherObj->Gravity()->IsSideGround())
				{
					_OtherObj->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::IDLE);
				}

				GetOwner()->GetParent()->GetScript<CDropRedCargoScript>()->SetDropRedCargoState(DROPREDCARGO_STATE::STEPPED);

				_OtherObj->Transform()->SetRelativePos(Vec3(vObjPos.x, vObjPos.y, _OtherObj->Transform()->GetRelativePos().z));
			}
			break;
			case OverlapDir::DOWN:
			{
				float fLen = abs(vObjPos.y - vPos.y);
				float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen + vOffsetPos.y;

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

void CDropRedCargoColScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetName() == L"ClimbBar" && !(_OtherObj->GetParent()->Gravity()->IsOnGround()))
	{
		CGameObject* Player = _OtherObj->GetParent();
		Player->Gravity()->SetSideGround(true);

		Vec2 vPlayerPos(Player->Transform()->GetWorldPos().x, Player->Transform()->GetWorldPos().y);
		Vec2 vPlayerScale(Player->Collider2D()->GetOffsetScale().x, Player->Collider2D()->GetOffsetScale().y);

		Vec2 vOffsetPos = _Collider->GetOffsetPos();
		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		if (vPos.x + (vScale.x / 2.f) <= vPlayerPos.x)
		{
			float fValue = vPos.x + (vPlayerScale.x / 2.f + vScale.x / 2.f) + 2.f + vOffsetPos.x;

			Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}
		else if (vPos.x - (vScale.x / 2.f) >= vPlayerPos.x)
		{
			float fValue = vPos.x - (vPlayerScale.x / 2.f + vScale.x / 2.f) - 2.f + vOffsetPos.x;


			Player->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::CLIMB);
			Player->Transform()->SetRelativePos(Vec3(fValue, Player->Transform()->GetRelativePos().y, Player->Transform()->GetRelativePos().z));
		}

	}

	else if (_OtherObj->Gravity())
	{
		_OtherObj->Gravity()->SetOnGround(true);

		Vec2 vObjPos(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y);
		Vec2 vObjScale = _OtherCollider->GetOffsetScale();
		Vec2 vOffsetPos = _Collider->GetOffsetPos();

		Vec2 vPos(Transform()->GetWorldPos().x, Transform()->GetWorldPos().y);
		Vec2 vScale = _Collider->GetOffsetScale();

		m_CurOverlapDir = CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);

		switch (m_CurOverlapDir)
		{
		case OverlapDir::LEFT:
		{
			float fValue = vPos.x + (vObjScale.x / 2.f + vScale.x / 2.f) + 2.f + vOffsetPos.x;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::RIGHT:
		{
			float fValue = vPos.x - (vObjScale.x / 2.f + vScale.x / 2.f) - 2.f + vOffsetPos.x;

			_OtherObj->Transform()->SetRelativePos(Vec3(fValue, _OtherObj->Transform()->GetRelativePos().y, _OtherObj->Transform()->GetRelativePos().z));
		}
		break;
		case OverlapDir::UP:
		{
			float fLen = abs(vObjPos.y - vPos.y);
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen + vOffsetPos.y;

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
			float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen + vOffsetPos.y;

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

void CDropRedCargoColScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->Gravity())
		_OtherObj->Gravity()->SetOnGround(false);
	else if (_OtherObj->GetParent() && _OtherObj->GetParent()->Gravity())
	{
		if (_OtherObj->GetParent()->RigidBody()->GetCurUpDownState() == RIGIDBODY_UPDOWNSTATE::FALLING)
		{
			_OtherObj->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::FALLING);
		}
		else if (_OtherObj->GetParent()->RigidBody()->GetCurUpDownState() == RIGIDBODY_UPDOWNSTATE::JUMPING)
		{
			_OtherObj->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::JUMPING);
		}

		_OtherObj->GetParent()->Gravity()->SetSideGround(false);
	}
}

OverlapDir CDropRedCargoColScript::CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	return CScript::CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);
}

void CDropRedCargoColScript::SaveToFile(FILE* _File)
{
}

void CDropRedCargoColScript::LoadFromFile(FILE* _File)
{
}


