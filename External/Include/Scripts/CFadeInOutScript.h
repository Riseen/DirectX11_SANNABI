#pragma once
#include <Engine/CScript.h>

enum class FADEINOUT_STATE
{
    NOT,
    FADEIN,
    FADEOUT,
};

class CFadeInOutScript :
    public CScript
{
private:
    FADEINOUT_STATE m_CurState;
    Vec3 m_vColor;

    float m_fAlpha;
    float m_fAccTime;
    float m_fDuration;

    bool  m_bFadeInOut;

public:
    void SetColor(Vec3 _vColor) { m_vColor = _vColor; }

    void FadeIn(float _fDuration, Vec3 _vColor);
    void FadeOut(float _fDuration);
    void FadeInOut(float _fDuration, Vec3 _vColor);

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CFadeInOutScript);
public:
    CFadeInOutScript();
    ~CFadeInOutScript();
};

