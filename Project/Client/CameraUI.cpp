#include "pch.h"
#include "CameraUI.h"

#include <Engine/CCamera.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>


CameraUI::CameraUI()
    : ComponentUI("Camera", "##Camera", COMPONENT_TYPE::CAMERA)
    , m_bLayerCheck {}
{
    SetSize(ImVec2(0.f, 350.f));
    SetComopnentTitle("Camera");
}

CameraUI::~CameraUI()
{
    
}

void CameraUI::render_update()
{
    ComponentUI::render_update();

    PROJ_TYPE ProjType = GetTargetObject()->Camera()->GetProjType();
    float fFov = GetTargetObject()->Camera()->GetFOV();
    float fFar = GetTargetObject()->Camera()->GetFar();
    float fScale = GetTargetObject()->Camera()->GetScale();


    const char* ProjType_Conta[] = { "ORTHOGRAPHIC", "PERSPECTIVE" };

    const char* combo_preview_value = ProjType_Conta[(int)ProjType];
    ImGui::Text("Projection Type"); ImGui::SameLine();
    if (ImGui::BeginCombo("##Projection Type", combo_preview_value, 0))
    {
        for (int i = 0; i < IM_ARRAYSIZE(ProjType_Conta); i++)
        {
            const bool is_selected = ((int)ProjType == i);
            if (ImGui::Selectable(ProjType_Conta[i], is_selected))
                ProjType = (PROJ_TYPE)i;


            if (is_selected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }


    ImGui::Text("FOV            "); ImGui::SameLine();	ImGui::DragFloat("##FOV", &fFov);
    ImGui::Text("FAR            "); ImGui::SameLine();	ImGui::DragFloat("##FAR", &fFar);
    ImGui::Text("Scale          "); ImGui::SameLine();	ImGui::DragFloat("##Scale", &fScale);



    for (int i = 0; i < LAYER_MAX; ++i)
        m_bLayerCheck[i] = GetTargetObject()->Camera()->GetLayerCheck(i);

    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
    
    ImGui::Text("Layer Check    "); 

   /* static char* cont;
    for (int i = 0; i < LAYER_MAX; ++i)
    {
        if (i < 10)
            ImGui::Text("(%d) ", i);
        else
            ImGui::Text("(%d)", i);

        ImGui::SameLine();
        if ((pCurLevel->GetLayer(i)->GetName().size() <= 0))
            ImGui::Checkbox("NONE", &m_bLayerCheck[i]);
        else
            ImGui::Checkbox(ToCChar(pCurLevel->GetLayer(i)->GetName()), &m_bLayerCheck[i]);
    }
    for (int i = 0; i < LAYER_MAX; ++i)
        GetTargetObject()->Camera()->LayerCheck(i, m_bLayerCheck[i]);*/


    if (ImGui::Button("ALL##ALL Btn", ImVec2(100.f, 20.f)))
    {
        GetTargetObject()->Camera()->LayerCheckAll();
    }
    ImGui::SameLine();
    if (ImGui::Button("NOTHING##NOTHING Btn", ImVec2(100.f, 20.f)))
    {
        GetTargetObject()->Camera()->LayerCheckNothing();
    }



    GetTargetObject()->Camera()->SetProjType(ProjType);
    GetTargetObject()->Camera()->SetFOV(fFov);
    GetTargetObject()->Camera()->SetFar(fFar);
    GetTargetObject()->Camera()->SetScale(fScale);

    
}

