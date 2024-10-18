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

    CFSM*                   m_Master;      // ������ FSM (���� FSM)
                                           // �� FSM�� nullptr�� �ƴҰ�쿣 ������� FSM�̶�� ���� �ȴ�.
    CStateMachine*          m_StateMachie; // FSM �� ����ϴ� StateMachine;

    map<wstring, CState*>   m_mapState;    // FSM���� �������� State��
    CBlackboard*            m_Blackboard;  // FSM BlackBoard

    CState*                 m_CurState;    // ���� State



public:
    void AddState(const wstring& _StateName, CState* _State);
    CState* FindState(const wstring& _StateName);
    void SetState(const wstring& _strState);
    void SetStateMachine(CStateMachine* _SM)
    { 
        // ������(����)�� �ƴҰ�쿡�� StateMachine��������
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

