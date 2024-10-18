#pragma once
#include "CComponent.h"

#include "CFSM.h"
#include "CBlackboard.h"


// Finite State Machine (유한 상태 기계)

// StateMachine은 컴포넌트
// FSM은 리소스(Asset)

// 리소스 이기에 같은 Object들은 최대한 공유해서 사용가능하며
// 애니메이터와 유사하게 StateMachine에서 FSM이 현재 State를 재생하는 느낌으로 구조가 짜여있음

// Object - StateMachine - FSM(현재 State) - State들


class CStateMachine :
    public CComponent
{
private:
    // 원본 FSM
    Ptr<CFSM>       m_FSM;
    // 객체화하여 복사된 FSM
    // Play도중에는 StateMachine에서 일시적으로 동적 FSM을 받아 사용할것이다.
    // 원본 FSM을 공유해서 쓰는방식이기에 FSM의 상태를 변경하면 다른 Object에도 영향을 주기때문
    Ptr<CFSM>       m_FSM_Inst;

    CBlackboard     m_Blackboard;

public:
    void SetFSM(Ptr<CFSM> _FSM);
    // 현재 FSM반환 함수
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

