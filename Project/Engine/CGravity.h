#pragma once
#include "CComponent.h"
class CGravity :
    public CComponent
{
private:
    bool	 m_bOnGround;
    bool	 m_bSideGround;
    bool     m_bGrab;

    float    m_fGravity;

public:
    bool IsOnGround() { return m_bOnGround; }
    bool IsSideGround() { return m_bSideGround; }
    bool IsGrab() { return m_bGrab; }
    void SetOnGround(bool _bOnGround);
    void SetSideGround(bool _bSideGround);
    void SetGrab(bool _bGrab);
    void SetGravity(float _fGravity) { m_fGravity; }
    
    float GetGravity() { return m_fGravity; }


public:
    virtual void begin() override;
    virtual void finaltick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
public:
    CLONE(CGravity);
    CGravity();
    ~CGravity();
};

