#include "pch.h"
#include "CBulletScript.h"

#include "CPlayerScript.h"

#include <Engine\CAnimator2D.h>

CBulletScript::CBulletScript()
	: CScript(BULLETSCRIPT)
	, m_fSpeed(600.f)
	, m_vDir {}
	, m_fDeadTime(7.f)
	, m_fAccTime(0.f)
{
}

CBulletScript::~CBulletScript()
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Bullet Speed", &m_fSpeed);
}


void CBulletScript::begin()
{
	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Bullet.png", L"texture\\Bullet.png");
	Animator2D()->Create(L"Bullet", pAltasTex, Vec2(0.f, 0.f), Vec2(7.f, 32.f), Vec2(0.f, 0.f), Vec2(57.f, 82.f), 3, 10, false);

	Vec3 vRot = Transform()->GetRelativeRotation();

	float angle = acosf(m_vDir.Dot(Vec3(1.0f, 0.f, 0.f)) / m_vDir.Length());
	float fDE = XMConvertToDegrees(angle);
	fDE += 90.f;
	if (0.f < m_vDir.y)
	{
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, XMConvertToRadians(fDE)));
	}
	else
	{
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, -XMConvertToRadians(fDE)));
	}

	Animator2D()->Play(L"Bullet");
}

void CBulletScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos() + m_vDir * DT * m_fSpeed;


	if (m_fAccTime > m_fDeadTime)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}
	
	m_fAccTime += DT;

	Transform()->SetRelativePos(vPos);
}

void CBulletScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetLayerIdx() == 5 || _OtherObj->GetLayerIdx() == 27 || _OtherObj->GetLayerIdx() == 23)
	{
		if (_OtherObj->GetScript<CPlayerScript>() != nullptr)
		{
			if (_OtherObj->GetScript<CPlayerScript>()->IsGod())
			{

			}
		}
		else
			GamePlayStatic::DestroyGameObject(GetOwner());
	}
}

void CBulletScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBulletScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBulletScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
}

void CBulletScript::LoadFromFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
}



