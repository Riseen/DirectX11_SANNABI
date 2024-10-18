#pragma once
#include <Engine/CScript.h>

class CHoldAimScript :
    public CScript
{
private:
    bool m_bHolding;
    bool m_bPrevHolding;
    Vec3 m_vDir;

public:
    Vec3 GetDir() { return m_vDir; }

    void SetHolding(bool _bHodling) { m_bHolding = _bHodling; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CHoldAimScript);
public:
    CHoldAimScript();
    ~CHoldAimScript();
};

