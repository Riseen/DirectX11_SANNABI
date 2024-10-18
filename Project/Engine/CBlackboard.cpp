#include "pch.h"
#include "CBlackboard.h"

CBlackboard::CBlackboard()
{
}

CBlackboard::CBlackboard(const CBlackboard& _board)
	: CEntity(_board)
	, m_mapBBData()
{
}

CBlackboard::~CBlackboard()
{
}

void CBlackboard::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);	// 추가하려는 Data가 이미 있을경우 assert

	assert(iter == m_mapBBData.end());

	m_mapBBData.insert(make_pair(_strKey, tBlackboardData{ _Type , _Data }));
}

void* CBlackboard::GetBlackboardData(const wstring& _strKey)
{
	map<wstring, tBlackboardData>::iterator iter = m_mapBBData.find(_strKey);

	if (iter == m_mapBBData.end())
		return nullptr;

	return iter->second.pData;
}
