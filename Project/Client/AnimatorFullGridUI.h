#pragma once
#include "UI.h"


class AnimatorFullGridUI :
    public UI
{
private:
    ImVec2 m_vCurMousePos;
    ImVec2 m_vGridSize;
    ImVec2 m_vCrossSize;

public:
    virtual void render_update() override;
    virtual void Deactivate() override;

public:
    AnimatorFullGridUI();
    ~AnimatorFullGridUI();
};


