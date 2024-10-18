#include "pch.h"
#include "CMainLogoUI.h"

#include <Engine/CKeyMgr.h>

CMainLogoUI::CMainLogoUI()
	: CScript(MAINLOGOUI)
	, m_LogoState(LOGO_STATE::ADD)
	, m_fSpeed(0.5f)
	, m_fAlpha(0.f)
	, m_fDuration(1.f)
	, m_bFinish(false)
{
}

CMainLogoUI::~CMainLogoUI()
{
}

void CMainLogoUI::begin()
{
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\WP_LOGO_EX.png", L"texture\\UI\\WP_LOGO_EX.png");
	Animator2D()->Create(L"WP", pAltasTex, Vec2(0.f, 0.f), Vec2(31.f, 38.f), Vec2(0.f, 0.f), Vec2(31.f, 38.f), 8, 10, false);


	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Spr_Logo_NW.png", L"texture\\UI\\Spr_Logo_NW.png");
	Animator2D()->Create(L"NW", pAltasTex, Vec2(0.f, 0.f), Vec2(49.f, 59.f), Vec2(0.f, 0.f), Vec2(49.f, 59.f), 9, 10, false);

	GetRenderComponent()->GetDynamicMaterial();
}

void CMainLogoUI::tick()
{
	static bool WPFinish = false;


	if (!m_bFinish)
		PlayWPLogo(L"WP", false);
	else
		PlayNWLogo(L"NW", false);





	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	if (nullptr != pMtrl)
	{
		pMtrl->SetScalarParam<float>(SCALAR_PARAM::FLOAT_0, m_fAlpha);
	}
}

void CMainLogoUI::SaveToFile(FILE* _File)
{
	fwrite(&m_LogoState, sizeof(LOGO_STATE), 1, _File);
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
	fwrite(&m_bFinish, sizeof(bool), 1, _File);
}

void CMainLogoUI::LoadFromFile(FILE* _File)
{
	fread(&m_LogoState, sizeof(LOGO_STATE), 1, _File);
	fread(&m_fSpeed, sizeof(float), 1, _File);
	fread(&m_bFinish, sizeof(bool), 1, _File);
}

void CMainLogoUI::SetUI(float& _Alpha, float _Speed, float _Duration, float _DT, bool _Delete)
{

}

void CMainLogoUI::PlayWPLogo(const wstring& _strAnimName, bool _bRepeat)
{
	static float fAcc = 0.f;
	static bool  bAlpha = false;

	switch (m_LogoState)
	{
	case LOGO_STATE::NONE:
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png"));
		break;
	case LOGO_STATE::ADD:
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, CAssetMgr::GetInst()->Load<CTexture>(L"texture\\UI\\Spr_Logo_WPReady (lp).png", L"texture\\UI\\Spr_Logo_WPReady (lp).png"));
		m_fAlpha += DT * m_fSpeed;
		if (m_fAlpha >= 1.f)
		{
			m_LogoState = LOGO_STATE::PLAY;
		}
	}
	break;
	case LOGO_STATE::PLAY:
	{
		fAcc += DT;
		if (!bAlpha)
		{
			Animator2D()->Play(_strAnimName, _bRepeat);
			bAlpha = true;
		}
		if (fAcc > m_fDuration)
		{
			m_LogoState = LOGO_STATE::MINUS;
		}
	}
	break;
	case LOGO_STATE::MINUS:
	{
		m_fAlpha += DT * -m_fSpeed;
		if (m_fAlpha <= 0.f)
		{
			m_bFinish = true;
			m_LogoState = LOGO_STATE::ADD;
		}
	}
	break;
	default:
		break;
	}
}

void CMainLogoUI::PlayNWLogo(const wstring& _strAnimName, bool _bRepeat)
{
	static float fAcc = 0.f;
	static bool  bAlpha = false;

	switch (m_LogoState)
	{
	case LOGO_STATE::NONE:
		break;
	case LOGO_STATE::ADD:
	{
		Transform()->SetRelativeScale(Vec3(490.f / 3.f, 590.f / 3.f, 1.f));

		Animator2D()->Play(_strAnimName, _bRepeat);

		m_fAlpha += DT * m_fSpeed;
		if (m_fAlpha >= 1.f)
		{
			m_LogoState = LOGO_STATE::PLAY;
		}
	}
	break;
	case LOGO_STATE::PLAY:
	{
		fAcc += DT;
		if (!bAlpha)
		{
			bAlpha = true;
		}
		if (fAcc > m_fDuration)
		{
			m_LogoState = LOGO_STATE::MINUS;
		}
	}
	break;
	case LOGO_STATE::MINUS:
	{

		m_fAlpha += DT * -m_fSpeed;
		if (m_fAlpha <= 0.f)
		{
			GamePlayStatic::DestroyGameObject(GetOwner());
		}
	}
	break;
	default:
		break;
	}
}


