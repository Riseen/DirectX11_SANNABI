#include "pch.h"
#include "CFadeInOutScript.h"

CFadeInOutScript::CFadeInOutScript()
	: m_CurState(FADEINOUT_STATE::NOT)
	, CScript(FADEINOUTSCRIPT)
	, m_vColor{}
	, m_fAlpha ()
	, m_fAccTime ()
	, m_fDuration ()
	, m_bFadeInOut (false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Alpha", &m_fAlpha);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "AccTime", &m_fAccTime);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Duration", &m_fDuration);
}

CFadeInOutScript::~CFadeInOutScript()
{
}


void CFadeInOutScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

}

void CFadeInOutScript::tick()
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	
	if (m_CurState == FADEINOUT_STATE::FADEIN)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<float>(SCALAR_PARAM::FLOAT_0, m_fAlpha);
			pMtrl->SetScalarParam<Vec4>(SCALAR_PARAM::VEC4_0, Vec4(m_vColor.x, m_vColor.y, m_vColor.z, 1.f));
		}

		if (m_fAccTime > m_fDuration)
		{
			m_fAccTime = 0.f;
			

			if (m_bFadeInOut)
				m_CurState = FADEINOUT_STATE::FADEOUT;
			else
			{
				m_CurState = FADEINOUT_STATE::NOT;
				m_fDuration = 0.f;
			}

			m_fAlpha = 1.f;
		}
		else
		{
			m_fAlpha = m_fAccTime / m_fDuration;

			m_fAccTime += DT;
		}
	}
	else if (m_CurState == FADEINOUT_STATE::FADEOUT)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<float>(SCALAR_PARAM::FLOAT_0, m_fAlpha);
			pMtrl->SetScalarParam<Vec4>(SCALAR_PARAM::VEC4_0, Vec4(m_vColor.x, m_vColor.y, m_vColor.z, 1.f));
		}

		if (m_fAccTime > m_fDuration)
		{
			m_fAccTime = 0.f;
			m_fDuration = 0.f;
			m_CurState = FADEINOUT_STATE::NOT;
			m_fAlpha = 0.f;
			m_bFadeInOut = false;
		}
		else
		{
			float fAlpha = 1.f - (m_fAccTime / m_fDuration);
			if (fAlpha < 0.f)
				m_fAlpha = 0.f;
			else
				m_fAlpha = fAlpha;

			m_fAccTime += DT;
		}
	}
	else
	{
		
	}
}

void CFadeInOutScript::SaveToFile(FILE* _File)
{
}

void CFadeInOutScript::LoadFromFile(FILE* _File)
{
}




void CFadeInOutScript::FadeIn(float _fDuration, Vec3 _vColor)
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();


	m_fAlpha = 0.f;
	m_fDuration = _fDuration;
	m_vColor = _vColor;
	m_CurState = FADEINOUT_STATE::FADEIN;
}

void CFadeInOutScript::FadeOut(float _fDuration)
{
	m_fDuration = _fDuration;
	m_CurState = FADEINOUT_STATE::FADEOUT;
}

void CFadeInOutScript::FadeInOut(float _fDuration, Vec3 _vColor)
{
	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	m_fAlpha = 0.f;
	m_fDuration = _fDuration;
	m_vColor = _vColor;

	m_bFadeInOut = true;

	m_CurState = FADEINOUT_STATE::FADEIN;
}