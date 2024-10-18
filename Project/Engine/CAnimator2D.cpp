#include "pch.h"
#include "CAnimator2D.h"
#include "CAnim.h"

#include <commdlg.h>
#include "CEngine.h"

CAnimator2D::CAnimator2D()
	: CComponent(COMPONENT_TYPE::ANIMATOR2D)
	, m_CurAnim(nullptr)
	, m_CurAnimKey {}
	, m_NextAnimKey {}
	, m_bRepeat(true)
	, m_bNextRepeat(true)
{

}

CAnimator2D::CAnimator2D(const CAnimator2D& _OriginAnimator)
	: CComponent(_OriginAnimator)
	, m_CurAnim(nullptr)
	, m_bRepeat(_OriginAnimator.m_bRepeat)
{
	map<wstring, CAnim*>::const_iterator iter = _OriginAnimator.m_mapAnim.begin();
	for (; iter != _OriginAnimator.m_mapAnim.end(); ++iter)
	{
		CAnim* pCloneAnim = iter->second->Clone();

		pCloneAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(iter->first, pCloneAnim));
	}

	if (nullptr != _OriginAnimator.m_CurAnim)
	{
		m_CurAnim = FindAnim(_OriginAnimator.m_CurAnim->GetName());
	}
}

CAnimator2D::~CAnimator2D()
{
	Delete_Map(m_mapAnim);	
}

void CAnimator2D::finaltick()
{
	if (nullptr == m_CurAnim)
		return;

	if (m_CurAnim->IsFinish() && m_NextAnimKey.size() > 0)
	{
		CAnim* pAnim = FindAnim(m_NextAnimKey);
		if (nullptr == pAnim)
			return;

		m_bRepeat = m_bNextRepeat;

		m_CurAnim = pAnim;
		m_CurAnim->Reset();
	}
	else if (m_CurAnim->IsFinish() && m_bRepeat)
	{
		m_CurAnim->Reset();
	}

	m_CurAnim->finaltick();
}

void CAnimator2D::UpdateData()
{
	if (nullptr == m_CurAnim)
		return;

	m_CurAnim->UpdateData();
}

void CAnimator2D::Clear()
{	
	CAnim::Clear();
}

void CAnimator2D::Create(const wstring& _strKey, Ptr<CTexture> _AltasTex, Vec2 _LeftTop
	, Vec2 _vSliceSize, Vec2 _OffsetSize, Vec2 _Background, int _FrmCount, float _FPS, bool _bRp)
{
	CAnim* pAnim = FindAnim(_strKey);
	assert(!pAnim);

	pAnim = new CAnim;
	if (_bRp)
		_LeftTop.x -= _vSliceSize.x;

	pAnim->Create(this, _AltasTex, _LeftTop, _vSliceSize, _OffsetSize, _Background, _FrmCount, _FPS, _bRp);
	m_mapAnim.insert(make_pair(_strKey, pAnim));
}

void CAnimator2D::CreateFromFile()
{
	// Load 안된 텍스쳐의 경우 Load 해야하지만 일단 안해놓음


	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CEngine::GetInst()->GetMainWind();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"anim\0*";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();


	ofn.lpstrInitialDir = strAnimationFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;



	// 파일 열기
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = CPathMgr::GetRelativePath(szName);
		strAnimationFolder += strRelativePath;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, strAnimationFolder.c_str(), L"rb");
		assert(pFile);



		// Animation의 이름을 읽어온다.
		string str;
		char szBuff[256] = {};

		// Animation Name이 읽힘
		FScanf(szBuff, pFile);
		// 경로 정보가 읽힌다.
		FScanf(szBuff, pFile);
		str = szBuff;

		CAnim* pAnim = FindAnim(ToWString(str));
		assert(!pAnim);

		pAnim = new CAnim;
		pAnim->Create(this, szBuff, pFile);
		m_mapAnim.insert(make_pair(ToWString(str), pAnim));
	}
}

void CAnimator2D::CreateFromFile(const wstring& _strPath)
{
	wstring strAnimationFolder = CPathMgr::CPathMgr::GetContentPath();

	//wstring strRelativePath = CPathMgr::GetRelativePath(_strPath);
	strAnimationFolder += _strPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strAnimationFolder.c_str(), L"rb");
	assert(pFile);



	// Animation의 이름을 읽어온다.
	string str;
	char szBuff[256] = {};

	// Animation Name이 읽힘
	FScanf(szBuff, pFile);
	// 경로 정보가 읽힌다.
	FScanf(szBuff, pFile);
	str = szBuff;

	CAnim* pAnim = FindAnim(ToWString(str));
	assert(!pAnim);

	pAnim = new CAnim;
	pAnim->Create(this, szBuff, pFile);
	m_mapAnim.insert(make_pair(ToWString(str), pAnim));
	
}

CAnim* CAnimator2D::FindAnim(const wstring& _strKey)
{
	map<wstring, CAnim*>::iterator iter = m_mapAnim.find(_strKey);

	if (iter == m_mapAnim.end())
		return nullptr;

	return iter->second;
}

void CAnimator2D::Play(const wstring& _strAnimName, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_NextAnimKey = {};

	m_CurAnimKey = _strAnimName;

	m_bRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}

void CAnimator2D::PlayToPlay(const wstring& _strAnimName, const wstring& _strAnimName_Second, bool _bRepeat)
{
	CAnim* pAnim = FindAnim(_strAnimName);
	if (nullptr == pAnim)
		return;

	m_CurAnimKey = _strAnimName;
	m_NextAnimKey = _strAnimName_Second;

	m_bRepeat = false;
	m_bNextRepeat = _bRepeat;

	m_CurAnim = pAnim;
	m_CurAnim->Reset();
}

void CAnimator2D::SaveToFile(FILE* _File)
{
	// 애니메이션 개수 저장
	size_t AnimCount = m_mapAnim.size();
	fwrite(&AnimCount, sizeof(size_t), 1, _File);

	for (const auto& pair : m_mapAnim)
	{
		pair.second->SaveToFile(_File);
	}
	
	// 플레이 중이던 애니메이션의 키를 저장한다.
	wstring PlayAnimName;

	if (nullptr != m_CurAnim)
	{
		PlayAnimName = m_CurAnim->GetName();
	}

	SaveWString(PlayAnimName, _File);
	SaveWString(m_NextAnimKey, _File);
	fwrite(&m_bRepeat, sizeof(bool), 1, _File);
	fwrite(&m_bNextRepeat, sizeof(bool), 1, _File);
}

void CAnimator2D::LoadFromFile(FILE* _File)
{
	// 애니메이션 개수 로드
	size_t AnimCount = 0;
	fread(&AnimCount, sizeof(size_t), 1, _File);
		
	for (size_t i = 0; i < AnimCount; ++i)
	{
		CAnim* pAnim = new CAnim;
		pAnim->LoadFromFile(_File);

		pAnim->m_Animator = this;
		m_mapAnim.insert(make_pair(pAnim->GetName(), pAnim));		
	}

	// 플레이 중이던 애니메이션의 키를 불러온다
	wstring PlayAnimName;
	LoadWString(PlayAnimName, _File);

	if (!PlayAnimName.empty())
	{
		m_CurAnim = FindAnim(PlayAnimName);
	}

	LoadWString(m_NextAnimKey, _File);
	fread(&m_bRepeat, sizeof(bool), 1, _File);
	fread(&m_bNextRepeat, sizeof(bool), 1, _File);
}
