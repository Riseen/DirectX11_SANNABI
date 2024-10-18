#pragma once
#include "UI.h"

class LevelOptUI :
    public UI
{
private:
    string m_LayerName[LAYER_MAX];

private:
    virtual void render_update() override;
    virtual void Deactivate() override;

public:
    LevelOptUI();
    ~LevelOptUI();
};

