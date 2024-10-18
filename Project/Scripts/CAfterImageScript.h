#pragma once
#include <Engine/CScript.h>

#include "CAfterImageManagerScript.h"

class CAfterImageScript :
    public CScript
{
private:
    AFTERIMAGE_TYPE m_CurState;
    bool            m_bLp;
    float           m_fDuration;
    float           m_fAccTime;


private:
    void AfterImageLoad(AFTERIMAGE_TYPE _type, bool _bLp);

public:
    void SetAfterImageState(AFTERIMAGE_TYPE _type) { m_CurState = _type; }
    void SetLp(bool _bLp) { m_bLp = _bLp; }


public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CAfterImageScript);
public:
    CAfterImageScript();
    ~CAfterImageScript();
};

