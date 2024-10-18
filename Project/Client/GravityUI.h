#pragma once
#include "ComponentUI.h"
class GravityUI :
    public ComponentUI
{
public:
    virtual void render_update() override;
public:
    GravityUI();
    ~GravityUI();
};

