#include "pch.h"
#include "CFinalCraneHookScript.h"

CFinalCraneHookScript::CFinalCraneHookScript()
	: CScript(FINALCRANEHOOKSCRIPT)
	, m_StartPos {}
	, m_fMaxDist(600.f)
	, m_fCurDist(0.f)
	, m_fCurAngle (0.f)
	, m_fCurMove (0.f)
{
}

CFinalCraneHookScript::~CFinalCraneHookScript()
{
}


void CFinalCraneHookScript::begin()
{
	m_StartPos = Transform()->GetRelativePos();

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Final_CraneHook.anim");

	Animator2D()->Play(L"Spr_WOE_Final_CraneHook");
}

void CFinalCraneHookScript::tick()
{
	HookMoveInit();
}

void CFinalCraneHookScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CFinalCraneHookScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CFinalCraneHookScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CFinalCraneHookScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fMaxDist, sizeof(float), 1, _File);
}

void CFinalCraneHookScript::LoadFromFile(FILE* _File)
{
	fread(&m_fMaxDist, sizeof(float), 1, _File);
}

void CFinalCraneHookScript::HookMoveInit()
{
	static float fLeftMaxAngle = 20.f;
	static float fRightMaxAngle = 30.f;
	static bool bLeftAngleDest = true;
	static bool bRightAngleDest = false;

	Vec3 vRot = Transform()->GetRelativeRotation();
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vDist = m_StartPos - vPos;
	m_fCurDist = vDist.Length();

	static float fSpeed = 100.f;
	//static float fMaxMove = 100.f;
	//static bool bLeftMoveDest = true;
	//static bool bRightMoveDest = false;

	if (bLeftAngleDest)
	{
		m_fCurAngle -= DT;
	}
	else if (bRightAngleDest)
	{
		m_fCurAngle += DT;
	}
	if (m_fCurAngle > bRightAngleDest)
	{
		bRightAngleDest = false;
		bLeftAngleDest = true;		
	}
	else if (m_fCurAngle < bLeftAngleDest)
	{
		bRightAngleDest = true;
		bLeftAngleDest = false;
	}

	

	if (m_fCurDist < m_fMaxDist)
		vPos.y -= fSpeed * DT;

	
	//vRot.z += XMConvertToRadians(m_fCurAngle);
	Transform()->SetRelativeRotation(vRot);
	Transform()->SetRelativePos(vPos);
}



