#pragma once
#include <Engine/CScript.h>

enum class QTE_TYPE
{
    PRESS,
    HOLD
};

class CQTEScript :
    public CScript
{
private:
    QTE_TYPE m_Type;


public:
    void SetQTEType(QTE_TYPE _type) { m_Type = _type; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CQTEScript);
public:
    CQTEScript();
    ~CQTEScript();
};

