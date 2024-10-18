#pragma once
#include "ComponentUI.h"

class CameraUI :
    public ComponentUI
{
private:
    bool  m_bLayerCheck[LAYER_MAX];

public:
    virtual void render_update() override;
public:
    CameraUI();
    ~CameraUI();
};

