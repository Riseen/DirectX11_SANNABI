#pragma once
#include "UI.h"

class CComponent;

class MenuUI :
    public UI
{
public:
    virtual void render() override;
    virtual void render_update() override;

private:
    void File();
    void Level();
    void GameObject();
    void Asset();

private:
    CComponent* GetComponent(const char& _ComponentName);

public:
    MenuUI();
    ~MenuUI();
};

