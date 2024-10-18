#pragma once
#include <Engine/CScript.h>

enum class ARM2LINE_STATE
{
    NOT,
    ACTIVE,
};


class CArmScript;

class CArmToGrabLineScript :
    public CScript
{
private:
    ARM2LINE_STATE m_CurState;
    ARM2LINE_STATE m_PrevState;

    vector<CGameObject*> m_Line;

    float m_fTerm;
    float m_fLineSize;

private:
    void ChangeState(Vec3 _vParent, Vec3 _vDestPos);
    void FirstCreate(Vec3 _vParent, Vec3 _vDestPos);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CArmToGrabLineScript);
public:
    CArmToGrabLineScript();
    ~CArmToGrabLineScript();
};

