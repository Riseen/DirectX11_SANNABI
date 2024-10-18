#include "pch.h"
#include "GravityUI.h"

#include <Engine/CGravity.h>

GravityUI::GravityUI()
	: ComponentUI("Gravity", "##Gravity", COMPONENT_TYPE::GRAVITY)
{
	SetSize(ImVec2(0.f, 120.f));
	SetComopnentTitle("Gravity");
}

GravityUI::~GravityUI()
{
}

void GravityUI::render_update()
{
	ComponentUI::render_update();
}


