#pragma once
#include "CEntity.h"

// Black Board 
// State를 만들거나 동작할때 필요한정보들을 그때그때 가져오긴 비효율적이고 귀찮을것이다.

// 그래서 Black Board에 기록해두고 필요할때 꺼내 쓰는것인데
// FSM이 에셋이기에 공유가되며 값이 공유되는것이 아닌가 싶지만
// 실제 저장은 StateMachine이 하기에 값이 공유되지않음


// Black Board에 저장될만한 Data
enum class BB_DATA
{
    INT,
    FLOAT,
    VEC2,
    VEC3,
    VEC4,
    OBJECT,
};

struct tBlackboardData
{
    BB_DATA     Type;   // Type
    void*       pData;  // 실제 저장된 데이터의 주소
};

class CBlackboard :
    public CEntity
{
private:
    map<wstring, tBlackboardData>   m_mapBBData;


public:
    void AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _Data);
    void* GetBlackboardData(const wstring& _strKey);


    CLONE(CBlackboard);
public:
    CBlackboard();
    CBlackboard(const CBlackboard& _board);
    ~CBlackboard();
};

