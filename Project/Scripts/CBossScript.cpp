#include "pch.h"
#include "CBossScript.h"
#include "CBossATScript.h"

#include "CCameraScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CBossScript::CBossScript()
	: CEnemyScript(BOSSSCRIPT)
	, m_CurState(BOSS_STATE::APPEAR_FIRST)
	, m_PrevState(BOSS_STATE::APPEAR_FIRST)
	, m_iBossHP(7)
	, m_iPatternCount(2)
	, m_fAccTime(0.f)
	, m_fChangeTime(0.9f)
{
	AddScriptParam(SCRIPT_PARAM::INT, "Boss HP", &m_iBossHP);
	AddScriptParam(SCRIPT_PARAM::INT, "Boss STATE", &m_CurState);
}

CBossScript::~CBossScript()
{
}



void CBossScript::begin()
{
	Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Appear1st_1.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Appear1st_2.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Appear2nd.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Appear3rd.anim");

	

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BossBattleInit_Down.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BossBattleInit_Loop.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BossBattleInit_Start.anim");

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Destroy.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Idle.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Respawn.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_BrokenCargoDroneBlue_A_Stepped.anim");

	

	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_NextPhase_Down.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_NextPhase_Loop.anim");
	Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_NextPhase_Start.anim");

	// Phase 1
	{
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_Alert.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_Damaged.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_ExcHolded.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_Idle.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern1_PopUp.anim");

		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern2_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern2_Moving.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern2_PopUp.anim");


		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_Alert.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_Damaged.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_ExcHolded.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_Groggy.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_GroggyStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_Moving.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_Pattern6_PopUp.anim");

		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_PatternLast_Alert.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_PatternLast_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_PatternLast_End.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_PatternLast_Idle.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase1\\Spr_WOE_Phase1_PatternLast_PopUp.anim");
	}

	// Phase 2
	{
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern1_Damaged.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern1_ExcHolded.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern1_Idle.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern1_PopUp.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern1_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern2_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern2_Moving.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern2_PopUp.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_Alert.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_Damaged.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_ExcHolded.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_Groggy.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_GroggyStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_Moving.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_Pattern6_PopUp.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_PatternLast_Alert.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_PatternLast_Down.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_PatternLast_Idle.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\Phase2\\Spr_WOE_Phase2_PatternLast_PopUp.anim");
	}

	// Final 
	{
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_1stPounding.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_1stPoundingReadyLoop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_2ndPounding.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_2ndPoundingReady1Loop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_2ndPoundingReady1to2.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_2ndPoundingReady2Loop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPounding.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPoundingReady1Loop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPoundingReady1to2.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPoundingReady2Loop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPoundingReady2to3.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_3rdPoundingReady3Loop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_BeforePoundingLoop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_BeforePoundingStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_BeforePoundingTo1stPounding.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_Execution.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_ExecutionEndLoop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_ExecutionReadyLoop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_ExecutionStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE&SNB_AfterExecutionLoop.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_1stHooked.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_1stHookedStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_2ndHooked.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_2ndHookedStart.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_3rdHooked.anim");
		Animator2D()->CreateFromFile(L"animation\\Enemy\\Boss\\final\\Spr_WOE_3rdHookedStart.anim");
	}

	CGameObject* pPlayer = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Player");
	if (pPlayer)
	{
		StateMachine()->AddBlackboardData(L"TargetObject", BB_DATA::OBJECT, pPlayer);
	}
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	if (pMainCamera)
	{
		StateMachine()->AddBlackboardData(L"Camera", BB_DATA::OBJECT, pMainCamera);
	}

	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->Play(L"Spr_WOE_Appear1st_1");

	GamePlayStatic::Play2DSound(L"sound\\Boss\\SFX_Chap1_Boss_Event.wav", 1, 0.1f);
}

void CBossScript::tick()
{
	/*SetScaleForState(m_CurState);

	ChangeState();

	m_PrevState = m_CurState;
	return;*/

	if (m_fAccTime > m_fChangeTime && m_CurState == BOSS_STATE::APPEAR_FIRST)
	{
		m_CurState = BOSS_STATE::APPEAR_SECOND;
		StateMachine()->GetFSM()->SetState(L"BossAppearState");
	}
	else
	{
		m_fAccTime += DT;
	}
	CGameObject* pCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");


	if (KEY_TAP(KEY::NUM4))
	{
		StateMachine()->GetFSM()->SetState(L"BossPhase1P1AlertState");
		SetBossState(BOSS_STATE::Phase1_Pattern1_ALERT);
		SetScaleForState(BOSS_STATE::Phase1_Pattern1_ALERT);
		pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
	}
	if (KEY_TAP(KEY::NUM5))
	{
		StateMachine()->GetFSM()->SetState(L"BossPhase2P1AlertState");
		SetBossState(BOSS_STATE::Phase2_Pattern1_ALERT);
		SetScaleForState(BOSS_STATE::Phase2_Pattern1_ALERT);
		pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
	}
	if (KEY_TAP(KEY::NUM6))
	{
		StateMachine()->GetFSM()->SetState(L"BossPhase2P1AlertState");
		SetBossState(BOSS_STATE::Phase2_PatternLast_ALERT);
		SetScaleForState(BOSS_STATE::Phase2_PatternLast_ALERT);
		pCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 5.f, 2.f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);
		m_iBossHP = 0;
	}


	Detected();

	ChangeState();

	m_PrevState = m_CurState;
}

void CBossScript::Detected()
{
	/*Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();

	CGameObject* pSearch = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SearchBar");
	if (pSearch->GetScript<CSearchBarScript>()->GetCurPriority() == SEARCH_PRIORITY::ENEMY && m_BossAttackPoint != nullptr &&
		pSearch->GetScript<CSearchBarScript>()->GetSearchObj() == m_BossAttackPoint)
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 1);
		}
	}
	else
	{
		if (nullptr != pMtrl)
		{
			pMtrl->SetScalarParam<int>(SCALAR_PARAM::INT_0, 0);
		}
	}*/
}

void CBossScript::SaveToFile(FILE* _File)
{
	fwrite(&m_iBossHP, sizeof(int), 1, _File);
	fwrite(&m_iPatternCount, sizeof(int), 1, _File);
}

void CBossScript::LoadFromFile(FILE* _File)
{
	fread(&m_iBossHP, sizeof(int), 1, _File);
	fread(&m_iPatternCount, sizeof(int), 1, _File);
}

void CBossScript::ChangeState()
{
	if (m_PrevState == m_CurState)
		return;
	else
	{
		DeleteAttackCollsion();
		DeleteBossCollsion();
	}

	

	switch (m_CurState)
	{
	case BOSS_STATE::INVISIBLE:
		Animator2D()->Play(L"NONE");
		break;
	case BOSS_STATE::SEARCH:
		Animator2D()->Play(L"NONE");
		break;
	case BOSS_STATE::APPEAR_FIRST:
		Animator2D()->Play(L"Spr_WOE_Appear1st_1");
		break;
	case BOSS_STATE::APPEAR_SECOND:
		Animator2D()->PlayToPlay(L"Spr_WOE_Appear1st_2", L"Spr_WOE_Appear2nd", false);
		break;
	case BOSS_STATE::APPEAR_THIRD:
		Animator2D()->PlayToPlay(L"Spr_WOE_Appear3rd", L"NONE");
		break;
	case BOSS_STATE::BATTLEINIT:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_BossBattleInit_Start", L"Spr_WOE_BossBattleInit_Loop");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\SFX_CHAP1_BossCrash1.wav", 1, 0.1f);
	}
		break;
	case BOSS_STATE::BATTLEINIT_END:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_BossBattleInit_Down", L"NONE");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDown.wav", 1, 0.1f);
	}
		break;
	case BOSS_STATE::Phase1_Pattern1_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase1_Pattern1_Alert");
		break;
	case BOSS_STATE::Phase1_Pattern1_IDLE:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern1_PopUp", L"Spr_WOE_Phase1_Pattern1_Idle");
		CreateAttackCollsion();
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase1_Pattern1_EXCHOLDED:
		Animator2D()->Play(L"Spr_WOE_Phase1_Pattern1_ExcHolded");
		break;
	case BOSS_STATE::Phase1_Pattern1_DAMAGE:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern1_Damaged", L"NONE");
		break;
	case BOSS_STATE::Phase1_Pattern1_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern1_Down", L"NONE");
		break;
	case BOSS_STATE::Phase1_Pattern2_ALERT:
		// State에서 처리
		break;
	case BOSS_STATE::Phase1_Pattern2_MOVING:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern2_PopUp", L"Spr_WOE_Phase1_Pattern2_Moving");
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase1_Pattern2_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern2_Down", L"NONE");
		break;
	case BOSS_STATE::Phase1_Pattern6_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase1_Pattern6_Alert");
		break;
	case BOSS_STATE::Phase1_Pattern6_MOVING:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern6_PopUp", L"Spr_WOE_Phase1_Pattern6_Moving");
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase1_Pattern6_GROGGY:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern6_GroggyStart", L"Spr_WOE_Phase1_Pattern6_Groggy");
		CreateAttackCollsion();
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase1_Pattern6_EXCHOLDED:
		Animator2D()->Play(L"Spr_WOE_Phase1_Pattern6_ExcHolded");
		break;
	case BOSS_STATE::Phase1_Pattern6_DAMAGE:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern6_Damaged", L"NONE");
		break;
	case BOSS_STATE::Phase1_Pattern6_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_Pattern6_Down", L"NONE");
		break;
	case BOSS_STATE::Phase1_PatternLast_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase1_PatternLast_Alert");
		break;
	case BOSS_STATE::Phase1_PatternLast_IDLE:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_PatternLast_PopUp", L"Spr_WOE_Phase1_PatternLast_Idle");
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase1_PatternLast_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_PatternLast_Down", L"NONE");
		break;
	case BOSS_STATE::Phase1_PatternLast_END:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase1_PatternLast_End", L"NONE");
		break;
	case BOSS_STATE::Phase1_NextPhase:
		Animator2D()->PlayToPlay(L"Spr_WOE_NextPhase_Start", L"Spr_WOE_NextPhase_Loop");
		break;
	case BOSS_STATE::Phase1_NextPhase_END:
		Animator2D()->PlayToPlay(L"Spr_WOE_NextPhase_Down", L"NONE");
		break;
	case BOSS_STATE::Phase2_Pattern1_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase1_Pattern1_Alert");
		break;
	case BOSS_STATE::Phase2_Pattern1_IDLE:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern1_PopUp", L"Spr_WOE_Phase2_Pattern1_Idle");
		CreateAttackCollsion();
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase2_Pattern1_EXCHOLDED:
		Animator2D()->Play(L"Spr_WOE_Phase2_Pattern1_ExcHolded");
		break;
	case BOSS_STATE::Phase2_Pattern1_DAMAGE:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern1_Damaged", L"NONE");
		break;
	case BOSS_STATE::Phase2_Pattern1_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern1_Down", L"NONE");
		break;
	case BOSS_STATE::Phase2_Pattern2_ALERT:
		// State에서 처리
		break;
	case BOSS_STATE::Phase2_Pattern2_MOVING:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern2_PopUp", L"Spr_WOE_Phase2_Pattern2_Moving");
		CreateBossCollsion();
	}
	break;
	case BOSS_STATE::Phase2_Pattern2_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern2_Down", L"NONE");
		break;
	case BOSS_STATE::Phase2_Pattern6_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase2_Pattern6_Alert");
		break;
	case BOSS_STATE::Phase2_Pattern6_MOVING:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern6_PopUp", L"Spr_WOE_Phase2_Pattern6_Moving");
		CreateBossCollsion();
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_GROGGY:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern6_GroggyStart", L"Spr_WOE_Phase2_Pattern6_Groggy");
		CreateAttackCollsion();
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_EXCHOLDED:
		Animator2D()->Play(L"Spr_WOE_Phase2_Pattern6_ExcHolded");
		break;
	case BOSS_STATE::Phase2_Pattern6_DAMAGE:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern6_Damaged", L"NONE");
		break;
	case BOSS_STATE::Phase2_Pattern6_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_Pattern6_Down", L"NONE");
		break;
	case BOSS_STATE::Phase2_PatternLast_ALERT:
		Animator2D()->Play(L"Spr_WOE_Phase2_PatternLast_Alert");
		break;
	case BOSS_STATE::Phase2_PatternLast_IDLE:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_PatternLast_PopUp", L"Spr_WOE_Phase2_PatternLast_Idle");
		CreateBossCollsion();
	}
		break;
	case BOSS_STATE::Phase2_PatternLast_DOWN:
		Animator2D()->PlayToPlay(L"Spr_WOE_Phase2_PatternLast_Down", L"NONE");
		break;
	case BOSS_STATE::PhaseFinal_1stHooked:
		Animator2D()->PlayToPlay(L"Spr_WOE_1stHookedStart", L"Spr_WOE_1stHooked");
		break;
	case BOSS_STATE::PhaseFinal_2ndHooked:
		Animator2D()->PlayToPlay(L"Spr_WOE_2ndHookedStart", L"Spr_WOE_2ndHooked");
		break;
	case BOSS_STATE::PhaseFinal_3rdHooked:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE_3rdHookedStart", L"Spr_WOE_3rdHooked");
		CreateAttackCollsion();
	}
		break;
	case BOSS_STATE::PhaseFinal_BeforePounding:
	{
		Animator2D()->PlayToPlay(L"Spr_WOE&SNB_BeforePoundingStart", L"Spr_WOE&SNB_BeforePoundingLoop");
	}
		break;
	case BOSS_STATE::PhaseFinal_1stPoundingReady:
		Animator2D()->PlayToPlay(L"Spr_WOE&SNB_BeforePoundingTo1stPounding", L"Spr_WOE&SNB_1stPoundingReadyLoop");
		break;
	case BOSS_STATE::PhaseFinal_1stPounding:
		Animator2D()->Play(L"Spr_WOE&SNB_1stPounding", false);
		break;
	case BOSS_STATE::PhaseFinal_2ndPoundingReady:
		Animator2D()->Play(L"Spr_WOE&SNB_2ndPoundingReady1Loop");
		break;
	case BOSS_STATE::PhaseFinal_2ndPoundingReady_Two:
		Animator2D()->PlayToPlay(L"Spr_WOE&SNB_2ndPoundingReady1to2", L"Spr_WOE&SNB_2ndPoundingReady2Loop");
		break;
	case BOSS_STATE::PhaseFinal_2ndPounding:
		Animator2D()->Play(L"Spr_WOE&SNB_2ndPounding",false);
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady:
		Animator2D()->Play(L"Spr_WOE&SNB_3rdPoundingReady1Loop");
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady_Two:
		Animator2D()->PlayToPlay(L"Spr_WOE&SNB_3rdPoundingReady1to2", L"Spr_WOE&SNB_3rdPoundingReady2Loop");
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady_Three:
		Animator2D()->PlayToPlay(L"Spr_WOE&SNB_3rdPoundingReady2to3", L"Spr_WOE&SNB_3rdPoundingReady3Loop");
		break;
	case BOSS_STATE::PhaseFinal_3rdPounding:
		Animator2D()->Play(L"Spr_WOE&SNB_3rdPounding",false);
		break;
	case BOSS_STATE::PhaseFinal_Execution_Start:
		Animator2D()->Play(L"SNB_ExecutionStart", false);
		break;
	case BOSS_STATE::PhaseFinal_Execution:
		Animator2D()->Play(L"Spr_WOE&SNB_Execution", false);
		break;
	case BOSS_STATE::PhaseFinal_Execution_Ready:
		Animator2D()->Play(L"Spr_WOE&SNB_ExecutionReadyLoop");
		break;
	case BOSS_STATE::PhaseFinal_Execution_End:
		Animator2D()->Play(L"Spr_WOE&SNB_ExecutionEndLoop");
		break;
	case BOSS_STATE::PhaseFinal_Execution_After:
		Animator2D()->Play(L"Spr_WOE&SNB_AfterExecutionLoop");
		break;
	default:
		break;
	}

	
}


void CBossScript::CreateAttackCollsion()
{
	m_BossAttackPoint = new CGameObject;
	m_BossAttackPoint->SetName(L"Boss Attack point");

	m_BossAttackPoint->AddComponent(new CTransform);
	m_BossAttackPoint->AddComponent(new CCollider2D);

	
	m_BossAttackPoint->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));

	switch (m_CurState)
	{
	case BOSS_STATE::Phase1_Pattern1_IDLE:
	{
		m_BossAttackPoint->Transform()->SetRelativePos(Vec3(0.f, 530.f, 0.f));
		m_BossAttackPoint->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 0.f));
		
		m_BossAttackPoint->Collider2D()->SetOffsetScale(Vec2(103.f, 163.f));
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_GROGGY:
	{
		m_BossAttackPoint->Transform()->SetRelativePos(Vec3(0.f, 530.f, 0.f));
		m_BossAttackPoint->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 0.f));

		m_BossAttackPoint->Collider2D()->SetOffsetScale(Vec2(103.f, 163.f));
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_IDLE:
	{
		m_BossAttackPoint->Transform()->SetRelativePos(Vec3(0.f, 610.f, 0.f));
		m_BossAttackPoint->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 0.f));

		m_BossAttackPoint->Collider2D()->SetOffsetScale(Vec2(103.f, 163.f));
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_GROGGY:
	{
		m_BossAttackPoint->Transform()->SetRelativePos(Vec3(0.f, 610.f, 0.f));
		m_BossAttackPoint->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 0.f));

		m_BossAttackPoint->Collider2D()->SetOffsetScale(Vec2(103.f, 163.f));
	}
		break;
	case BOSS_STATE::PhaseFinal_3rdHooked:
	{
		m_BossAttackPoint->Transform()->SetRelativePos(Vec3(-22.f, -73.f, 0.f));
		m_BossAttackPoint->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 0.f));

		m_BossAttackPoint->Collider2D()->SetOffsetScale(Vec2(103.f, 163.f));
	}
		break;
	default:
		break;
	}
	
	

	
	

	GetOwner()->AddChild(m_BossAttackPoint);
}

void CBossScript::DeleteAttackCollsion()
{
	if (m_BossAttackPoint != nullptr)
		GamePlayStatic::DestroyGameObject(m_BossAttackPoint);
}

void CBossScript::DeleteBossCollsion()
{
	if (m_BossCollsion != nullptr)
		GamePlayStatic::DestroyGameObject(m_BossCollsion);

	int a = 0;
}


void CBossScript::CreateBossCollsion()
{
	
	m_BossCollsion = new CGameObject;
	m_BossCollsion->SetName(L"Boss AT");

	m_BossCollsion->AddComponent(new CTransform);
	m_BossCollsion->AddComponent(new CCollider2D);
	m_BossCollsion->AddComponent(new CBossATScript);

	m_BossCollsion->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	m_BossCollsion->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));

	switch (m_CurState)
	{
	case BOSS_STATE::Phase1_Pattern1_IDLE:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(290.f, 1181.f));
	}
		break;
	case BOSS_STATE::Phase1_Pattern2_MOVING:
	{
		m_BossCollsion->Transform()->SetRelativePos(Vec3(220.f, m_BossCollsion->Transform()->GetRelativePos().y, m_BossCollsion->Transform()->GetRelativePos().z));
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(800.f, 941.f));
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_MOVING:
	case BOSS_STATE::Phase1_Pattern6_GROGGY:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(323.f, 1234.f));
	}
		break;
	case BOSS_STATE::Phase1_PatternLast_IDLE:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(289.f, 1055.f));
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_IDLE:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(323.f, 1327.f));
	}
		break;
	case BOSS_STATE::Phase2_Pattern2_MOVING:
	{
		m_BossCollsion->Transform()->SetRelativePos(Vec3(220.f, m_BossCollsion->Transform()->GetRelativePos().y, m_BossCollsion->Transform()->GetRelativePos().z));
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(800.f, 941.f));
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_MOVING:
	case BOSS_STATE::Phase2_Pattern6_GROGGY:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(340.f, 1222.f));
	}
		break;
	case BOSS_STATE::Phase2_PatternLast_IDLE:
	{
		m_BossCollsion->Collider2D()->SetOffsetPos(Vec2(0.f, 0.f));
		m_BossCollsion->Collider2D()->SetOffsetScale(Vec2(345.f, 1314.f));
	}
		break;
	default:
		break;
	}

	GetOwner()->AddChild(m_BossCollsion);

	// boss 공격은 Layer 다르게
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(m_BossCollsion, 12);
}

void CBossScript::Holding()
{


	switch (m_CurState)
	{
	case BOSS_STATE::Phase1_Pattern1_IDLE:
	{
		m_CurState = BOSS_STATE::Phase1_Pattern1_EXCHOLDED;
		StateMachine()->GetFSM()->SetState(L"BossPhase1P1ExcHoldedState");
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_GROGGY:
	{
		m_CurState = BOSS_STATE::Phase1_Pattern6_EXCHOLDED;
		StateMachine()->GetFSM()->SetState(L"BossPhase1P6ExcHoldedState");
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_IDLE:
	{
		m_CurState = BOSS_STATE::Phase2_Pattern1_EXCHOLDED;
		StateMachine()->GetFSM()->SetState(L"BossPhase2P1ExcHoldedState");
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_GROGGY:
	{
		m_CurState = BOSS_STATE::Phase2_Pattern6_EXCHOLDED;
		StateMachine()->GetFSM()->SetState(L"BossPhase2P6ExcHoldedState");
	}
		break;
	default:
		break;
	}



}

void CBossScript::Damage()
{
	m_iBossHP--;

	switch (m_CurState)
	{
	case BOSS_STATE::Phase1_Pattern1_EXCHOLDED:
	{
		m_CurState = BOSS_STATE::Phase1_Pattern1_DAMAGE;
		SetScaleForState(BOSS_STATE::Phase1_Pattern1_DAMAGE);
		StateMachine()->GetFSM()->SetState(L"BossPhase1P1DamageState");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_EXCHOLDED:
	{
		m_CurState = BOSS_STATE::Phase1_Pattern6_DAMAGE;
		SetScaleForState(BOSS_STATE::Phase1_Pattern6_DAMAGE);
		StateMachine()->GetFSM()->SetState(L"BossPhase1P6DamageState");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_EXCHOLDED:
	{
		m_CurState = BOSS_STATE::Phase2_Pattern1_DAMAGE;
		SetScaleForState(BOSS_STATE::Phase2_Pattern1_DAMAGE);
		StateMachine()->GetFSM()->SetState(L"BossPhase2P1DamageState");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_EXCHOLDED:
	{
		m_CurState = BOSS_STATE::Phase2_Pattern6_DAMAGE;
		SetScaleForState(BOSS_STATE::Phase2_Pattern6_DAMAGE);
		StateMachine()->GetFSM()->SetState(L"BossPhase2P6DamageState");
		GamePlayStatic::Play2DSound(L"sound\\Boss\\Sfx_BossDamaged.wav", 1, 0.1f);
	}
		break;
	default:
		break;
	}

	
}

void CBossScript::SetScaleForState(BOSS_STATE _State)
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vScale = Transform()->GetRelativeScale();


	switch (_State)
	{
	case BOSS_STATE::IDLE:
		break;
	case BOSS_STATE::INVISIBLE:
		break;
	case BOSS_STATE::SEARCH:
		break;
	case BOSS_STATE::APPEAR_FIRST:
		break;
	case BOSS_STATE::APPEAR_SECOND:
	{
		vPos = Vec3(-796.f, -451.f, 558.f);
		vScale = Vec3(1956.f, 489.f, vScale.z);
	}
		break;
	case BOSS_STATE::APPEAR_THIRD:
	{
		vPos = Vec3(1374.f, -517.f, 515.f);
		vScale = Vec3(2800.f, 700.f, vScale.z);
	}
		break;
	case BOSS_STATE::BATTLEINIT:
	{
		vPos = Vec3(254.f, -466.f, 472.f);
		vScale = Vec3(700.f, 1050.f, vScale.z);
	}
		break;
	case BOSS_STATE::BATTLEINIT_END:
		break;
	case BOSS_STATE::Phase1_Pattern1_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(500.f, 500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern1_IDLE:
	{
		vScale = Vec3(600.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern1_EXCHOLDED:
		break;
	case BOSS_STATE::Phase1_Pattern1_DAMAGE:
	{
		vScale = Vec3(800.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern1_DOWN:
		break;
	case BOSS_STATE::Phase1_Pattern2_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(1300.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern2_MOVING:
		break;
	case BOSS_STATE::Phase1_Pattern2_DOWN:
		break;
	case BOSS_STATE::Phase1_Pattern6_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_MOVING:
		break;
	case BOSS_STATE::Phase1_Pattern6_GROGGY:
		break;
	case BOSS_STATE::Phase1_Pattern6_EXCHOLDED:
		break;
	case BOSS_STATE::Phase1_Pattern6_DAMAGE:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(800.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_Pattern6_DOWN:
		break;
	case BOSS_STATE::Phase1_PatternLast_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(600.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_PatternLast_IDLE:
		break;
	case BOSS_STATE::Phase1_PatternLast_DOWN:
		break;
	case BOSS_STATE::Phase1_PatternLast_END:
		break;
	case BOSS_STATE::Phase1_NextPhase:
	{
		vPos = Vec3(251, -337.f, 522.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase1_NextPhase_END:
		break;
	case BOSS_STATE::Phase2_Pattern1_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(500.f, 500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_IDLE:
	{
		vScale = Vec3(600.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_EXCHOLDED:
		break;
	case BOSS_STATE::Phase2_Pattern1_DAMAGE:
	{
		vScale = Vec3(800.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern1_DOWN:
		break;
	case BOSS_STATE::Phase2_Pattern2_ALERT:
	{
		vScale = Vec3(1300.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern2_MOVING:
		break;
	case BOSS_STATE::Phase2_Pattern2_DOWN:
		break;
	case BOSS_STATE::Phase2_Pattern6_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_MOVING:
	{
		vPos = Vec3(vPos.x, -508.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_GROGGY:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_EXCHOLDED:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_DAMAGE:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_Pattern6_DOWN:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_PatternLast_ALERT:
	{
		vPos = Vec3(vPos.x, -633.f, 500.f);
		vScale = Vec3(700.f, 1500.f, vScale.z);
	}
		break;
	case BOSS_STATE::Phase2_PatternLast_IDLE:
		break;
	case BOSS_STATE::Phase2_PatternLast_DOWN:
		break;
	case BOSS_STATE::Phase2_PatternLast_END:
		break;
	case BOSS_STATE::PhaseFinal_1stHooked:
	{
		vPos = Vec3(vPos.x, 122.f, 500.f);
		vScale = Vec3(750.f, 2300.f, vScale.z);
	}
		break;
	case BOSS_STATE::PhaseFinal_2ndHooked:
		break;
	case BOSS_STATE::PhaseFinal_3rdHooked:
		break;
	case BOSS_STATE::PhaseFinal_1stPoundingReady:
		break;
	case BOSS_STATE::PhaseFinal_1stPounding:
		break;
	case BOSS_STATE::PhaseFinal_2ndPoundingReady:
		break;
	case BOSS_STATE::PhaseFinal_2ndPoundingReady_Two:
		break;
	case BOSS_STATE::PhaseFinal_2ndPounding:
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady:
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady_Two:
		break;
	case BOSS_STATE::PhaseFinal_3rdPoundingReady_Three:
		break;
	case BOSS_STATE::PhaseFinal_3rdPounding:
		break;
	case BOSS_STATE::PhaseFinal_BeforePounding:
		break;
	case BOSS_STATE::PhaseFinal_Execution:
		break;
	case BOSS_STATE::PhaseFinal_Execution_Ready:
		break;
	case BOSS_STATE::PhaseFinal_Execution_End:
		break;
	case BOSS_STATE::PhaseFinal_Execution_After:
	{
		vPos = Vec3(vPos.x, 350.f, 500.f);
	}
		break;
	default:
		break;
	}

	Transform()->SetRelativeScale(vScale);
	Transform()->SetRelativePos(vPos);
}
