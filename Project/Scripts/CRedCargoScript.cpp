#include "pch.h"
#include "CRedCargoScript.h"

#include "CPlayerScript.h"

CRedCargoScript::CRedCargoScript()
	: CScript(REDCARGOSCRIPT)
{
}

CRedCargoScript::~CRedCargoScript()
{
}

void CRedCargoScript::begin()
{
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Spr_CargoPlatform_Idle.png", L"texture\\Spr_CargoPlatform_Idle.png");
	Animator2D()->Create(L"RED_CARGO_IDLE", pAltasTex, Vec2(0.f, 0.f), Vec2(153.f, 81.f), Vec2(0.f, 0.f), Vec2(203.f, 131.f), 8, 10, false);

	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->Play(L"RED_CARGO_IDLE");
}

void CRedCargoScript::tick()
{

}

void CRedCargoScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
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
			float fValue = vPos.x +(vPlayerScale.x / 2.f + vScale.x / 2.f) + 2.f + vOffsetPos.x;

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

void CRedCargoScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
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

void CRedCargoScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
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

OverlapDir CRedCargoScript::CheckOverlapDir(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	return CScript::CheckOverlapDir(_Collider, _OtherObj, _OtherCollider);
}

void CRedCargoScript::SaveToFile(FILE* _File)
{
}

void CRedCargoScript::LoadFromFile(FILE* _File)
{
}



