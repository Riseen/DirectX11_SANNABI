#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"
#include "CKeyMgr.h"
#include "CFontMgr.h"

CTimeMgr::CTimeMgr()
	: m_Frequency{}
	, m_PrevCount{}
	, m_CurCount{}
	, m_Time(0.f)
	, m_DeltaTimeSpeed (1.0)
	, m_AccTime(0.)
	, m_bLock(true)
	, m_szText{}
{	

}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// �ʴ� ��
	QueryPerformanceFrequency(&m_Frequency);

	QueryPerformanceCounter(&m_PrevCount);
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&m_CurCount);

	m_EngineDeltaTime = m_DeltaTime = double(m_CurCount.QuadPart - m_PrevCount.QuadPart) / double(m_Frequency.QuadPart);

	if (m_DeltaTimeSpeed != 0.)
	{
		m_AccTime += m_EngineDeltaTime;
		m_DeltaTime *= m_DeltaTimeSpeed;
		if (m_AccTime >= m_DeltaTimeSpeed)
		{
			m_DeltaTimeSpeed = 1. ;
			m_AccTime = 0.;
		}
	}

	if (m_bLock)
	{
		m_DeltaTime = 0.f;
	}

	m_PrevCount = m_CurCount;

	// DT ����
	if ((1.f / 60.f) < m_DeltaTime)
		m_DeltaTime = (1. / 60.);

	// �ð� ���� ==> 1�ʸ��� if ���� ����
	m_Time += m_EngineDeltaTime;
	m_szText[50] = {};
	if (1.f <= m_Time)
	{		
		// 1�ʸ��� ���ŵȴ�.
		// �Ź� ���ŵǸ� �ð��� �ʹ� �����ϰ� ����
		swprintf_s(m_szText, 50, L"FPS : %d", m_iCall);
		m_iCall = 0;
		m_Time = 0.f;
	}

	++m_iCall;	
	g_global.g_dt = (float)m_DeltaTime;
	g_global.g_time += (float)m_DeltaTime;	
}

void CTimeMgr::render()
{
	//// ��Ʈ ���
	// tick�������� �׷����� clear�Ǽ� ����������
	CFontMgr::GetInst()->DrawFont(m_szText, 10.f, 30.f, 16, FONT_RGBA(10, 245, 245, 255));

	//

	//static wchar_t MousePos[256] = {};
	//
	//swprintf_s(MousePos, 256, L"MousePos.x : %f, MousePos.y : %f", CKeyMgr::GetInst()->GetMousePos().x, CKeyMgr::GetInst()->GetMousePos().y);
	//CFontMgr::GetInst()->DrawFont(MousePos, 10.f, 60.f, 16, FONT_RGBA(255, 30, 30, 255));

	//static wchar_t test[256] = {L"����!! ��ô�̱���~!!"};
	//CFontMgr::GetInst()->DrawFont(test, 10.f, 120.f, 50, FONT_RGBA(255, 255, 255, 255));
}