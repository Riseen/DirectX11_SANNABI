#pragma once
#include "ComponentUI.h"
class StateMachineUI :
    public ComponentUI
{
public:
    virtual void render_update() override;
public:
    StateMachineUI();
    ~StateMachineUI();
};

