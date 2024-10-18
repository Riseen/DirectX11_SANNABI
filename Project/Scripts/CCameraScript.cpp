#include "pch.h"
#include "CCameraScript.h"
#include "CFadeInOutScript.h"

#include <Engine/CEngine.h>
#include <Engine/CCamera.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CCameraScript::CCameraScript()
	: CScript(CAMERASCRIPT)
	, m_CurShakeState(CAMERA_SHAKE_TYPE::NO)
	, m_vZoomPos {}
	, m_vMinMovePos{}
	, m_vMaxMovePos{}
	, m_fAccTime(0.f)
	, m_fShakeValue(0.f)
	, m_fShakeTime(0.f)
	, m_fZoomAccTime(0.f)
	, m_fZoomTime(0.f)
	, m_fZoomValue(0.f)
	, m_bShake(false)
	, m_bTimeZoom(false)
	, m_bZoomIn(false)
	, m_bZoomOut(false)
	, m_bCameraMoveDistLock(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Shake Value", &m_fShakeValue);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Shake Time", &m_fShakeTime);
}

CCameraScript::~CCameraScript()
{
}

void CCameraScript::begin()
{
	m_pFadeInOutObj = new CGameObject;
	m_pFadeInOutObj->SetName(L"FadeInout");

	m_pFadeInOutObj->AddComponent(new CTransform);
	m_pFadeInOutObj->AddComponent(new CMeshRender);
	m_pFadeInOutObj->AddComponent(new CFadeInOutScript);

	Vec2 vResolution = CEngine::GetInst()->GetResolution();

	m_pFadeInOutObj->Transform()->SetRelativePos(Vec3{});
	m_pFadeInOutObj->Transform()->SetRelativeScale(Vec3(vResolution.x, vResolution.y, 1.f));

	m_pFadeInOutObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	m_pFadeInOutObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"FadeInOutMtrl"));

	GamePlayStatic::SpawnGameObject(m_pFadeInOutObj, 2);

	/*if (CLevelMgr::GetInst()->GetCurLevelType() == LEVEL_TYPE::STAGE1)
		CameraMoveDistLock(Vec3(-4016.f, -4338.f, Transform()->GetRelativePos().z), Vec3(3620.f, 2603.f, Transform()->GetRelativePos().z));*/

	//if (CLevelMgr::GetInst()->GetCurLevelType() == LEVEL_TYPE::MAIN)
	//	CameraMoveDistLock(Vec3(-300.f, -300.f, Transform()->GetRelativePos().z), Vec3(258.f, 143.f, Transform()->GetRelativePos().z));
}

void CCameraScript::tick()
{
	m_pFadeInOutObj->Transform()->SetRelativePos(Transform()->GetRelativePos());

	Move();

	Zoom();

	if (m_bShake)
		Shake(m_fShakeValue, m_fShakeTime);
}

void CCameraScript::SaveToFile(FILE* _File)
{
}

void CCameraScript::LoadFromFile(FILE* _File)
{
}


void CCameraScript::ZoomIn(float _fValue)
{
	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() - DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() - DT_ENGINE * _fValue);
}

void CCameraScript::ZoomIn(float _fValue, Vec3 _vZoomPos)
{
	Transform()->SetRelativePos(_vZoomPos);

	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() - DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() - DT_ENGINE * _fValue);
}

void CCameraScript::ZoomIn(float _fValue, CGameObject* _ZoomObject)
{
	Vec3 vPos = _ZoomObject->Transform()->GetWorldPos();
	Transform()->SetRelativePos(vPos);

	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() - DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() - DT_ENGINE * _fValue);
}

void CCameraScript::ZoomOut(float _fValue)
{
	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() + DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() + DT_ENGINE * _fValue);
}

void CCameraScript::ZoomOut(float _fValue, Vec3 _vZoomPos)
{
	Transform()->SetRelativePos(_vZoomPos);

	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() + DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() + DT_ENGINE * _fValue);
}

void CCameraScript::ZoomOut(float _fValue, CGameObject* _ZoomObject)
{
	Vec3 vPos = _ZoomObject->Transform()->GetWorldPos();
	Transform()->SetRelativePos(vPos);

	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
		Camera()->SetScale(Camera()->GetScale() + DT_ENGINE * _fValue);
	else
		Camera()->SetFOV(Camera()->GetFOV() + DT_ENGINE * _fValue);
}

void CCameraScript::ZoomInWithTime(float _fValue, float _fTime)
{
	m_bTimeZoom = true;
	m_bZoomIn = true;
	m_bZoomOut = false;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;

	m_fFirstScale = Camera()->GetScale();
}

void CCameraScript::ZoomInWithTime(float _fValue, float _fTime, Vec3 _vZoomPos)
{
	m_bTimeZoom = true;
	m_bZoomIn = true;
	m_bZoomOut = false;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;
	m_vZoomPos = _vZoomPos;

	m_fFirstScale = Camera()->GetScale();
}

void CCameraScript::ZoomInWithTime(float _fValue, float _fTime, CGameObject* _ZoomObject)
{
	m_bTimeZoom = true;
	m_bZoomIn = true;
	m_bZoomOut = false;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;
	m_vZoomPos = _ZoomObject->Transform()->GetWorldPos();
}

void CCameraScript::ZoomOutWithTime(float _fValue, float _fTime)
{
	m_bTimeZoom = true;
	m_bZoomIn = false;
	m_bZoomOut = true;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;

	m_fFirstScale = Camera()->GetScale();
}

void CCameraScript::ZoomOutWithTime(float _fValue, float _fTime, Vec3 _vZoomPos)
{
	m_bTimeZoom = true;
	m_bZoomIn = false;
	m_bZoomOut = true;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;
	m_vZoomPos = _vZoomPos;

	m_fFirstScale = Camera()->GetScale();
}

void CCameraScript::ZoomOutWithTime(float _fValue, float _fTime, CGameObject* _ZoomObject)
{
	m_bTimeZoom = true;
	m_bZoomIn = false;
	m_bZoomOut = true;
	m_fZoomTime = _fTime;
	m_fZoomAccTime = 0.f;
	m_fZoomValue = _fValue;
	m_vZoomPos = _ZoomObject->Transform()->GetWorldPos();

	m_fFirstScale = Camera()->GetScale();
}

void CCameraScript::CameraMoveDistLock(Vec3 _vMin, Vec3 _vMax)
{
	m_bCameraMoveDistLock = true;

	m_vMinMovePos = _vMin;
	m_vMaxMovePos = _vMax;
}




void CCameraScript::FadeIn(float _fDuration, Vec3 _vColor)
{
	m_pFadeInOutObj->GetScript<CFadeInOutScript>()->FadeIn(_fDuration, _vColor);
}

void CCameraScript::FadeOut(float _fDuration)
{
	m_pFadeInOutObj->GetScript<CFadeInOutScript>()->FadeOut(_fDuration);
}

void CCameraScript::FadeInOut(float _fDuration, Vec3 _vColor)
{
	m_pFadeInOutObj->GetScript<CFadeInOutScript>()->FadeInOut(_fDuration, _vColor);
}

void CCameraScript::SetFocus(Vec3 _vPos)
{
	Transform()->SetRelativePos(_vPos);
}

void CCameraScript::SetFocus(CGameObject* _pObj)
{
	Vec3 vObjPos = _pObj->Transform()->GetWorldPos();
	Transform()->SetRelativePos(vObjPos);
}

void CCameraScript::Shake(float _fValue, float& _fDuration)
{
	if (m_fAccTime >= _fDuration)
	{
		_fDuration = 0.f;
		m_fAccTime = 0.f;
		m_bShake = false;
		m_CurShakeState = CAMERA_SHAKE_TYPE::NO;
		return;
	}

	Vec3 vPos = Transform()->GetRelativePos();

	static bool bChange = true;
	
	static int iChange = 0;

	if (iChange > 3)
		iChange = 0;

	static float y = 0.f;

	y = sin(m_fAccTime);


	switch (m_CurShakeState)
	{
	case CAMERA_SHAKE_TYPE::NO:
		break;
	case CAMERA_SHAKE_TYPE::LB_TO_RT:
	{
		if (bChange)
		{
			vPos.x += _fValue * y;
			vPos.y += _fValue * y;
			bChange = false;
		}
		else
		{
			vPos.x -= _fValue * y;
			vPos.y -= _fValue * y;
			bChange = true;
		}
	}
		break;
	case CAMERA_SHAKE_TYPE::LT_TO_RB:
	{
		if (bChange)
		{
			vPos.x -= _fValue * y;
			vPos.y += _fValue * y;
			bChange = false;
		}
		else
		{
			vPos.x += _fValue * y;
			vPos.y -= _fValue * y;
			bChange = true;
		}
	}
		break;
	case CAMERA_SHAKE_TYPE::FOURDIR_LT:
	{
		if (iChange == 0)
		{
			vPos.x += _fValue * y;
			vPos.y += _fValue * y;
			iChange = 1;
		}
		else if (iChange == 1)
		{
			vPos.x -= _fValue * y;
			vPos.y -= _fValue * y;
			iChange = 2;
		}
		else if (iChange == 2)
		{
			vPos.x += _fValue * y;
			vPos.y -= _fValue * y;
			iChange = 3;
		}
		else if (iChange == 3)
		{
			vPos.x -= _fValue * y;
			vPos.y += _fValue * y;
			iChange = 0;
		}
	}
		break;
	case CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM:
	{
		if (bChange)
		{
			vPos.y += _fValue * y;
			bChange = false;
		}
		else
		{
			vPos.y -= _fValue * y;
			bChange = true;
		}
	}
		break;
	case CAMERA_SHAKE_TYPE::LEFT_TO_RIGHT:
	{
		if (bChange)
		{
			vPos.x += _fValue * y;
			bChange = false;
		}
		else
		{
			vPos.x -= _fValue * y;
			bChange = true;
		}
	}
		break;
	case CAMERA_SHAKE_TYPE::FOURDIR_TOP:
	{
		if (iChange == 0)
		{
			vPos.x += _fValue * y;
			iChange = 1;
		}
		else if (iChange == 1)
		{
			vPos.x -= _fValue * y;
			iChange = 2;
		}
		else if (iChange == 2)
		{
			vPos.y -= _fValue * y;
			iChange = 3;
		}
		else if (iChange == 3)
		{
			vPos.y += _fValue * y;
			iChange = 0;
		}
	}
		break;
	default:
		break;
	}

	

	Transform()->SetRelativePos(vPos);

	m_fAccTime += DT;
}

void CCameraScript::Move()
{
	if (KEY_PRESSED(KEY::NUM1))
	{
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
			Camera()->SetScale(Camera()->GetScale() + DT * 0.2f);
		else
			Camera()->SetFOV(Camera()->GetFOV() + DT * 2.f);
	}

	if (KEY_PRESSED(KEY::NUM2))
	{
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
			Camera()->SetScale(Camera()->GetScale() - DT * 0.2f);
		else
			Camera()->SetFOV(Camera()->GetFOV() - DT * 2.f);
	}

	Vec3 vPos = Transform()->GetRelativePos();

	/*if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT * 800.f;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT * 800.f;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT * 800.f;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT * 800.f;
	}

	Transform()->SetRelativePos(vPos);

	return;*/

	//if (CLevelMgr::GetInst()->GetCurLevelType() != LEVEL_TYPE::MAIN && CLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY)
	if(CLevelMgr::GetInst()->GetCurrentLevel()->GetState() == LEVEL_STATE::PLAY)
	{
		Vec3 vPos = Transform()->GetRelativePos();

		CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
		if (pPlayer == nullptr)
			return;

		Vec3 vPlayerPos = pPlayer->Transform()->GetRelativePos();


		if (m_bCameraMoveDistLock)
		{
			Vec3 vFinalPos = Vec3(vPlayerPos.x, vPlayerPos.y + 200.f, vPlayerPos.z);

			if (vFinalPos.x < m_vMinMovePos.x)
			{
				vFinalPos = (Vec3(m_vMinMovePos.x, vFinalPos.y, vFinalPos.z));
			}
			if (vFinalPos.y < m_vMinMovePos.y)
			{
				vFinalPos = (Vec3(vFinalPos.x, m_vMinMovePos.y, vFinalPos.z));
			}

			if (vFinalPos.x > m_vMaxMovePos.x)
			{
				vFinalPos = (Vec3(m_vMaxMovePos.x, vFinalPos.y, vFinalPos.z));
			}
			if (vFinalPos.y > m_vMaxMovePos.y)
			{
				vFinalPos = (Vec3(vFinalPos.x, m_vMaxMovePos.y, vFinalPos.z));
			}

			Transform()->SetRelativePos(vFinalPos);
		}
		else
		{
			Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y + 200.f, vPlayerPos.z));
		}
	}
}

void CCameraScript::Zoom()
{
	if (!m_bTimeZoom)
		return;


	if (m_fZoomAccTime >= m_fZoomTime)
	{
		m_fZoomAccTime = 0.f;
		m_fZoomTime = 0.f;
		m_fZoomValue = 0.f;
		m_bTimeZoom = false;
		m_bZoomIn = false;
		m_bZoomOut = false;
		m_vZoomPos = Vec3{};
		m_fFirstScale = 0.f;
		return;
	}
	else
	{
		if (m_vZoomPos != Vec3{})
		{
			Transform()->SetRelativePos(m_vZoomPos);
		}

		if (m_bZoomIn)
		{
			if (Camera()->GetScale() <= 0.001f)
			{

			}
			else
			{
				float fZoomValue = m_fZoomValue * (m_fZoomAccTime / m_fZoomTime);

				if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
				{
					float fScale = Camera()->GetScale();
					fScale = m_fFirstScale - fZoomValue;

					Camera()->SetScale(fScale);
				}
			}
		}
		else if (m_bZoomOut)
		{
			float fZoomValue = m_fZoomValue * (m_fZoomAccTime / m_fZoomTime);

			if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
			{
				float fScale = Camera()->GetScale();
				fScale = m_fFirstScale + fZoomValue;

				Camera()->SetScale(fScale);
			}
		}

		m_fZoomAccTime += DT;
	}
	
}

void CCameraScript::MoveLock()
{
	if (!m_bCameraMoveDistLock)
		return;

	
}
