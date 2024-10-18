#pragma once
#include "ComponentUI.h"
class RigidBodyUI :
    public ComponentUI
{
public:
    virtual void render_update() override;
public:
    RigidBodyUI();
    ~RigidBodyUI();
};

