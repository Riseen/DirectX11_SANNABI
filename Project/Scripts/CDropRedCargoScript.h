#pragma once
#include <Engine/CScript.h>

enum class DROPREDCARGO_STATE
{
    NOT,
    SPAWN,
    IDLE,
    STEPPED,
    DESTROY
};

class CDropRedCargoScript :
    public CScript
{
private:
    DROPREDCARGO_STATE m_CurState;
    DROPREDCARGO_STATE m_PrevState;

    int m_iDir;

    
    float m_fDownSpeed;
    float m_fAccTime;
    float m_fSpawnTime;


    bool m_bDown;

private:
    void ChangeState();
   

public:
    void SetDropRedCargoState(DROPREDCARGO_STATE _state) { m_CurState = _state; }
    void SetDown(bool _bDown) { m_bDown = _bDown; }
    void Destroy();
    void SetDir(int _iDir) { m_iDir = _iDir; }

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CDropRedCargoScript);
public:
    CDropRedCargoScript();
    ~CDropRedCargoScript();
};

