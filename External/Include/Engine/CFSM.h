#pragma once
#include "CAsset.h"

#include "CState.h"
#include "CBlackboard.h"

class CStateMachine;

// FSM
class CFSM :
    public CAsset
{
private:

    CFSM*                   m_Master;      // 마스터 FSM (원본 FSM)
                                           // 이 FSM이 nullptr가 아닐경우엔 복사받은 FSM이라는 뜻이 된다.
    CStateMachine*          m_StateMachie; // FSM 을 사용하는 StateMachine;

    map<wstring, CState*>   m_mapState;    // FSM에서 보유중인 State들
    CBlackboard*            m_Blackboard;  // FSM BlackBoard

    CState*                 m_CurState;    // 현재 State



public:
    void AddState(const wstring& _StateName, CState* _State);
    CState* FindState(const wstring& _StateName);
    void SetState(const wstring& _strState);
    void SetStateMachine(CStateMachine* _SM)
    { 
        // 마스터(원본)가 아닐경우에만 StateMachine설정가능
        if (m_Master) 
        { 
            m_StateMachie = _SM; 
        } 
    }
    CFSM* GetFSMIstance();
    CState* GetCurState() { return m_CurState; }
    const wstring GetFSMKey() { return m_Master->GetKey(); }

    map<wstring, CState*> GetStates() { return m_mapState; }

    CStateMachine* GetStateMachine() { return m_StateMachie; }
    void ChangeState(const wstring& _strStateName);


public:
    void finaltick();

public:
    CLONE_DISABLE(CFSM);
    CFSM(bool _bEngine = false);    
    ~CFSM();
};

