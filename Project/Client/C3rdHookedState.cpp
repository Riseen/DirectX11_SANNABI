#include "pch.h"
#include "C3rdHookedState.h"

#include <Engine/CTimeMgr.h>
#include <Scripts/CBossScript.h>

C3rdHookedState::C3rdHookedState()
	: m_f3rdHookedTime(5.f)
	, m_fAccTime(0.f)
{
}

C3rdHookedState::~C3rdHookedState()
{
}


void C3rdHookedState::finaltick()
{
	//if (m_fAccTime > m_f3rdHookedTime)
	{

	}

	m_fAccTime += DT;
}

void C3rdHookedState::Enter()
{
}

void C3rdHookedState::Exit()
{
	m_fAccTime = 0.f;


}

