#include "pch.h"
#include "CLight2D.h"

#include "CRenderMgr.h"
#include "CTransform.h"



CLight2D::CLight2D()
	: CComponent(COMPONENT_TYPE::LIGHT2D)
{
}

CLight2D::~CLight2D()
{

}

void CLight2D::finaltick()
{
	// 월드 위치값을 LightInfo 맴버에 갱신해놓는다.
	Vec3 vWorldPos = Transform()->GetWorldPos();
	m_Info.vWorldPos = vWorldPos;

	// Spot Light를 위해 Right벡터를 기준으로 방향 정보를 갱신한다.
	Vec3 vWorldRDir = Transform()->GetWorldDir(DIR_TYPE::RIGHT);
	m_Info.vWorldDir = vWorldRDir;

	// 광원 등록
	CRenderMgr::GetInst()->RegisterLight2D(this);
}

void CLight2D::SetLightType(LIGHT_TYPE _type)
{
	m_Info.LightType = (int)_type;
}

void CLight2D::SetRadius(float _Radius)
{
	wstring w = GetOwner()->GetName();
	tLightInfo* t = &m_Info;
	m_Info.fRadius = _Radius;
}

void CLight2D::SetAngle(float _Angle)
{
	m_Info.fAngle = _Angle;
}

void CLight2D::SaveToFile(FILE* _File)
{
	// Light구조체 저장
	fwrite(&m_Info, sizeof(tLightInfo), 1, _File);
}

void CLight2D::LoadFromFile(FILE* _File)
{
	fread(&m_Info, sizeof(tLightInfo), 1, _File);
}