#include "pch.h"
#include "CAfterImageScript.h"

#include "CPlayerScript.h"

CAfterImageScript::CAfterImageScript()
	: CScript(AFTERIMAGESCRIPT)
	, m_CurState(AFTERIMAGE_TYPE::NOT)
	, m_bLp(true)
	, m_fDuration(0.5f)
	, m_fAccTime(0.f)
{
}

CAfterImageScript::~CAfterImageScript()
{
}

void CAfterImageScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	AfterImageLoad(m_CurState, m_bLp);
}

void CAfterImageScript::tick()
{

	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	if (nullptr != pMtrl)
	{
		if (m_fDuration >= 0.f)
			pMtrl->SetScalarParam<float>(SCALAR_PARAM::FLOAT_0, m_fDuration);
	}

	

	if (m_fDuration <= 0.0f)
	{
		GamePlayStatic::DestroyGameObject(GetOwner());
	}

	m_fDuration -= DT;
}

void CAfterImageScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fDuration, sizeof(float), 1, _File);
}

void CAfterImageScript::LoadFromFile(FILE* _File)
{
	fread(&m_fDuration, sizeof(float), 1, _File);
}

void CAfterImageScript::AfterImageLoad(AFTERIMAGE_TYPE _type, bool _bLp)
{
	switch (_type)
	{
	case AFTERIMAGE_TYPE::NOT:
		break;
	case AFTERIMAGE_TYPE::SWING_DASH:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, 
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_Swing_VFX.png", L"texture\\particle\\Spr_SNB_Swing_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, 
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_Swing_rp_VFX.png", L"texture\\particle\\Spr_SNB_Swing_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_DOWN:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDDown_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDDown_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDDown_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDDown_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_FRONT:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDFront_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDFront_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDFront_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDFront_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_UP:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDUp_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDUp_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotGNDUp_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotGNDUp_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_AIR_DOWN:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRDown_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRDown_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRDown_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRDown_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_AIR_FRONT:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRFront_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRFront_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRFront_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRFront_rp_VFX.png"));
		break;
	case AFTERIMAGE_TYPE::SHOT_AIR_UP:
		if (_bLp)
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRUp_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRUp_VFX.png"));
		else
			MeshRender()->GetMaterial()->SetTexParam(TEX_PARAM::TEX_0,
				CAssetMgr::GetInst()->Load<CTexture>(L"texture\\particle\\Spr_SNB_ShotAIRUp_rp_VFX.png", L"texture\\particle\\Spr_SNB_ShotAIRUp_rp_VFX.png"));
		break;
	default:
		break;
	}

}


