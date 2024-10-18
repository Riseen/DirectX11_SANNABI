#include "pch.h"
#include "CBossATScript.h"

#include "CBossScript.h"

CBossATScript::CBossATScript()
	: CScript(BOSSATSCRIPT)
{
}

CBossATScript::~CBossATScript()
{
}


void CBossATScript::begin()
{
}

void CBossATScript::tick()
{
}

void CBossATScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (GetOwner()->GetParent()->GetScript<CBossScript>()->GetCurBossState() == BOSS_STATE::Phase1_PatternLast_IDLE)
	{
		if (_OtherObj->GetName() == L"BombCargoCol")
		{
			GetOwner()->GetParent()->GetScript<CBossScript>()->SetBossState(BOSS_STATE::Phase1_PatternLast_END);
			GetOwner()->GetParent()->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::Phase1_PatternLast_END);
			GetOwner()->GetParent()->StateMachine()->GetFSM()->SetState(L"BossPhase1PLEndState");

			GamePlayStatic::DestroyGameObject(_OtherObj->GetParent());
		}
	}
	else if (GetOwner()->GetParent()->GetScript<CBossScript>()->GetCurBossState() == BOSS_STATE::Phase2_PatternLast_IDLE)
	{
		if (_OtherObj->GetName() == L"FNCRANE")
		{
			GetOwner()->GetParent()->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_1stHooked);
			GetOwner()->GetParent()->GetScript<CBossScript>()->SetScaleForState(BOSS_STATE::PhaseFinal_1stHooked);
			GetOwner()->GetParent()->StateMachine()->GetFSM()->SetState(L"1stHookedState");


			GamePlayStatic::Play2DSound(L"sound\\Boss\\SFX_CHAP1_BossCrash2.wav", 1, 0.1f);
			GamePlayStatic::DestroyGameObject(_OtherObj);
		}
	}
}

void CBossATScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBossATScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBossATScript::SaveToFile(FILE* _File)
{
}

void CBossATScript::LoadFromFile(FILE* _File)
{
}


