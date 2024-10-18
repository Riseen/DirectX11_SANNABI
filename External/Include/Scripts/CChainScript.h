#pragma once
#include <Engine/CScript.h>

class CChainScript :
    public CScript
{
private:
    Vec3 m_vDestPos;
    Vec3 m_vStartPos;


public:
    void SetDestPos(Vec3 _vDestPos) { m_vDestPos = _vDestPos; }
    void SetStartPos(Vec3 _vStartPos) { m_vStartPos = _vStartPos; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CChainScript);
public:
    CChainScript();
    ~CChainScript();
};

