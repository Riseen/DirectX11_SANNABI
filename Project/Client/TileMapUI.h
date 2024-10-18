#pragma once
#include "ComponentUI.h"

class TileMapUI :
    public ComponentUI
{
public:

private:
    virtual void render_update() override;

public:
    TileMapUI();
    ~TileMapUI();
};

