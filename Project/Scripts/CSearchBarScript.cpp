#include "pch.h"
#include "CSearchBarScript.h"

#include "CTileColScript.h"

CSearchBarScript::CSearchBarScript()
	: CScript(SEARCHBARSCRIPT)
	, m_CurSearchPri(SEARCH_PRIORITY::NOTHING)
	, m_PrevSearchPri(SEARCH_PRIORITY::NOTHING)
	, m_vSearchObjPos {}
	, m_vDir {}
	, m_fMaxDist (600.f)
	, m_bSearchActive(true)
{
}

CSearchBarScript::~CSearchBarScript()
{
}


void CSearchBarScript::begin()
{
	AddScriptParam(SCRIPT_PARAM::INT, "Search_Pri", &m_CurSearchPri);
}

void CSearchBarScript::tick()
{
	SearchRay(m_bSearchActive);

	m_PrevSearchPri = m_CurSearchPri;
}

void CSearchBarScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

	SetPosToLine(_Collider, _OtherObj, _OtherCollider);

	// Tile
	if (_OtherObj->GetLayerIdx() == 27 &&
		m_PrevSearchPri != SEARCH_PRIORITY::CARGO &&
		m_PrevSearchPri != SEARCH_PRIORITY::SWINGHOOK &&
		m_PrevSearchPri != SEARCH_PRIORITY::ENEMY)
	{
		if (_OtherObj->GetScript<CTileColScript>()->GetTileType() == Tile_TYPE::Default)
			m_CurSearchPri = SEARCH_PRIORITY::ENABLED;
		else
			m_CurSearchPri = SEARCH_PRIORITY::NOTHING;

		m_vSearchObj = _OtherObj;
	}
	// CARGO
	if (_OtherObj->GetLayerIdx() == 23 &&
		m_PrevSearchPri != SEARCH_PRIORITY::SWINGHOOK &&
		m_PrevSearchPri != SEARCH_PRIORITY::ENEMY)
	{
		m_CurSearchPri = SEARCH_PRIORITY::CARGO;

		m_vSearchObj = _OtherObj;
	}
	// Enemy
	if (_OtherObj->GetLayerIdx() == 8 || _OtherObj->GetLayerIdx() == 21)
	{
		m_CurSearchPri = SEARCH_PRIORITY::ENEMY;

		m_vSearchObj = _OtherObj;
	}
	else if (_OtherObj->GetLayerIdx() == 17)
	{
		m_CurSearchPri = SEARCH_PRIORITY::NOTHING;
		m_vSearchObj = nullptr;
	}
	
	m_vSearchObjPos = Transform()->GetWorldPos();
	

	Transform()->SetRelativePos(Vec3(0.f, 0.f, Transform()->GetRelativePos().z));
}

void CSearchBarScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CSearchBarScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CSearchBarScript::SaveToFile(FILE* _File)
{
}

void CSearchBarScript::LoadFromFile(FILE* _File)
{
}


void CSearchBarScript::SearchRay(bool _bActive)
{
	if (!m_bSearchActive)
		return;

	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vOwnerWorldpos = GetOwner()->GetParent()->Transform()->GetRelativePos();

	vPos += Vec3(m_vDir.x * DT * 3000.f, m_vDir.y * DT * 3000.f, vPos.z);


	float fCur = pow((vPos.x - vOwnerWorldpos.x), 2);
	float fArri = pow((vPos.y - vOwnerWorldpos.y), 2);

	float fCurDist = sqrt(fCur + fArri);

	if (fCurDist >= m_fMaxDist)
	{
		Transform()->SetRelativePos(Vec3(0.f, 0.f, vPos.z));
		fCurDist = 0.f;
		m_CurSearchPri = SEARCH_PRIORITY::NOTHING;
		m_vSearchObjPos = Vec3{};
	}
	else
	{
		Transform()->SetRelativePos(vPos);
	}
}

void CSearchBarScript::SetPosToLine(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	Vec3 vPos = Transform()->GetWorldPos();

	Vec3 vTargetObjpos = _OtherObj->Transform()->GetWorldPos();
	Vec3 vTargetObjScale = Vec3(_OtherCollider->GetOffsetScale().x, _OtherCollider->GetOffsetScale().y, 1.f);

	if(vPos.x > vTargetObjpos.x && vPos.y > vTargetObjpos.y)
	{
		if (IsRatioX(vPos.x, vTargetObjpos.x, vPos.y, vTargetObjpos.y))
		{
			m_CurGrabDir = GRAB_DIR::RIGHT;
		}
		else
		{
			m_CurGrabDir = GRAB_DIR::UP;
		}
	}
	else if (vPos.x < vTargetObjpos.x && vPos.y > vTargetObjpos.y)
	{
		if (IsRatioX(vPos.x, vTargetObjpos.x, vPos.y, vTargetObjpos.y))
		{
			m_CurGrabDir = GRAB_DIR::LEFT;
		}
		else
		{
			m_CurGrabDir = GRAB_DIR::UP;
		}
	}
	else if (vPos.x < vTargetObjpos.x && vPos.y < vTargetObjpos.y)
	{
		if (IsRatioX(vPos.x, vTargetObjpos.x, vPos.y, vTargetObjpos.y))
		{
			m_CurGrabDir = GRAB_DIR::LEFT;
			/*float fX = abs(vTargetObjpos.x - vTargetObjScale.x / 2.f) - abs(vPos.x);
			float fXRatio = abs(vTargetObjpos.x - vTargetObjScale.x / 2.f) - abs(fX);

			Vec3 vStartPos = GetOwner()->GetParent()->Transform()->GetWorldPos();

			float fX2Ratio = abs(vPos.x - vStartPos.x);
			fX2Ratio -= fXRatio;

			float fYRatio = fX / fX2Ratio;

			float fY2Ratio = abs(vPos.x - vStartPos.x);

			fY2Ratio *= fYRatio;

			m_vSearchObjPos = Vec3(vTargetObjpos.x - vTargetObjScale.x / 2.f, vPos.y - abs(fY2Ratio), Transform()->GetWorldPos().z);*/
		}
		else
		{
			m_CurGrabDir = GRAB_DIR::DOWN;
			/*float fY = abs(vTargetObjpos.y - vTargetObjScale.y / 2.f) - abs(vPos.y);
			float fYRatio = abs(vTargetObjpos.y - vTargetObjScale.y / 2.f) - abs(fY);

			Vec3 vStartPos = GetOwner()->GetParent()->Transform()->GetWorldPos();

			float fY2Ratio = abs(vPos.y - vStartPos.y);
			fY2Ratio -= fYRatio;

			float fXRatio = fY / fY2Ratio;

			float fX2Ratio = abs(vPos.x - vStartPos.x);

			fX2Ratio *= fXRatio;

			m_vSearchObjPos = Vec3(vPos.x - abs(fX2Ratio), vTargetObjpos.y - vTargetObjScale.y / 2.f, Transform()->GetWorldPos().z);*/
		}
	}
	else if (vPos.x > vTargetObjpos.x && vPos.y > vTargetObjpos.y)
	{
		if (IsRatioX(vPos.x, vTargetObjpos.x, vPos.y, vTargetObjpos.y))
		{
			m_CurGrabDir = GRAB_DIR::RIGHT;
		}
		else
		{
			m_CurGrabDir = GRAB_DIR::DOWN;
		}
	}
	


}

bool CSearchBarScript::IsRatioX(float _x, float _xStart, float _y, float _yStart)
{
	float xRatio = 0.f;
	float yRatio = 0.f;

	float x = abs(_x);
	float xStart = abs(_xStart);
	float y = abs(_y);
	float yStart = abs(_yStart);


	if (xStart == 0.f)
		xStart = 1.f;
	if (yStart == 0.f)
		yStart = 1.f;


	if (x > xStart)
	{
		xRatio = xStart / x;
	}
	else if (x <= xStart)
	{
		xRatio = x / xStart;
	}
	if (y > yStart)
	{
		yRatio = yStart / y;
	}
	else if (y <= yStart)
	{
		yRatio = y / yStart;
	}


	if (xRatio < yRatio)
		return true;
	else
		return false;
}



void CSearchBarScript::SetSearchAct(bool _bAct)
{
	m_bSearchActive = _bAct;

	if (!m_bSearchActive)
	{
		Vec3 vPos = Transform()->GetRelativePos();
		Transform()->SetRelativePos(Vec3(0.f, 0.f, vPos.z));
		m_CurSearchPri = SEARCH_PRIORITY::NOTHING;
	}
}
