#include "pch.h"
#include "CIdleState.h"

#include <Engine/CGameObject.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>

CIdleState::CIdleState()
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::finaltick()
{
	CGameObject* p = GetFSM()->GetStateMachine()->GetOwner();

	
}

void CIdleState::Enter()
{

}

void CIdleState::Exit()
{

}