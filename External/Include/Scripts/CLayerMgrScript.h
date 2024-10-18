#pragma once
#include <Engine/CScript.h>

class CLayer;

class CLayerMgrScript :
    public CScript
{
private:
    CLayer* m_arrLayer[LAYER_MAX];
    UINT	m_matrix[LAYER_MAX];

private:

public:



public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CLayerMgrScript);
public:
    CLayerMgrScript();
    ~CLayerMgrScript();

};

