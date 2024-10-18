#include "pch.h"
#include "CAimmingRayScript.h"

CAimmingRayScript::CAimmingRayScript()
	: CScript(AIMMINGRAYSCRIPT)
	, m_fSpeed (6000.f)
	, m_vDir {}
	, m_vStartPos {}
	, m_vDestPos{}
	, m_fMaxDist (2000.f)
{
}

CAimmingRayScript::~CAimmingRayScript()
{
}

void CAimmingRayScript::begin()
{
	
}

void CAimmingRayScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos += Vec3(m_vDir.x * DT * m_fSpeed, m_vDir.y * DT * m_fSpeed, vPos.z);


	float fCur = pow((vPos.x - m_vStartPos.x), 2);
	float fArri = pow((vPos.y - m_vStartPos.y), 2);

	float fCurDist = sqrt(fCur + fArri);

	if (fCurDist >= m_fMaxDist)
	{
		Transform()->SetRelativePos(m_vStartPos);
		fCurDist = 0.f;
	}
	else
	{
		Transform()->SetRelativePos(vPos);
	}
}

void CAimmingRayScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	m_vDestPos = Transform()->GetWorldPos();
}

void CAimmingRayScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CAimmingRayScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CAimmingRayScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fMaxDist, sizeof(float), 1, _File);
}

void CAimmingRayScript::LoadFromFile(FILE* _File)
{
	fread(&m_fMaxDist, sizeof(float), 1, _File);
}



