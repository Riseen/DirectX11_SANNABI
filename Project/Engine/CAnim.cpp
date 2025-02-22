#include "pch.h"
#include "CAnim.h"

#include "CTimeMgr.h"

#include "CDevice.h"
#include "CConstBuffer.h"

CAnim::CAnim()
	: m_Animator(nullptr)
	, m_CurFrmIdx(0)
	, m_bFinish(false)
	, m_AccTime(0.f)
{
}

CAnim::CAnim(const CAnim& _OriginAnim)
	: m_Animator(nullptr)
	, m_vecFrm(_OriginAnim.m_vecFrm)
	, m_CurFrmIdx(_OriginAnim.m_CurFrmIdx)
	, m_bFinish(_OriginAnim.m_bFinish)
	, m_AtlasTex(_OriginAnim.m_AtlasTex)
	, m_AccTime(_OriginAnim.m_AccTime)
{
}

CAnim::~CAnim()
{
}

void CAnim::finaltick()
{	
	m_AccTime += DT;

	if (m_vecFrm[m_CurFrmIdx].Duration < m_AccTime)
	{
		++m_CurFrmIdx;
		if (m_vecFrm.size() <= m_CurFrmIdx)
		{
			m_CurFrmIdx = (int)m_vecFrm.size() - 1;
			m_bFinish = true;
		}
		m_AccTime = 0.f;
	}
}

void CAnim::UpdateData()
{
	// 현재 프레임 정보를 상수버퍼로 옮기고 b2 레지스터로 바인딩
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 1;
	data.vLeftTop = m_vecFrm[m_CurFrmIdx].vLeftTop;
	data.vOffset = m_vecFrm[m_CurFrmIdx].vOffset;
	data.vSlizeSize = m_vecFrm[m_CurFrmIdx].vSlice;
	data.vBackGround = m_vecFrm[m_CurFrmIdx].vBackground;

	pCB->SetData(&data);
	pCB->UpdateData();

	// 아틀라스 텍스쳐 t10 에 바인딩
	m_AtlasTex->UpdateData(10);
}

void CAnim::Clear()
{
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::ANIM2D_DATA);
	tAnimData2D data = {};
	data.UseAnim2D = 0;

	pCB->SetData(&data);
	pCB->UpdateData();
}

void CAnim::Create(CAnimator2D* _Animator, Ptr<CTexture> _Atlas, Vec2 _vLeftTop
	, Vec2 _vSliceSize, Vec2 _vOffset, Vec2 _vBackground, int _FrmCount, float _FPS, bool _bRp)
{
	m_Animator = _Animator;
	m_AtlasTex = _Atlas;

	for (int i = 0; i < _FrmCount; ++i)
	{
		tAnimFrm frm = {};
				
		frm.vSlice = Vec2(_vSliceSize.x / (float)_Atlas->GetWidth(), _vSliceSize.y / (float)_Atlas->GetHeight());

		if (_bRp)
			frm.vLeftTop = Vec2(_vLeftTop.x / (float)_Atlas->GetWidth() - frm.vSlice.x * i, _vLeftTop.y / (float)_Atlas->GetHeight());
		else 
			frm.vLeftTop = Vec2(_vLeftTop.x / (float)_Atlas->GetWidth() + frm.vSlice.x * i, _vLeftTop.y / (float)_Atlas->GetHeight());

		frm.vOffset = Vec2(_vOffset.x / (float)_Atlas->GetWidth(), _vOffset.y / (float)_Atlas->GetHeight());
		frm.Duration = 1.f / _FPS;

		frm.vBackground = Vec2(_vBackground.x / (float)_Atlas->GetWidth(), _vBackground.y / (float)_Atlas->GetHeight());
	

		m_vecFrm.push_back(frm);
	}
}

void CAnim::Create(CAnimator2D* _Animator, char _szBuff[], FILE* _File)
{
	m_Animator = _Animator;

	string str;
	// 참조하는 텍스쳐 이름 및 경로
	FScanf(_szBuff, _File);
	FScanf(_szBuff, _File);

	str = _szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());


	FScanf(_szBuff, _File);
	FScanf(_szBuff, _File);

	str = _szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	// Texture Load
	Ptr<CTexture> pTex = CAssetMgr::GetInst()->Load<CTexture>(strTexKey, strTexPath);
	m_AtlasTex = pTex;

	// 프레임 개수
	FScanf(_szBuff, _File);
	int iFrameCount = 0;
	fscanf_s(_File, "%d", &iFrameCount);

	// 모든 프레임 정보
	tAnimFrm frm = {};
	for (int i = 0; i < iFrameCount; ++i)
	{
		POINT pt = {};

		while (true)
		{
			FScanf(_szBuff, _File);


			if (!strcmp("[Frame Index]", _szBuff))
			{
				fscanf_s(_File, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", _szBuff))
			{
				fscanf_s(_File, "%d", &pt.x);
				fscanf_s(_File, "%d", &pt.y);

				frm.vLeftTop = Vec2((float)pt.x / (float)m_AtlasTex->GetWidth(), (float)pt.y / (float)m_AtlasTex->GetHeight());
			}
			else if (!strcmp("[Slice Top]", _szBuff))
			{
				fscanf_s(_File, "%d", &pt.x);
				fscanf_s(_File, "%d", &pt.y);

				frm.vSlice = Vec2((float)pt.x / (float)m_AtlasTex->GetWidth(), (float)pt.y / (float)m_AtlasTex->GetHeight());
			}
			else if (!strcmp("[Offset]", _szBuff))
			{
				fscanf_s(_File, "%d", &pt.x);
				fscanf_s(_File, "%d", &pt.y);

				frm.vOffset = Vec2((float)pt.x / (float)m_AtlasTex->GetWidth(), (float)pt.y / (float)m_AtlasTex->GetHeight());
			}
			else if (!strcmp("[fDruation]", _szBuff))
			{
				fscanf_s(_File, "%f", &frm.Duration);
			}
			else if (!strcmp("[Background]", _szBuff))
			{
				fscanf_s(_File, "%d", &pt.x);
				fscanf_s(_File, "%d", &pt.y);

				frm.vBackground = Vec2((float)pt.x / (float)m_AtlasTex->GetWidth(), (float)pt.y / (float)m_AtlasTex->GetHeight());
				break;
			}
		}
		m_vecFrm.push_back(frm);
	}

	fclose(_File);


}


void CAnim::SaveToFile(FILE* _File)
{
	// 애니메이션 이름 저장
	SaveWString(GetName(), _File);
	
	// 모든 프레임 정보 저장
	size_t FrmSize = m_vecFrm.size();
	fwrite(&FrmSize, sizeof(size_t), 1, _File);
	fwrite(m_vecFrm.data(), sizeof(tAnimFrm), m_vecFrm.size(), _File);
	fwrite(&m_bFinish, sizeof(bool), 1, _File);

	// 애니메이션이 참조하던 텍스쳐 정보 저장
	SaveAssetRef(m_AtlasTex, _File);
}

void CAnim::LoadFromFile(FILE* _File)
{
	// 애니메이션 이름 로드
	wstring strName;
	LoadWString(strName, _File);
	SetName(strName);
	
	// 모든 프레임 정보 로드
	size_t FrmSize = 0;
	fread(&FrmSize, sizeof(size_t), 1, _File);
	m_vecFrm.resize(FrmSize);
	fread(m_vecFrm.data(), sizeof(tAnimFrm), m_vecFrm.size(), _File);
	fread(&m_bFinish, sizeof(bool), 1, _File);

	// 애니메이션이 참조하던 텍스쳐 정보 로드
	LoadAssetRef(m_AtlasTex, _File);
}
