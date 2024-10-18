#include "pch.h"
#include "CGravity.h"

CGravity::CGravity()
	: CComponent(COMPONENT_TYPE::GRAVITY)
	, m_fGravity (-700.f)
{
}

CGravity::~CGravity()
{
}



void CGravity::begin()
{
}

void CGravity::finaltick()
{
	if (!m_bOnGround && !m_bGrab && !m_bSideGround)
	{
		RigidBody()->SetAccelAlpha(Vec2(0.f, m_fGravity));
	}
}

void CGravity::SaveToFile(FILE* _File)
{
	fwrite(&m_bOnGround, sizeof(bool), 1, _File);
	fwrite(&m_bSideGround, sizeof(bool), 1, _File);
	fwrite(&m_bGrab, sizeof(bool), 1, _File);
	fwrite(&m_fGravity, sizeof(float), 1, _File);
}

void CGravity::LoadFromFile(FILE* _File)
{
	fread(&m_bOnGround, sizeof(bool), 1, _File);
	fread(&m_bSideGround, sizeof(bool), 1, _File);
	fread(&m_bGrab, sizeof(bool), 1, _File);
	fread(&m_fGravity, sizeof(float), 1, _File);
}

void CGravity::SetOnGround(bool _bOnGround)
{
	m_bOnGround = _bOnGround;
	if (m_bOnGround && !m_bGrab)
	{
		Vec2 vV = RigidBody()->GetVelocity();
		RigidBody()->SetVelocity(Vec2(vV.x, 0.f));
	}
}

void CGravity::SetSideGround(bool _bSideGround)
{
	m_bSideGround = _bSideGround;
	if (m_bSideGround && !m_bGrab)
	{
		Vec2 vV = RigidBody()->GetVelocity();
		RigidBody()->SetVelocity(Vec2(vV.x, 0.f));
	}
}

void CGravity::SetGrab(bool _bGrab)
{
	m_bGrab = _bGrab;
}


