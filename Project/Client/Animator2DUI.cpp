#include "pch.h"
#include "Animator2DUI.h"

#include "AnimatorEditorUI.h"
#include  <Engine/CAssetMgr.h>
#include  <Engine/CAnimator2D.h>



Animator2DUI::Animator2DUI()
    : ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
    , bOpen(false)
    , m_iCurrent_index(0)
{
    SetSize(ImVec2(0.f, 120.f));
    SetComopnentTitle("Animator2D");
}

Animator2DUI::~Animator2DUI()
{

}




void Animator2DUI::render_update()
{
    ComponentUI::render_update();



    AnimComboBox();

    if (ImGui::Button("Load##Animation Load Btn", ImVec2(40.f, 20.f)))
    {
        GetTargetObject()->Animator2D()->CreateFromFile();
    }

    ImGui::SameLine();
    if (ImGui::Button("Edit##AnimEditor_Btn", ImVec2(40.f, 20.f)))
    {
        AnimatorEditorUI* pAnimEditor = (AnimatorEditorUI*)CImGuiMgr::GetInst()->FindUI("##AnimatorEditorUI");
        pAnimEditor->Activate();
    }

}

void Animator2DUI::AnimComboBox()
{
    //if (!bOpen)
    //{
    //    // 현재 TargetObject의 Animation목록 가져오기
    //    AnimKey = GetTargetObject()->Animator2D()->GetAnimKey();
    //    // 현재 TargetObject의 Current Animation 가져오기
    //    wstring wCurKey = GetTargetObject()->Animator2D()->GetCurAnimKey();

    //    for (int i = 0; i < AnimKey.size(); ++i)
    //    {
    //        if (AnimKey[i] == wCurKey)
    //        {
    //            m_iCurrent_index = i;
    //        }
    //    }
    //}

    //if (AnimKey.size() <= 0)
    //    return;

    //combo_preview_value = ToCChar(AnimKey[m_iCurrent_index]);


    //ImGui::Text("Animation"); ImGui::SameLine();
    //bOpen = ImGui::BeginCombo("##Animation List", combo_preview_value, 0);
    //if (bOpen)
    //{
    //    for (int i = 0; i < AnimKey.size(); i++)
    //    {
    //        const bool is_selected = (m_iCurrent_index == i);
    //        if (ImGui::Selectable(ToCChar(AnimKey[i]), is_selected))
    //        {
    //            m_iCurrent_index = i;
    //            GetTargetObject()->Animator2D()->Play(AnimKey[i]);
    //        }

    //        if (is_selected)
    //        {
    //            ImGui::SetItemDefaultFocus();
    //        }
    //    }
    //    ImGui::EndCombo();
    //}
}



