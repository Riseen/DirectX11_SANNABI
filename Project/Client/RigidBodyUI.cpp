#include "pch.h"
#include "RigidBodyUI.h"

#include <Engine/CRigidBody.h>

RigidBodyUI::RigidBodyUI()
	: ComponentUI("RigidBody", "##RigidBody", COMPONENT_TYPE::RIGIDBODY)
{
	SetSize(ImVec2(0.f, 220.f));
	SetComopnentTitle("RigidBody");
}

RigidBodyUI::~RigidBodyUI()
{
}

void RigidBodyUI::render_update()
{
	ComponentUI::render_update();


	
	ImVec2 vForce(GetTargetObject()->RigidBody()->GetForce().x, GetTargetObject()->RigidBody()->GetForce().y);
	ImVec2 vAccel(GetTargetObject()->RigidBody()->GetAccel().x, GetTargetObject()->RigidBody()->GetAccel().y);
	ImVec2 vAccelAlpha(GetTargetObject()->RigidBody()->GetAccelAlpha().x, GetTargetObject()->RigidBody()->GetAccelAlpha().y);
	ImVec2 vVelocity(GetTargetObject()->RigidBody()->GetVelocity().x, GetTargetObject()->RigidBody()->GetVelocity().y);
	ImVec2 vMaxVelocity(GetTargetObject()->RigidBody()->GetMaxVelocity().x, GetTargetObject()->RigidBody()->GetMaxVelocity().y);
	Vec3 vStartPos(GetTargetObject()->RigidBody()->GetStartPos().x, GetTargetObject()->RigidBody()->GetStartPos().y, GetTargetObject()->RigidBody()->GetStartPos().z);
	Vec3 vEndPos(GetTargetObject()->RigidBody()->GetEndPos().x, GetTargetObject()->RigidBody()->GetEndPos().y, GetTargetObject()->RigidBody()->GetEndPos().z);
	float fMass = GetTargetObject()->RigidBody()->GetMass();
	float fSpeed = GetTargetObject()->RigidBody()->GetSpeed();
	float fFricCoeff = GetTargetObject()->RigidBody()->GetFricCoeff();
	float fAngle = GetTargetObject()->RigidBody()->GetCurAngle();


	ImGui::Text("Force      ");
	ImGui::SameLine();
	ImGui::DragFloat2("##Force", &vForce.x);

	ImGui::Text("Accel      ");
	ImGui::SameLine();
	ImGui::DragFloat2("##Accel", &vAccel.x);

	ImGui::Text("AccelAlpha ");
	ImGui::SameLine();
	ImGui::DragFloat2("##AccelAlpha", &vAccelAlpha.x);

	ImGui::Text("Velocity   ");
	ImGui::SameLine();
	ImGui::DragFloat2("##Velocity  ", &vVelocity.x);

	ImGui::Text("MaxVelocity");
	ImGui::SameLine();
	ImGui::DragFloat2("##MaxVelocity", &vMaxVelocity.x);

	ImGui::Text("StartPos");
	ImGui::SameLine();
	ImGui::DragFloat3("##StartPos", &vStartPos.x);

	ImGui::Text("EndPos");
	ImGui::SameLine();
	ImGui::DragFloat3("##EndPos", &vEndPos.x);

	ImGui::Text("Mass       ");
	ImGui::SameLine();
	ImGui::DragFloat("##Mass", &fMass);

	ImGui::Text("FricCoeff  ");
	ImGui::SameLine();
	ImGui::DragFloat("##FricCoeff", &fFricCoeff);

	ImGui::Text("Speed : %f ", fSpeed);
	ImGui::Text("Angle : %f ", fAngle);


	GetTargetObject()->RigidBody()->SetForce(Vec2(vForce.x, vForce.y));
	GetTargetObject()->RigidBody()->SetAccel(Vec2(vAccel.x, vAccel.y));
	GetTargetObject()->RigidBody()->SetAccelAlpha(Vec2(vAccelAlpha.x, vAccelAlpha.y));
	GetTargetObject()->RigidBody()->SetVelocity(Vec2(vVelocity.x, vVelocity.y));
	GetTargetObject()->RigidBody()->SetMaxVelocity(Vec2(vMaxVelocity.x, vMaxVelocity.y));
	GetTargetObject()->RigidBody()->SetMass(fMass);
	GetTargetObject()->RigidBody()->SetFricCoeff(fFricCoeff);

}


