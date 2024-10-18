#pragma once
#include "CEntity.h"

// Black Board 
// State�� ����ų� �����Ҷ� �ʿ����������� �׶��׶� �������� ��ȿ�����̰� ���������̴�.

// �׷��� Black Board�� ����صΰ� �ʿ��Ҷ� ���� ���°��ε�
// FSM�� �����̱⿡ �������Ǹ� ���� �����Ǵ°��� �ƴѰ� ������
// ���� ������ StateMachine�� �ϱ⿡ ���� ������������


// Black Board�� ����ɸ��� Data
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
    void*       pData;  // ���� ����� �������� �ּ�
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

