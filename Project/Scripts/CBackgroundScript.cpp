#include "pch.h"
#include "CBackgroundScript.h"

#include "CMainLightOnScript.h"
#include "CMainFlashScript.h"

CBackgroundScript::CBackgroundScript()
	: CScript(SCRIPT_TYPE::BACKGROUNDSCRIPT)
	, m_fAccTime(0.f)
	, m_State(BackGroundSTATE::START)
	, m_prevState(BackGroundSTATE::START)
{
}

CBackgroundScript::~CBackgroundScript()
{
}

void CBackgroundScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	m_BlueLEDTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_MainTitle_BlueLED.png", L"texture\\BackGround\\Spr_MainTitle_BlueLED.png");
	m_LightOffTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_MainTitle_LightOff.png", L"texture\\BackGround\\Spr_MainTitle_LightOff.png");
	m_LightOnTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\BackGround\\Spr_MainTitle_LightOn.png", L"texture\\BackGround\\Spr_MainTitle_LightOn.png");

	MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_BlueLEDTex);

	Transform()->SetRelativePos(Vec3(-600.f, 300.f, 600.f));

	GamePlayStatic::Play2DBGM(L"sound\\BGM\\BGM_Event_MainTheme.wav", 0.5f);
	//Transform()->SetRelativePos(Vec3(0.f, 0.f, 600.f));

	//// Light
	//CGameObject* pPointLight;

	//pPointLight = new CGameObject;
	//pPointLight->SetName(L"flash");

	//pPointLight->AddComponent(new CTransform);
	//pPointLight->AddComponent(new CLight2D);
	//pPointLight->AddComponent(new CMainLightOnScript);

	//pPointLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
	//pPointLight->Light2D()->SetLightColor(Vec3(9.f, 9.f, 7.f));
	//pPointLight->Light2D()->SetRadius(1000.f);

	//pPointLight->Transform()->SetRelativePos(Vec3(-230.f, 530.f, 300.f));

	//GamePlayStatic::SpawnGameObject(pPointLight, 5);
}

void CBackgroundScript::tick()
{
	//m_prevState = BackGroundSTATE::START;
	static int LightPattern = 0;
	m_fAccTime += DT;


	if (m_prevState != BackGroundSTATE::START)
	{
		if (m_fAccTime > 1.4f)
		{
			if (m_prevState == BackGroundSTATE::LIGHTON)
			{
				m_State = BackGroundSTATE::LIGHTOFF;
				LightPattern++;

				if (LightPattern >= 3)
				{
					m_fAccTime = 1.3f;
					LightPattern = 0;
				}
				else
					m_fAccTime = 0.f;

			}
			else if (m_prevState == BackGroundSTATE::LIGHTOFF)
			{
				m_State = BackGroundSTATE::LIGHTON;
				m_fAccTime = 1.3f;
			}
		}
	}


	static CGameObject* pPointLight = nullptr;
	static CGameObject* pFlashLight = nullptr;

	switch (m_State)
	{
	case BackGroundSTATE::START:
		if (m_fAccTime > 3.f && m_prevState == BackGroundSTATE::START)
		{
			Vec3 vPos = Transform()->GetRelativePos();

			if (vPos.x <= 0.f)
				vPos.x += 60.f * DT;
			if (vPos.y >= 0.f)
				vPos.y -= 30.f * DT;

			if (vPos.x >= 0.f && vPos.y <= 0.f)
			{
				m_State = BackGroundSTATE::LIGHTON;
				m_fAccTime = 0.f;

				GamePlayStatic::Play2DSound(L"sound\\UI\\SFX_TitleLightOn.wav", 1, 1.f);

				pFlashLight = new CGameObject;
				pFlashLight->SetName(L"Flash");

				pFlashLight->AddComponent(new CTransform);
				pFlashLight->AddComponent(new CLight2D);
				pFlashLight->AddComponent(new CMainFlashScript);

				pFlashLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
				pFlashLight->Light2D()->SetLightColor(Vec3(150.f, 150.f, 100.f));
				pFlashLight->Light2D()->SetRadius(1500.f);

				pFlashLight->Transform()->SetRelativePos(Vec3(-400.f, 530.f, 300.f));

				GamePlayStatic::SpawnGameObject(pFlashLight, 1);
			}

			Transform()->SetRelativePos(vPos);
		}
		break;
	case BackGroundSTATE::LIGHTON:
		if (m_prevState == BackGroundSTATE::START)
		{
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_LightOnTex);

			if (pPointLight == nullptr && pFlashLight->GetScript<CMainFlashScript>()->IsFinish())
			{
				// Light
				pPointLight = new CGameObject;
				pPointLight->SetName(L"LightOn");

				pPointLight->AddComponent(new CTransform);
				pPointLight->AddComponent(new CLight2D);
				pPointLight->AddComponent(new CMainLightOnScript);

				pPointLight->Light2D()->SetLightType(LIGHT_TYPE::POINT);
				pPointLight->Light2D()->SetLightColor(Vec3(5.f, 5.f, 3.f));
				pPointLight->Light2D()->SetRadius(1000.f);

				pPointLight->Transform()->SetRelativePos(Vec3(-211.f, 530.f, 300.f));

				GamePlayStatic::SpawnGameObject(pPointLight, 1);

			}

			if (pPointLight != nullptr && pPointLight->GetScript<CMainLightOnScript>()->IsFinish())
			{
				m_prevState = BackGroundSTATE::LIGHTON;
			}
		}
		else
		{
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_LightOnTex);
			m_prevState = BackGroundSTATE::LIGHTON;
		}
		break;
	case BackGroundSTATE::LIGHTOFF:
	{
		MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_LightOffTex);
		m_prevState = BackGroundSTATE::LIGHTOFF;
	}
	break;
	default:
		break;
	}
}

void CBackgroundScript::SaveToFile(FILE* _File)
{
}

void CBackgroundScript::LoadFromFile(FILE* _File)
{
}

bool CBackgroundScript::IsMainReady()
{
	if (m_prevState == BackGroundSTATE::START)
	{
		return false;
	}
	if (m_prevState == BackGroundSTATE::LIGHTOFF || m_prevState == BackGroundSTATE::LIGHTON)
	{
		return true;
	}
}