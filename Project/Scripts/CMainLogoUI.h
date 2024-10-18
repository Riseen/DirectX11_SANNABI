#pragma once
#include <Engine/CScript.h>

enum class LOGO_STATE
{
    NONE,
    ADD,
    PLAY,
    MINUS
};


class CMainLogoUI :
    public CScript
{
private:
    LOGO_STATE m_LogoState;
    float m_fSpeed;
    float m_fAlpha;
    float m_fDuration;
    bool  m_bFinish;

public:
    void SetUI(float& _Alpha, float _Speed, float _Duration, float _DT, bool _Delete);

private:
    void PlayWPLogo(const wstring& _strAnimName, bool _bRepeat);
    void PlayNWLogo(const wstring& _strAnimName, bool _bRepeat);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainLogoUI);
public:
    CMainLogoUI();
    ~CMainLogoUI();
};

