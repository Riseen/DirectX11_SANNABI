#pragma once
#include "AssetUI.h"

class PrefabUI :
    public AssetUI
{
private:
    void Instantiate(Ptr<CPrefab> _Prefab, Vec3 _vWorldPos, int _layerIdx);

public:
    virtual void render_update() override;

public:
    PrefabUI();
    ~PrefabUI();
};

