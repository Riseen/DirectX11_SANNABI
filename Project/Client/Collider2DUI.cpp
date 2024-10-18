#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComopnentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::render_update()
{
	ComponentUI::render_update();

	ImVec2 vOffsetPos(GetTargetObject()->Collider2D()->GetOffsetPos().x, GetTargetObject()->Collider2D()->GetOffsetPos().y);
	ImVec2 vOffsetScale(GetTargetObject()->Collider2D()->GetOffsetScale().x, GetTargetObject()->Collider2D()->GetOffsetScale().y);

	bool bDebugShader_Enable = GetTargetObject()->Collider2D()->IsDrawDebugShader();
	ImGui::Text("Rect DebugShader Enable"); ImGui::SameLine();  ImGui::Checkbox("##DebugEnable", &bDebugShader_Enable);
	GetTargetObject()->Collider2D()->SetDrawDebugShader(bDebugShader_Enable);

	ImGui::Text("Offset Position"); ImGui::SameLine();  ImGui::DragFloat2("##Offset Postion", &vOffsetPos.x);
	ImGui::Text("Offset Scale   "); ImGui::SameLine();	ImGui::DragFloat2("##Offset Scale", &vOffsetScale.x);


	GetTargetObject()->Collider2D()->SetOffsetPos(Vec2(vOffsetPos.x, vOffsetPos.y));
	GetTargetObject()->Collider2D()->SetOffsetScale(Vec2(vOffsetScale.x, vOffsetScale.y));
}