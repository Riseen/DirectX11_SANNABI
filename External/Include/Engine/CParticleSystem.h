#pragma once
#include "CRenderComponent.h"

#include "CParticleUpdate.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*      m_ParticleBuffer;
    UINT                    m_MaxParticleCount;

    tParticleModule         m_Module;
    CStructuredBuffer*      m_ParticleModuleBuffer;

    CStructuredBuffer*      m_SpawnCountBuffer;

    Ptr<CParticleUpdate>    m_CSParticleUpdate;

    Ptr<CTexture>           m_ParticleTex[3];

    float                   m_Time;

    int                     m_iParticleTexNum;

public:
    const tParticleModule& GetParticleModule() { return m_Module; }
    UINT GetMaxParticleCount() { return m_MaxParticleCount; }

    void SetParticleModule(tParticleModule _Module) { m_Module = _Module; }
    void SetMaxParticleCount(UINT _MaxCount) { m_MaxParticleCount = _MaxCount; }

    void SetParticleTexture(const wstring& _strKey, const wstring& _strRelativePath);
    Ptr<CTexture> GetParticleTexture() { return m_ParticleTex[0]; }

public:
    virtual void UpdateData() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CParticleSystem);
public:
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _OriginParticle);
    ~CParticleSystem();
};

