#include "pch.h"
#include "Light2DUI.h"

#include <Engine/CLight2D.h>

Light2DUI::Light2DUI()
	: ComponentUI("Light2D", "##Light2D", COMPONENT_TYPE::LIGHT2D)
{
	SetSize(ImVec2(0.f, 180.f));
	SetComopnentTitle("Light2D");
}

Light2DUI::~Light2DUI()
{
}


void Light2DUI::render_update()
{
	ComponentUI::render_update();

	Vec4 vColor = GetTargetObject()->Light2D()->GetLightInfo().vColor;
	Vec4 vSpecular = GetTargetObject()->Light2D()->GetLightInfo().vSpecular;
	Vec4 vAmbient = GetTargetObject()->Light2D()->GetLightInfo().vAmbient;
	float fRadius = GetTargetObject()->Light2D()->GetLightInfo().fRadius;
	float fAngle = GetTargetObject()->Light2D()->GetLightInfo().fAngle;
	LIGHT_TYPE LightType = GetTargetObject()->Light2D()->GetLightType();



	ImGui::Text("Color    "); ImGui::SameLine(); ImGui::DragFloat4("##Color", vColor);
	ImGui::Text("Specular "); ImGui::SameLine(); ImGui::DragFloat4("##Specular", vSpecular);
	ImGui::Text("Ambient  "); ImGui::SameLine(); ImGui::DragFloat4("##Ambient", vAmbient);
	ImGui::Text("Radius   "); ImGui::SameLine(); ImGui::DragFloat("##Radius", &fRadius);
	ImGui::Text("Angle    "); ImGui::SameLine(); ImGui::DragFloat("##fAngle", &fAngle);


	const char* LightType_Conta[] = { "DIRECTIONAL", "POINT", "SPOT" };


	const char* combo_preview_value = LightType_Conta[(int)LightType];
	ImGui::Text("LightType"); ImGui::SameLine();
	//ImGuiComboFlags_::
	if (ImGui::BeginCombo("##LightType", combo_preview_value, 0))
	{
		for (int i = 0; i < IM_ARRAYSIZE(LightType_Conta); i++)
		{
			const bool is_selected = ((int)LightType == i);
			if (ImGui::Selectable(LightType_Conta[i], is_selected))
				LightType = (LIGHT_TYPE)i;


			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}

	GetTargetObject()->Light2D()->SetLightColor(vColor);
	GetTargetObject()->Light2D()->SetSpecular(vSpecular);
	GetTargetObject()->Light2D()->SetAmbient(vAmbient);
	GetTargetObject()->Light2D()->SetRadius(fRadius);
	GetTargetObject()->Light2D()->SetAngle(fAngle);
	GetTargetObject()->Light2D()->SetLightType(LightType);

}
