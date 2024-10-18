#include "pch.h"
#include "ParticleSystemUI.h"

#include <Engine/CParticleSystem.h>

ParticleSystemUI::ParticleSystemUI()
	: ComponentUI("ParticleSystem", "##ParticleSystem", COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetSize(ImVec2(0.f, 0.f));
	SetComopnentTitle("ParticleSystem");
}

ParticleSystemUI::~ParticleSystemUI()
{
}

void ParticleSystemUI::render_update()
{
	ComponentUI::render_update();

	tParticleModule tModule = GetTargetObject()->ParticleSystem()->GetParticleModule();
	int ParticleMaxCount = GetTargetObject()->ParticleSystem()->GetMaxParticleCount();


	Ptr<CTexture> pT =	GetTargetObject()->ParticleSystem()->GetParticleTexture();

	bool SpawnModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN];
	bool AddVelocityModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY];
	bool ScaleModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SCALE];
	bool NoiseForceModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE];
	bool DragModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::DRAG];
	bool CALCULATEFORCEModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::CALCULATE_FORCE];
	bool RENDERModuleCheck = tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::RENDER];

	

	ImGui::Text("ParticleMaxCount");
	ImGui::SameLine();
	ImGui::DragInt("##ParticleMaxCount", &ParticleMaxCount);
	if (ParticleMaxCount <= 0) ParticleMaxCount = 1;
	{
		ImGui::SeparatorText("SPAWN Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check", &SpawnModuleCheck);

		ImGui::Text("SpaceType (0: Local, 1: World)");
		ImGui::SameLine();
		ImGui::InputInt("##SpaceType", &tModule.SpaceType);

		ImGui::Text("SpawnColor    ");
		ImGui::SameLine();
		ImGui::DragFloat4("##SpawnColor", tModule.vSpawnColor);

		ImGui::Text("vSpawnMinScale");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnMinScale", tModule.vSpawnMinScale);

		ImGui::Text("vSpawnMaxScale");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnMaxScale", tModule.vSpawnMaxScale);

		ImGui::Text("MinLife       ");
		ImGui::SameLine();
		ImGui::InputFloat("##MinLife", &tModule.MinLife);

		ImGui::Text("MaxLife       ");
		ImGui::SameLine();
		ImGui::InputFloat("##MaxLife", &tModule.MaxLife);

		ImGui::Text("MinMass       ");
		ImGui::SameLine();
		ImGui::DragFloat("##MinMass", &tModule.MinMass);

		ImGui::Text("MaxMass       ");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxMass", &tModule.MaxMass);

		ImGui::Text("SpawnShape    ");
		ImGui::SameLine();
		ImGui::InputInt("##SpawnShape", &tModule.SpawnShape);

		ImGui::Text("Radius        ");
		ImGui::SameLine();
		ImGui::DragFloat("##Radius", &tModule.Radius);

		ImGui::Text("vSpawnBoxScale");
		ImGui::SameLine();
		ImGui::DragFloat4("##vSpawnBoxScale", tModule.vSpawnBoxScale);

		ImGui::Text("SpawnRate     ");
		ImGui::SameLine();
		ImGui::InputInt("##SpawnRate", &tModule.SpawnRate);
	}

	{
		ImGui::SeparatorText("ADD_VELOCITY Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check1", &AddVelocityModuleCheck);

		ImGui::Text("AddVelocityType");
		ImGui::SameLine();
		ImGui::InputInt("##AddVelocityType", &tModule.AddVelocityType);

		ImGui::Text("MinSpeed       ");
		ImGui::SameLine();
		ImGui::DragFloat("##MinSpeed", &tModule.MinSpeed);

		ImGui::Text("MaxSpeed       ");
		ImGui::SameLine();
		ImGui::DragFloat("##MaxSpeed", &tModule.MaxSpeed);

		ImGui::Text("FixedDirection ");
		ImGui::SameLine();
		ImGui::DragFloat4("##FixedDirection", tModule.FixedDirection);

		ImGui::Text("FixedAngle     ");
		ImGui::SameLine();
		ImGui::DragFloat("##FixedAngle", &tModule.FixedAngle);

		ImGui::Text("Dist           ");
		ImGui::SameLine();
		ImGui::DragFloat("##Dist", &tModule.Dist);
	}

	{
		ImGui::SeparatorText("SCALE Module");

		ImGui::Text("Module Check   ");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check2", &ScaleModuleCheck);

		ImGui::Text("vScaleRatio    ");
		ImGui::SameLine();
		ImGui::DragFloat4("##vScaleRatio", tModule.vScaleRatio);
	}

	{
		ImGui::SeparatorText("NOISE_FORCE Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check3", &NoiseForceModuleCheck);

		ImGui::Text("NoiseForceScale");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseForceScale", &tModule.NoiseForceScale);

		ImGui::Text("NoiseForceTerm ");
		ImGui::SameLine();
		ImGui::DragFloat("##NoiseForceTerm", &tModule.NoiseForceTerm);
	}

	{
		ImGui::SeparatorText("DRAG Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check4", &DragModuleCheck);

		ImGui::Text("DragTime      ");
		ImGui::SameLine();
		ImGui::DragFloat("##DragTime", &tModule.DragTime);
	}

	{
		ImGui::SeparatorText("CALCULATE_FORCE Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check5", &CALCULATEFORCEModuleCheck);
	}

	{
		ImGui::SeparatorText("RENDER Module");

		ImGui::Text("Module Check");
		ImGui::SameLine();
		ImGui::Checkbox("##Module Check6", &RENDERModuleCheck);

		ImGui::Text("VelocityAlignment");
		ImGui::SameLine();
		ImGui::InputInt("##VelocityAlignment", &tModule.VelocityAlignment);

		ImGui::Text("AlphaBasedLife   ");
		ImGui::SameLine();
		ImGui::InputInt("##AlphaBasedLife", &tModule.AlphaBasedLife);

		ImGui::Text("AlphaMaxAge      ");
		ImGui::SameLine();
		ImGui::DragFloat("##AlphaMaxAge", &tModule.AlphaMaxAge);
	}


	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = SpawnModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::ADD_VELOCITY] = AddVelocityModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SCALE] = ScaleModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::NOISE_FORCE] = NoiseForceModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::DRAG] = DragModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::CALCULATE_FORCE] = CALCULATEFORCEModuleCheck;
	tModule.arrModuleCheck[(UINT)PARTICLE_MODULE::RENDER] = RENDERModuleCheck;

	GetTargetObject()->ParticleSystem()->SetMaxParticleCount((UINT)ParticleMaxCount);
	GetTargetObject()->ParticleSystem()->SetParticleModule(tModule);
}
