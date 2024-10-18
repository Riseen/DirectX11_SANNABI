#pragma once
#include "CComponent.h"

#include "CFSM.h"
#include "CBlackboard.h"


// Finite State Machine (���� ���� ���)

// StateMachine�� ������Ʈ
// FSM�� ���ҽ�(Asset)

// ���ҽ� �̱⿡ ���� Object���� �ִ��� �����ؼ� ��밡���ϸ�
// �ִϸ����Ϳ� �����ϰ� StateMachine���� FSM�� ���� State�� ����ϴ� �������� ������ ¥������

// Object - StateMachine - FSM(���� State) - State��


class CStateMachine :
    public CComponent
{
private:
    // ���� FSM
    Ptr<CFSM>       m_FSM;
    // ��üȭ�Ͽ� ����� FSM
    // Play���߿��� StateMachine���� �Ͻ������� ���� FSM�� �޾� ����Ұ��̴�.
    // ���� FSM�� �����ؼ� ���¹���̱⿡ FSM�� ���¸� �����ϸ� �ٸ� Object���� ������ �ֱ⶧��
    Ptr<CFSM>       m_FSM_Inst;

    CBlackboard     m_Blackboard;

public:
    void SetFSM(Ptr<CFSM> _FSM);
    // ���� FSM��ȯ �Լ�
    Ptr<CFSM> GetFSM() 
    { 
        if (m_FSM_Inst.Get())
            return m_FSM_Inst;
        else
            return m_FSM;
    };

    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData);
    void* GetBlackboardData(const wstring& _strKey);


public:
    virtual void begin() override;
    virtual void finaltick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CStateMachine);
    CStateMachine();

    ~CStateMachine();
};

