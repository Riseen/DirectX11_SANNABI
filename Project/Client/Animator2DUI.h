#pragma once
#include "ComponentUI.h"

class Animator2DUI :
    public ComponentUI
{
private:
    bool bOpen;
    vector<wstring> AnimKey;
    char* combo_preview_value;
    int   m_iCurrent_index;

private:
    void AnimComboBox();


public:
    virtual void render_update() override;


public:
    Animator2DUI();
    ~Animator2DUI();
};

