#include "pch.h"
#include "CBombCargoScript.h"

CBombCargoScript::CBombCargoScript()
	: CScript(BOMBCARGOSCRIPT)
	, m_vStartPos {}
	, m_vEndPos {}
	, m_fCurDist (0.f)
	, m_fMaxDist (0.f)
	, m_fAccTime (0.f)
	, m_fStopTime (0.1f)
	, m_fSpeed (200.f)
{
}

CBombCargoScript::~CBombCargoScript()
{
}

void CBombCargoScript::begin()
{
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BombCargoDrone_Idle.anim");

	Vec3 vDist = m_vStartPos - m_vEndPos;
	m_fMaxDist = vDist.Length();

	

	Animator2D()->Play(L"Spr_WOE_BombCargoDrone_Idle");

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"BombCargoCol");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);

	pObj->Transform()->SetRelativePos(Vec3{});
	pObj->Transform()->SetRelativeScale(Vec3{1.f,1.f,1.f});

	pObj->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
	pObj->Collider2D()->SetOffsetScale(Vec2(176.f, 100.f));

	GetOwner()->AddChild(pObj);
}

void CBombCargoScript::tick()
{
	Move();
}

void CBombCargoScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombCargoScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombCargoScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBombCargoScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fStopTime, sizeof(float), 1, _File);
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CBombCargoScript::LoadFromFile(FILE* _File)
{
	fwrite(&m_fStopTime, sizeof(float), 1, _File);
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CBombCargoScript::Move()
{
	static bool bStartDest = true;
	static bool bEndDest = false;


	Vec3 vPos = Transform()->GetRelativePos();


	if (bStartDest)
	{
		vPos.y -= m_fSpeed * DT;
		Transform()->SetRelativePos(vPos);
	}
	else if (bEndDest)
	{
		vPos.y += m_fSpeed * DT;
		Transform()->SetRelativePos(vPos);
	}


	if (vPos.y >= m_vStartPos.y)
	{
		bStartDest = true;
		bEndDest = false;
	}
	else if (vPos.y <= m_vEndPos.y)
	{
		bStartDest = false;
		bEndDest = true;
	}
}

