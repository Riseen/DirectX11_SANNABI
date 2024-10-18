#include "pch.h"
#include "CPlayerScript.h"


#include <Engine/CAssetMgr.h>
#include <Engine/CGameObject.h>

#include "CSearchBarScript.h"
#include "CMissileScript.h"
#include "CGrabScript.h"
#include "CArmScript.h"
#include "CHoldAimScript.h"
#include "CHPUIScript.h"
#include "CClimbBarScript.h"
#include "CAfterImageManagerScript.h"
#include "CCapeScript.h"
#include "CCameraScript.h"
#include "CGameSystemMgrScript.h"

#include <Engine/CMaterial.h>
#include <Engine/CRenderComponent.h>

#include <Engine/CFontMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CCamera.h>


CPlayerScript::CPlayerScript()
	: CScript(PLAYERSCRIPT)
	, m_CurState(PLAYER_STATE::IDLE)
	, m_PrevState(PLAYER_STATE::IDLE)
	, m_fSpeed(600.f)
	, m_fDashTime(0.5f)
	, m_fGodTime(2.f)
	, m_fAccTime(0.f)
	, m_iHP(4)
	, m_bCurLP(true)
	, m_bPrevLP(true)
	, m_bCanJump(false)
	, m_bCanRopeDash(false)
	, m_bRopeDash(false)
	, m_bGod(false)
	, m_bFade(false)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Player Speed", &m_fSpeed);
	AddScriptParam(SCRIPT_PARAM::INT, "Player STATE", &m_CurState);
	AddScriptParam(SCRIPT_PARAM::INT, "Player HP", &m_iHP);
}

CPlayerScript::~CPlayerScript()
{

}


void CPlayerScript::begin()
{
	
	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Idle.png", L"texture\\Player\\Spr_SNB_Idle.png");
	Animator2D()->Create(L"IDLE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Idle_rp.png", L"texture\\Player\\Spr_SNB_Idle_rp.png");
	Animator2D()->Create(L"IDLE_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_jumping.png", L"texture\\Player\\Spr_SNB_jumping.png");
	Animator2D()->Create(L"JUMPING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_jumping_rp.png", L"texture\\Player\\Spr_SNB_jumping_rp.png");
	Animator2D()->Create(L"JUMPING_RP", pAltasTex, Vec2(480.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Damaged.png", L"texture\\Player\\Spr_SNB_Damaged.png");
	Animator2D()->Create(L"DAMAGED_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Damaged_rp.png", L"texture\\Player\\Spr_SNB_Damaged_rp.png");
	Animator2D()->Create(L"DAMAGED_RP", pAltasTex, Vec2(400.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Dash.png", L"texture\\Player\\Spr_SNB_Dash.png");
	Animator2D()->Create(L"DASH_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 30, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Dash_rp.png", L"texture\\Player\\Spr_SNB_Dash_rp.png");
	Animator2D()->Create(L"DASH_RP", pAltasTex, Vec2(320.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 30, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_DashEndGround.png", L"texture\\Player\\Spr_SNB_DashEndGround.png");
	Animator2D()->Create(L"DASHENDGROUND_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_DashEndGround_rp.png", L"texture\\Player\\Spr_SNB_DashEndGround_rp.png");
	Animator2D()->Create(L"DASHENDGROUND_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Falling.png", L"texture\\Player\\Spr_SNB_Falling.png");
	Animator2D()->Create(L"FALLING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Falling_rp.png", L"texture\\Player\\Spr_SNB_Falling_rp.png");
	Animator2D()->Create(L"FALLING_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_FallStart.png", L"texture\\Player\\Spr_SNB_FallStart.png");
	Animator2D()->Create(L"FALLSTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_FallStart_rp.png", L"texture\\Player\\Spr_SNB_FallStart_rp.png");
	Animator2D()->Create(L"FALLSTART_RP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Land2Run.png", L"texture\\Player\\Spr_SNB_Land2Run.png");
	Animator2D()->Create(L"RAND2RUN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Land2Run_rp.png", L"texture\\Player\\Spr_SNB_Land2Run_rp.png");
	Animator2D()->Create(L"RAND2RUN_RP", pAltasTex, Vec2(960.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Roll2Fall.png", L"texture\\Player\\Spr_SNB_Roll2Fall.png");
	Animator2D()->Create(L"ROLL2FALL_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Roll2Fall_rp.png", L"texture\\Player\\Spr_SNB_Roll2Fall_rp.png");
	Animator2D()->Create(L"ROLL2FALL_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Rolling.png", L"texture\\Player\\Spr_SNB_Rolling.png");
	Animator2D()->Create(L"ROLLING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Rolling_rp.png", L"texture\\Player\\Spr_SNB_Rolling_rp.png");
	Animator2D()->Create(L"ROLLING_RP", pAltasTex, Vec2(960.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_RopeSliding.png", L"texture\\Player\\Spr_SNB_RopeSliding.png");
	Animator2D()->Create(L"ROPESLIDING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_RopeSliding_rp.png", L"texture\\Player\\Spr_SNB_RopeSliding_rp.png");
	Animator2D()->Create(L"ROPESLIDING_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_runstart.png", L"texture\\Player\\Spr_SNB_runstart.png");
	Animator2D()->Create(L"RUNSTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_runstart_rp.png", L"texture\\Player\\Spr_SNB_runstart_rp.png");
	Animator2D()->Create(L"RUNSTART_RP", pAltasTex, Vec2(160.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_runstop.png", L"texture\\Player\\Spr_SNB_runstop.png");
	Animator2D()->Create(L"RUNSTOP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_runstop_rp.png", L"texture\\Player\\Spr_SNB_runstop_rp.png");
	Animator2D()->Create(L"RUNSTOP_RP", pAltasTex, Vec2(480.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_running_lp.png", L"texture\\Player\\Spr_SNB_running_lp.png");
	Animator2D()->Create(L"RUNNING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 20, 20, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_running_rp.png", L"texture\\Player\\Spr_SNB_running_rp.png");
	Animator2D()->Create(L"RUNNING_RP", pAltasTex, Vec2(1600.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 20, 20, true);

	// SHOT AIR DOWN, FRONT, UP
	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRDown.png", L"texture\\Player\\Spr_SNB_ShotAIRDown.png");
		Animator2D()->Create(L"SHOTAIRDOWN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRDown_rp.png", L"texture\\Player\\Spr_SNB_ShotAIRDown_rp.png");
		Animator2D()->Create(L"SHOTAIRDOWN_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRFront.png", L"texture\\Player\\Spr_SNB_ShotAIRFront.png");
		Animator2D()->Create(L"SHOTAIRFRONT_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRFront_rp.png", L"texture\\Player\\Spr_SNB_ShotAIRFront_rp.png");
		Animator2D()->Create(L"SHOTAIRFRONT_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRUp.png", L"texture\\Player\\Spr_SNB_ShotAIRUp.png");
		Animator2D()->Create(L"SHOTAIRUP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotAIRUp_rp.png", L"texture\\Player\\Spr_SNB_ShotAIRUp_rp.png");
		Animator2D()->Create(L"SHOTAIRUP_RP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);
	}

	// SHOTGND DOWN, FRONT, UP
	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDDown.png", L"texture\\Player\\Spr_SNB_ShotGNDDown.png");
		Animator2D()->Create(L"SHOTGNDDOWN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDDown_rp.png", L"texture\\Player\\Spr_SNB_ShotGNDDown_rp.png");
		Animator2D()->Create(L"SHOTGNDDOWN_RP", pAltasTex, Vec2(320.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDFront.png", L"texture\\Player\\Spr_SNB_ShotGNDFront.png");
		Animator2D()->Create(L"SHOTGNDFRONT_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDFront_rp.png", L"texture\\Player\\Spr_SNB_ShotGNDFront_rp.png");
		Animator2D()->Create(L"SHOTGNDFRONT_RP", pAltasTex, Vec2(320.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDUp.png", L"texture\\Player\\Spr_SNB_ShotGNDUp.png");
		Animator2D()->Create(L"SHOTGNDUP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ShotGNDUp_rp.png", L"texture\\Player\\Spr_SNB_ShotGNDUp_rp.png");
		Animator2D()->Create(L"SHOTGNDUP_RP", pAltasTex, Vec2(320.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 4, 10, true);
	}

	// SWING, JUMP, JUMPUP
	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swing.png", L"texture\\Player\\Spr_SNB_swing.png");
		Animator2D()->Create(L"SWING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 15, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swing_rp.png", L"texture\\Player\\Spr_SNB_swing_rp.png");
		Animator2D()->Create(L"SWING_RP", pAltasTex, Vec2(1200.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 15, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swingjump.png", L"texture\\Player\\Spr_SNB_swingjump.png");
		Animator2D()->Create(L"SWINGJUMP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swingjump_rp.png", L"texture\\Player\\Spr_SNB_swingjump_rp.png");
		Animator2D()->Create(L"SWINGJUMP_RP", pAltasTex, Vec2(720.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swingjumpup.png", L"texture\\Player\\Spr_SNB_swingjumpup.png");
		Animator2D()->Create(L"SWINGJUMPUP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_swingjumpup_rp.png", L"texture\\Player\\Spr_SNB_swingjumpup_rp.png");
		Animator2D()->Create(L"SWINGJUMPUP_RP", pAltasTex, Vec2(720.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, true);
	}

	// WALL CLIMB IDLE, DOWN, UP, SLIDE
	{
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbup.png", L"texture\\Player\\Spr_SNB_WallClimbup.png");
		Animator2D()->Create(L"CLIMBUP_IDLE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 1, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbup_rp.png", L"texture\\Player\\Spr_SNB_WallClimbup_rp.png");
		Animator2D()->Create(L"CLIMBUP_IDLE_RP", pAltasTex, Vec2(80.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 1, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbDown.png", L"texture\\Player\\Spr_SNB_WallClimbDown.png");
		Animator2D()->Create(L"CLIMBDOWN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbDown_rp.png", L"texture\\Player\\Spr_SNB_WallClimbDown_rp.png");
		Animator2D()->Create(L"CLIMBDOWN_RP", pAltasTex, Vec2(560.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbup.png", L"texture\\Player\\Spr_SNB_WallClimbup.png");
		Animator2D()->Create(L"CLIMBUP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 10, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallClimbup_rp.png", L"texture\\Player\\Spr_SNB_WallClimbup_rp.png");
		Animator2D()->Create(L"CLIMBUP_RP", pAltasTex, Vec2(800.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 10, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallSlideStart.png", L"texture\\Player\\Spr_SNB_WallSlideStart.png");
		Animator2D()->Create(L"SLIDESTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallSlideStart_rp.png", L"texture\\Player\\Spr_SNB_WallSlideStart_rp.png");
		Animator2D()->Create(L"SLIDESTART_RP", pAltasTex, Vec2(880.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, true);

		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallSliding.png", L"texture\\Player\\Spr_SNB_WallSliding.png");
		Animator2D()->Create(L"SLIDING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);
		pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_WallSliding_rp.png", L"texture\\Player\\Spr_SNB_WallSliding_rp.png");
		Animator2D()->Create(L"SLIDING_RP", pAltasTex, Vec2(880.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, true);


	}

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ExcHolding_Back.png", L"texture\\Player\\Spr_SNB_ExcHolding_Back.png");
	Animator2D()->Create(L"EXCHOLDING_BACK_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_ExcHolding_Back_rp.png", L"texture\\Player\\Spr_SNB_ExcHolding_Back_rp.png");
	Animator2D()->Create(L"EXCHOLDING_BACK_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);


	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Player\\Spr_SNB_Death.png", L"texture\\Player\\Spr_SNB_Death.png");
	Animator2D()->Create(L"DEATH", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 24, 10, false);

	GetRenderComponent()->GetDynamicMaterial();

	CGameObject* pObj = nullptr;

	pObj = new CGameObject;
	pObj->SetName(L"ARM");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CArmScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GetOwner()->AddChild(pObj);

	CLevelMgr::GetInst()->GetCurrentLevel()->AddObject(pObj, 10);

	pObj = new CGameObject;
	pObj->SetName(L"HPUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHPUIScript);

	pObj->Transform()->SetRelativePos(Vec3(-45.f, 20.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GetOwner()->AddChild(pObj);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(pObj, 3);

	pObj = new CGameObject;
	pObj->SetName(L"AimUI");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CHoldAimScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(384.f, 384.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GetOwner()->AddChild(pObj);

	pCurLevel->AddObject(pObj, 3);

	pObj = new CGameObject;
	pObj->SetName(L"ClimbBar");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CCollider2D);
	pObj->AddComponent(new CClimbBarScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(30.f, 20.f, 1.f));

	pObj->Collider2D()->SetDrawDebugShader(false);
	pObj->Collider2D()->SetOffsetPos(Vec2(1.f, 1.f));
	pObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));


	GetOwner()->AddChild(pObj);

	pCurLevel->AddObject(pObj, 15);


	pObj = new CGameObject;
	pObj->SetName(L"AfterImageManager");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CAfterImageManagerScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(1.f, 1.f, 1.f));


	GetOwner()->AddChild(pObj);

	pObj = new CGameObject;
	pObj->SetName(L"Cape");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CCapeScript);

	pObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, -300.f));
	pObj->Transform()->SetRelativeScale(Vec3(160.f, 160.f, 1.f));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GetOwner()->AddChild(pObj);


	Animator2D()->Play(L"IDLE_LP");
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();


	CGameObject* pGrab = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Grab");
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");


	vector<CGameObject*> pChild = GetOwner()->GetChild();
	assert(pChild[0] != nullptr || pChild[0]->GetName() != L"ARM");
	assert(pChild[1] != nullptr || pChild[1]->GetName() != L"HPUI");
	assert(pChild[2] != nullptr || pChild[2]->GetName() != L"AimUI");
	assert(pChild[3] != nullptr || pChild[3]->GetName() != L"ClimbBar");
	assert(pChild[4] != nullptr || pChild[4]->GetName() != L"AfterImageManager");

	static bool binitSpeed = true;
	static float AccTime = 0.f;

	if (KEY_RELEASED(KEY::LBTN))
	{
		pGrab->GetScript<CGrabScript>()->SetGrabState(GRAB_STATE::GRABRETURN);
		Gravity()->SetGrab(false);
		binitSpeed = true;
	}

	if (m_CurState != PLAYER_STATE::DEATH)
	{
		if(KEY_TAP(KEY::LBTN) && pChild[0]->GetScript<CArmScript>()->IsHolding())
			CreateEffect(PlayerEffect_TYPE::ATTACKDONUT);

		if (KEY_PRESSED(KEY::LBTN))
		{
			if (pChild[0]->GetScript<CArmScript>()->IsHolding())
			{
				m_CurState = PLAYER_STATE::HOLDING;
				RigidBody()->SetVelocity(Vec2(0.f, 0.f));
				Gravity()->SetOnGround(true);
				pChild[2]->GetScript<CHoldAimScript>()->SetHolding(true);
				


				pChild[4]->GetScript<CAfterImageManagerScript>()->SetAfterImage(pChild[0]->GetScript<CArmScript>()->GetCurShotState());
			}
			else if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
			{
				if (m_CurState == PLAYER_STATE::DAMAGE)
				{
					pGrab->GetScript<CGrabScript>()->SetGrabState(GRAB_STATE::GRABRETURN);
					RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::DEFAULT);
					Gravity()->SetGrab(false);
					binitSpeed = true;
				}
				else
				{
					Vec3 vPos = pGrab->Transform()->GetRelativePos();
					RigidBody()->SetGrabPos(vPos);
					RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWING);
					m_CurState = PLAYER_STATE::SWING;
					Gravity()->SetGrab(true);
					m_bCanRopeDash = true;

					if (binitSpeed)
					{
						RigidBody()->SetVelocity(Vec2(0.f, 0.f));
						binitSpeed = false;

						RigidBody()->SetSwingStartPos(Vec3(Transform()->GetRelativePos()));
					}
				}
			}
		}
		else if (pGrab->GetScript<CGrabScript>()->GetGrabState() != GRAB_STATE::GRABING && Gravity()->IsOnGround() && !pChild[0]->GetScript<CArmScript>()->IsHolding())
		{
			RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::DEFAULT);
		}
		else if (KEY_RELEASED(KEY::LBTN))
		{
			if (m_PrevState == PLAYER_STATE::HOLDING)
			{
				pChild[2]->GetScript<CHoldAimScript>()->SetHolding(false);

				Gravity()->SetOnGround(false);
				pChild[0]->GetScript<CArmScript>()->SetHolding(false);
				pChild[0]->GetScript<CArmScript>()->SetAttack(true);
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				RigidBody()->SetHolding(true);
				CreateEffect(PlayerEffect_TYPE::ENEMYATTACK);

				Vec3 vDir = pChild[2]->GetScript<CHoldAimScript>()->GetDir();
				RigidBody()->SetVelocity(Vec2(vDir.x * 700.f, vDir.y * 700.f));
				m_CurState = PLAYER_STATE::SWINGJUMP;

				pChild[4]->GetScript<CAfterImageManagerScript>()->SetAfterImage(AFTERIMAGE_TYPE::NOT);

				GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Execute01.wav", 1, 0.1f);
			}
			else if (m_PrevState == PLAYER_STATE::SWING)
			{
				pGrab->GetScript<CGrabScript>()->SetGrabState(GRAB_STATE::GRABRETURN);
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				Gravity()->SetGrab(false);
				binitSpeed = true;
				m_CurState = PLAYER_STATE::SWINGJUMP;
				RigidBody()->SetSwingEndPos(Vec3(Transform()->GetRelativePos()));
				RigidBody()->SwingDir();
			}
		}

	}


	if (!pChild[0]->GetScript<CArmScript>()->IsHolding() && m_CurState != PLAYER_STATE::DAMAGE && m_CurState != PLAYER_STATE::DEATH)
	{
		if (KEY_PRESSED(KEY::D))
		{
			if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
				RigidBody()->SetAccelAlpha(Vec2(300.f, 0.f));
			else if (m_CurState == PLAYER_STATE::SWINGJUMP || m_CurState == PLAYER_STATE::SWINGJUMP_ROLLING || (IsShot() && Gravity()->IsOnGround()))
			{
				RigidBody()->AddVelocity(Vec2(100.f * DT, 0.f));
				//RigidBody()->SetVelocity(Vec2(200.f, 0.f));
			}
			else if (m_CurState != PLAYER_STATE::SWINGJUMP && m_CurState != PLAYER_STATE::SWINGJUMP_ROLLING && !IsShot())
			{
				RigidBody()->SetVelocity(Vec2(m_fSpeed, RigidBody()->GetVelocity().y));
				if (!Gravity()->IsSideGround())
					m_CurState = PLAYER_STATE::RUN;
			}
		}
		if (KEY_RELEASED(KEY::D))
		{
			if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
				int a = 0;
			else if (m_CurState == PLAYER_STATE::SWINGJUMP || m_CurState == PLAYER_STATE::SWINGJUMP_ROLLING || (IsShot() && Gravity()->IsOnGround()))
			{
				RigidBody()->SetVelocity(Vec2(0.f, RigidBody()->GetVelocity().y));
			}
			else if (m_CurState != PLAYER_STATE::SWINGJUMP && m_CurState != PLAYER_STATE::SWINGJUMP_ROLLING && !IsShot())
			{
				RigidBody()->SetVelocity(Vec2(0.f, RigidBody()->GetVelocity().y));
				m_CurState = PLAYER_STATE::IDLE;
			}
		}

		if (KEY_PRESSED(KEY::A))
		{
			if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
				RigidBody()->SetAccelAlpha(Vec2(-300.f, 0.f));
			else if (m_CurState == PLAYER_STATE::SWINGJUMP || m_CurState == PLAYER_STATE::SWINGJUMP_ROLLING || (IsShot() && Gravity()->IsOnGround()))
			{
				RigidBody()->AddVelocity(Vec2(-100.f * DT, 0.f));
				//RigidBody()->SetVelocity(Vec2(-200.f, 0.f));
			}
			else if (m_CurState != PLAYER_STATE::SWINGJUMP && m_CurState != PLAYER_STATE::SWINGJUMP_ROLLING && !IsShot())
			{
				RigidBody()->SetVelocity(Vec2(-m_fSpeed, RigidBody()->GetVelocity().y));
				if (!Gravity()->IsSideGround())
					m_CurState = PLAYER_STATE::RUN;
			}
		}
		if (KEY_RELEASED(KEY::A))
		{
			if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
				int a = 0;
			else if (m_CurState == PLAYER_STATE::SWINGJUMP || m_CurState == PLAYER_STATE::SWINGJUMP_ROLLING || (IsShot() && Gravity()->IsOnGround()))
			{
				RigidBody()->SetVelocity(Vec2(0.f, RigidBody()->GetVelocity().y));
			}
			else if (m_CurState != PLAYER_STATE::SWINGJUMP && m_CurState != PLAYER_STATE::SWINGJUMP_ROLLING && !IsShot())
			{
				RigidBody()->SetVelocity(Vec2(0.f, RigidBody()->GetVelocity().y));
				m_CurState = PLAYER_STATE::IDLE;
			}
		}




		if (pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
		{
			if (KEY_PRESSED(KEY::LSHIFT) && AccTime <= m_fDashTime)
			{
				m_bCanRopeDash = false;
				if (!m_bRopeDash)
				{
					m_bRopeDash = true;
					RigidBody()->SetVelocity(Vec2(0.f, RigidBody()->GetVelocity().y));
					pChild[4]->GetScript<CAfterImageManagerScript>()->SetAfterImage(AFTERIMAGE_TYPE::SWING_DASH);
					CreateEffect(PlayerEffect_TYPE::ATTACKDONUT);
				}
				else
				{
					AccTime += DT;

					if (m_bCurLP)
						RigidBody()->SetVelocity(Vec2(200.f, RigidBody()->GetVelocity().y));
					else if (!m_bCurLP)
						RigidBody()->SetVelocity(Vec2(-200.f, RigidBody()->GetVelocity().y));
				}
			}
		}
			if (KEY_RELEASED(KEY::LSHIFT))
			{
				m_bRopeDash = false;
				AccTime = 0.f;
				pChild[4]->GetScript<CAfterImageManagerScript>()->SetAfterImage(AFTERIMAGE_TYPE::NOT);
			}
		
	}

	if (IsClimb())
	{
		RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::DEFAULT);
		if (KEY_PRESSED(KEY::W))
		{
			RigidBody()->SetVelocity(Vec2(0.f, 400.f));
			m_CurState = PLAYER_STATE::CLIMB_UP;
		}
		else if (KEY_PRESSED(KEY::S))
		{
			RigidBody()->SetVelocity(Vec2(0.f, -500.f));
			m_CurState = PLAYER_STATE::SLIDE;
		}
		else if (KEY_RELEASED(KEY::S) || KEY_RELEASED(KEY::W))
		{
			RigidBody()->SetVelocity(Vec2(0.f, 0.f));
			m_CurState = PLAYER_STATE::CLIMB;
		}
		else if (KEY_TAP(KEY::SPACE))
		{
			if (m_bCurLP)
				RigidBody()->SetVelocity(Vec2(-200.f, 600.f));
			else
				RigidBody()->SetVelocity(Vec2(200.f, 600.f));
		}
	}

	
	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);

	if (KEY_TAP(KEY::SPACE) && m_bCanJump && m_CurState != PLAYER_STATE::DEATH)
	{
		Transform()->SetRelativePos(Vec3(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y + 1.f, Transform()->GetRelativePos().z));
		RigidBody()->SetVelocity(Vec2(RigidBody()->GetVelocity().x, 300.f));

		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Jump.wav", 1, 0.1f);
	}

	if (RigidBody()->GetVelocity().x > 0)
	{
		m_bCurLP = true;
	}
	else if (RigidBody()->GetVelocity().x < 0)
	{
		m_bCurLP = false;
	}
	

	

	Dead();

	if (m_CurState == PLAYER_STATE::DEATH && m_PrevState != PLAYER_STATE::DEATH)
	{
		pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.7f, 1.f, Transform()->GetRelativePos());
		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_Player_Death.wav", 1, 0.1f);
	}
	else if (m_CurState == PLAYER_STATE::DASH)
	{
		Dash2Idle();
	}
	else if (m_CurState == PLAYER_STATE::DAMAGE)
	{
		DamageDash();
	}
	else if (IsShot())
	{
		if (Gravity()->IsOnGround())
			RigidBody()->SetVelocity(Vec2(0.f, 0.f));
	}
	else if (IsClimb())
	{
		
	}
	else if (m_CurState == PLAYER_STATE::SWING)
	{
		int a = 0;
	}
	else if (m_CurState == PLAYER_STATE::SWINGJUMP && m_PrevState != PLAYER_STATE::SWINGJUMP)
	{
		if (abs(RigidBody()->GetVelocity().x) < abs(RigidBody()->GetVelocity().y))
		{
			m_CurState = PLAYER_STATE::SWINGJUMP_ROLLING;
		}
	}
	else if (m_PrevState == PLAYER_STATE::SWINGJUMP_ROLLING || m_PrevState == PLAYER_STATE::SWINGJUMP)
	{
		int a = 0;
	}
	else if (RigidBody()->GetCurUpDownState() == RIGIDBODY_UPDOWNSTATE::FALLING && !Gravity()->IsOnGround() && !Gravity()->IsSideGround())
	{
		m_CurState = PLAYER_STATE::FALLING;
		m_bCanJump = false;
	}
	else if (RigidBody()->GetCurUpDownState() == RIGIDBODY_UPDOWNSTATE::JUMPING && !Gravity()->IsOnGround() && !Gravity()->IsSideGround())
	{
		m_CurState = PLAYER_STATE::JUMPING;
		m_bCanJump = false;
	}

	if (Gravity()->IsOnGround())
	{
		m_bCanJump = true;
		if (m_CurState != PLAYER_STATE::RUN && m_CurState != PLAYER_STATE::DAMAGE && m_CurState != PLAYER_STATE::DASH && 
			(m_PrevState == PLAYER_STATE::SWINGJUMP || m_PrevState == PLAYER_STATE::FALLING || m_PrevState == PLAYER_STATE::SWINGJUMP_ROLLING))
		{
			m_CurState = PLAYER_STATE::IDLE;
			RigidBody()->SetVelocity(Vec2(0.f, 0.f));
		}
		else if (m_CurState == PLAYER_STATE::SWING)
		{
			//m_CurState == PLAYER_STATE::ROPE_SLIDE;
		}
	}
	

	
	

	
	if (KEY_TAP(KEY::NUM3))
	{
		Transform()->SetRelativePos(Vec3(3497.f, -2426.f, 500.f));
	}
	if (KEY_TAP(KEY::N))
	{
		if (m_bGod)
		{
			m_bGod = false;
		}
		else
		{
			m_bGod = true;
		}
			
	}

	ChangeAnimation();
	pChild[0]->GetScript<CArmScript>()->ChangeARMState(m_CurState, m_PrevState, m_bCurLP);
	pChild[1]->GetScript<CHPUIScript>()->SetCurHP(m_iHP);

	pChild[5]->GetScript<CCapeScript>()->ChangeState(m_CurState, m_PrevState, m_bCurLP, m_bPrevLP);

	GodTime();

	m_bPrevLP = m_bCurLP;
	m_PrevState = m_CurState;
}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider
	, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (_OtherObj->GetLayerIdx() == 12)
	{
		Damage(_OtherObj->Transform()->GetWorldPos());
	}
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_fSpeed, sizeof(float), 1, _File);
	fwrite(&m_fDashTime , sizeof(float), 1, _File);
	fwrite(&m_fDeathTime , sizeof(float), 1, _File);
	fwrite(&m_iHP, sizeof(int), 1, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_fSpeed, sizeof(float), 1, _File);
	fread(&m_fDashTime, sizeof(float), 1, _File);
	fread(&m_fDeathTime, sizeof(float), 1, _File);
	fread(&m_iHP, sizeof(int), 1, _File);
}


void CPlayerScript::ChangeAnimation()
{
	if (m_CurState == m_PrevState && m_bCurLP == m_bPrevLP)
		return;


	

	switch (m_CurState)
	{
	case PLAYER_STATE::IDLE:
		if (m_PrevState == PLAYER_STATE::FALLING || m_PrevState == PLAYER_STATE::SWINGJUMP || m_PrevState == PLAYER_STATE::SWING)
			CreateEffect(PlayerEffect_TYPE::LANDING);

		if (m_PrevState == PLAYER_STATE::RUN && m_bCurLP)
			Animator2D()->PlayToPlay(L"RUNSTOP_LP", L"IDLE_LP");
		else if (m_bCurLP)
			Animator2D()->Play(L"IDLE_LP");
		if (m_PrevState == PLAYER_STATE::RUN && !m_bCurLP)
			Animator2D()->PlayToPlay(L"RUNSTOP_RP", L"IDLE_RP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"IDLE_RP");
		break;
	case PLAYER_STATE::JUMPING:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"JUMPING_LP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"JUMPING_RP");

		if (m_PrevState == PLAYER_STATE::CLIMB || m_PrevState == PLAYER_STATE::CLIMB_UP)
			CreateEffect(PlayerEffect_TYPE::WALLJUMP);
		else
			if (m_bCurLP == m_bPrevLP)
				CreateEffect(PlayerEffect_TYPE::JUMP);
	}
		break;
	case PLAYER_STATE::DAMAGE:
		if (m_bCurLP)
			Animator2D()->Play(L"DAMAGED_LP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"DAMAGED_RP");
		break;
	case PLAYER_STATE::DASH:
		if (m_bCurLP)
			Animator2D()->Play(L"DASH_LP",false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"DASH_RP",false);
		break;
	case PLAYER_STATE::DASHENDGROUND:
		break;
	case PLAYER_STATE::FALLING:
		if (m_PrevState == PLAYER_STATE::ROLLING)
		{
			if (m_bCurLP)
				Animator2D()->PlayToPlay(L"ROLL2FALL_LP", L"FALLING_LP");
			else if (!m_bCurLP)
				Animator2D()->PlayToPlay(L"ROLL2FALL_RP", L"FALLING_RP");
		}
		else
		{
			if (m_bCurLP)
				Animator2D()->PlayToPlay(L"FALLSTART_LP", L"FALLING_LP");
			else if (!m_bCurLP)
				Animator2D()->PlayToPlay(L"FALLSTART_RP", L"FALLING_RP");
			if (m_bCurLP != m_bPrevLP)
			{
				if (m_bCurLP)
					Animator2D()->Play(L"FALLING_LP");
				else if (!m_bCurLP)
					Animator2D()->Play(L"FALLING_RP");
			}
		}
		break;
	case PLAYER_STATE::ROLLING:
		if (m_bCurLP)
			Animator2D()->Play(L"ROLLING_LP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"ROLLING_RP");
		break;
	case PLAYER_STATE::RUN:
	{
		if (m_PrevState == PLAYER_STATE::FALLING || m_PrevState == PLAYER_STATE::SWINGJUMP || m_PrevState == PLAYER_STATE::SWING)
		{
			if (m_bCurLP)
				Animator2D()->PlayToPlay(L"RAND2RUN_LP", L"RUNNING_LP");
			else if (!m_bCurLP)
				Animator2D()->PlayToPlay(L"RAND2RUN_RP", L"RUNNING_RP");

			CreateEffect(PlayerEffect_TYPE::LANDING);
		}
		else if (m_bCurLP)
			Animator2D()->PlayToPlay(L"RUNSTART_LP", L"RUNNING_LP");
		else if (!m_bCurLP)
			Animator2D()->PlayToPlay(L"RUNSTART_RP", L"RUNNING_RP");

		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Footstep_Concrete A.wav", 1, 0.1f);
	}
		break;
	case PLAYER_STATE::SHOT_DOWN:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTGNDDOWN_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTGNDDOWN_RP", false);
	}
		break;
	case PLAYER_STATE::SHOT_FRONT:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTGNDFRONT_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTGNDFRONT_RP", false); 
	}
		break;
	case PLAYER_STATE::SHOT_UP:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTGNDUP_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTGNDUP_RP", false);
	}
		break;
	case PLAYER_STATE::SHOT_AIR_DOWN:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTAIRDOWN_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTAIRDOWN_RP", false);
	}
		break;
	case PLAYER_STATE::SHOT_AIR_FRONT:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTAIRFRONT_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTAIRFRONT_RP", false);
	}
		break;
	case PLAYER_STATE::SHOT_AIR_UP:
	{
		if (m_bCurLP)
			Animator2D()->Play(L"SHOTAIRUP_LP", false);
		else if (!m_bCurLP)
			Animator2D()->Play(L"SHOTAIRUP_RP", false);
	}
		break;
	case PLAYER_STATE::SWING:
		if (m_bCurLP)
			Animator2D()->Play(L"SWING_LP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"SWING_RP");
		break;
	case PLAYER_STATE::SWINGJUMP:
	{
		if (m_PrevState == PLAYER_STATE::HOLDING)
		{
			if (m_bCurLP)
				Animator2D()->PlayToPlay(L"ROLLING_LP", L"FALLING_LP");
			else if (!m_bCurLP)
				Animator2D()->PlayToPlay(L"ROLLING_RP", L"FALLING_RP");
		}
		else if (m_bCurLP)
			Animator2D()->PlayToPlay(L"SWINGJUMP_LP", L"FALLING_LP");
		else if (!m_bCurLP)
			Animator2D()->PlayToPlay(L"SWINGJUMP_RP", L"FALLING_RP");
	}
		break;
	case PLAYER_STATE::SWINGJUMP_ROLLING:
		if (m_bCurLP)
			Animator2D()->PlayToPlay(L"SWINGJUMPUP_LP", L"ROLLING_LP");
		else if (!m_bCurLP)
			Animator2D()->PlayToPlay(L"SWINGJUMPUP_RP", L"ROLLING_RP");
		break;
	case PLAYER_STATE::CLIMB_UP:
		if (m_bCurLP)
		{
			Animator2D()->Play(L"CLIMBUP_LP");
		}
		else if (!m_bCurLP)
		{
			Animator2D()->Play(L"CLIMBUP_RP");
		}
		break;
	case PLAYER_STATE::CLIMB:
		if (m_bCurLP)
		{
			Animator2D()->Play(L"CLIMBUP_IDLE_LP");
		}
		else if (!m_bCurLP)
		{
			Animator2D()->Play(L"CLIMBUP_IDLE_RP");
		}
		break;
	case PLAYER_STATE::SLIDE:
	{
		if (m_bCurLP)
			Animator2D()->PlayToPlay(L"SLIDESTART_LP", L"SLIDING_LP");
		else if (!m_bCurLP)
			Animator2D()->PlayToPlay(L"SLIDESTART_RP", L"SLIDING_RP");

		CreateEffect(PlayerEffect_TYPE::WALLSLIDING);
	}
		break;
	case PLAYER_STATE::HOLDING:
		if (m_bCurLP)
			Animator2D()->Play(L"EXCHOLDING_BACK_LP");
		else if (!m_bCurLP)
			Animator2D()->Play(L"EXCHOLDING_BACK_RP");
		break;
	case PLAYER_STATE::DEATH:
		Animator2D()->Play(L"DEATH", false);
	default:
		break;
	}



}

void CPlayerScript::DamageDash()
{
	CTimeMgr::GetInst()->SetDeltaTimeSpeed(0.3);

	Vec2 vDir[8] = { Vec2{-1.0f, 0.0f},		// left
					 Vec2{-0.5f, -0.5f},	// left bottom
					 Vec2{-0.5f, 0.5f},		// left top
					 Vec2{0.0f, 1.0f},		// top
					 Vec2{0.0f,-1.0f},		// bottom
					 Vec2{1.0f, 0.0f},		// right
					 Vec2{0.5f, -0.5f},		// right bottom
					 Vec2{0.5f, 0.5f} };	// right top


	if (KEY_PRESSED(KEY::SPACE))
	{
		if (KEY_PRESSED(KEY::A))
		{
			if (KEY_PRESSED(KEY::W))
			{
				// 왼쪽위
				RigidBody()->SetVelocity(Vec2(vDir[2].x * 400.f, vDir[2].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
			else if (KEY_PRESSED(KEY::S))
			{
				// 왼쪽아래
				RigidBody()->SetVelocity(Vec2(vDir[1].x * 400.f, vDir[1].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
			else
			{
				// 왼쪽
				RigidBody()->SetVelocity(Vec2(vDir[0].x * 400.f, vDir[0].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
		}
		else if (KEY_PRESSED(KEY::W))
		{
			// 위
			RigidBody()->SetVelocity(Vec2(vDir[3].x * 400.f, vDir[3].y * 400.f));
			RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
			m_CurState = PLAYER_STATE::DASH;
		}
		else if (KEY_PRESSED(KEY::S))
		{
			// 아래
			RigidBody()->SetVelocity(Vec2(vDir[4].x * 400.f, vDir[4].y * 400.f));
			RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
			m_CurState = PLAYER_STATE::DASH;
		}
		else if (KEY_PRESSED(KEY::D))
		{
			if (KEY_PRESSED(KEY::W))
			{
				// 오른쪽 위
				RigidBody()->SetVelocity(Vec2(vDir[7].x * 400.f, vDir[7].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
			else if (KEY_PRESSED(KEY::S))
			{
				// 오른쪽 아래
				RigidBody()->SetVelocity(Vec2(vDir[6].x * 400.f, vDir[6].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
			else
			{
				// 오른쪽
				RigidBody()->SetVelocity(Vec2(vDir[5].x * 400.f, vDir[5].y * 400.f));
				RigidBody()->SetCurRigidBodyState(RIGIDBODY_STATE::SWINGJUMP);
				m_CurState = PLAYER_STATE::DASH;
			}
		}

		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_ChargeDash.wav", 1, 0.1f);
	}
	else
	{
		// 아무방향으로도 대쉬하지않을경우
		//m_CurState = PLAYER_STATE::IDLE;
	}
}

void CPlayerScript::Dash2Idle()
{
	static float fAcc = 0.f;
	static float fDashTime = 0.4f;

	if (fAcc > fDashTime)
	{
		m_CurState = PLAYER_STATE::IDLE;
		fAcc = 0.f;
	}
	fAcc += DT;
}

void CPlayerScript::GodTime()
{
	static float fAcc = 0.f;

	if (m_bGod)
	{
		fAcc += DT;
		
		
		if (fAcc >= m_fGodTime)
		{
			m_bGod = false;
			fAcc = 0.f;
		}
	}
	else
	{
		return;
	}
}

bool CPlayerScript::IsClimb()
{
	if (Gravity()->IsSideGround())
	{
		return true;
	}
	else
		return false;
}

bool CPlayerScript::IsShot()
{
	static float fAcc = 0.f;
	static float fChangeTime = 0.4f;

	if (m_CurState == PLAYER_STATE::SHOT_FRONT 
		|| m_CurState == PLAYER_STATE::SHOT_UP
		|| m_CurState == PLAYER_STATE::SHOT_DOWN
		|| m_CurState == PLAYER_STATE::SHOT_AIR_FRONT
		|| m_CurState == PLAYER_STATE::SHOT_AIR_UP
		|| m_CurState == PLAYER_STATE::SHOT_AIR_DOWN)
	{
		if (fAcc > fChangeTime)
		{
			m_CurState = PLAYER_STATE::IDLE;
			fAcc = 0.f;
			return false;
		}
		fAcc += DT;
		return true;
	}
	else
		return false;
}

void CPlayerScript::CreateEffect(PlayerEffect_TYPE _Type)
{
	vector<CGameObject*> pChild = GetOwner()->GetChild();
	CGameObject* pCursor = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Cursor");
	Vec3 vCursorPos = pCursor->Transform()->GetRelativePos();

	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"Effect");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CPlayerEffectScript);

	Vec3 vPlayerPos = Transform()->GetRelativePos();
	Vec3 vPlayerScale = Transform()->GetRelativeScale();

	Vec2 vOffsetScale = Collider2D()->GetOffsetScale();


	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));
	

	switch (_Type)
	{
	case PlayerEffect_TYPE::NOT:
		break;
	case PlayerEffect_TYPE::JUMP:
	{
		pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y - vOffsetScale.y /2.f, vPlayerPos.z));
		pObj->Transform()->SetRelativeScale(Vec3(256.f, 256.f, 1.f));
		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Jump.wav", 1, 0.1f);
	}
		break;
	case PlayerEffect_TYPE::LANDING:
	{
		pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y - vOffsetScale.y / 2.f, vPlayerPos.z));
		pObj->Transform()->SetRelativeScale(Vec3(256.f, 256.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::WALLJUMP:
	{
		
		CGameObject* pOverlapObj = pChild[3]->GetScript<CClimbBarScript>()->GetOverlapObj();

		Vec3 vOverlapObjPos = pOverlapObj->Transform()->GetWorldPos();
		Vec2 vOverlapObjOffsetScale = pOverlapObj->Collider2D()->GetOffsetScale();

		if(m_bCurLP)
			pObj->Transform()->SetRelativePos(Vec3(vOverlapObjPos.x + (vOverlapObjOffsetScale.x / 2.f) + 15.f, vPlayerPos.y, vPlayerPos.z));
		else
			pObj->Transform()->SetRelativePos(Vec3(vOverlapObjPos.x - (vOverlapObjOffsetScale.x / 2.f) - 15.f, vPlayerPos.y, vPlayerPos.z));

		pObj->Transform()->SetRelativeScale(Vec3(256.f, 256.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::WALLSLIDING:
	{
		if (m_bCurLP)
			pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x + vOffsetScale.x / 2.f, vPlayerPos.y, vPlayerPos.z));
		else
			pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x - vOffsetScale.x / 2.f, vPlayerPos.y, vPlayerPos.z));

		pObj->Transform()->SetRelativeScale(Vec3(256.f, 256.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::ATTACKDONUT:
	{
		if (m_CurState == PLAYER_STATE::HOLDING)
		{
			Vec3 vBeforeHoldingPos = pChild[0]->GetScript<CArmScript>()->GetBeforeHodlingPos();

			if (m_bCurLP)
				pObj->Transform()->SetRelativePos(Vec3(vBeforeHoldingPos.x, vPlayerPos.y, vPlayerPos.z));
			else
				pObj->Transform()->SetRelativePos(Vec3(vBeforeHoldingPos.x, vPlayerPos.y, vPlayerPos.z));
		}
		else
		{
			if (m_bCurLP)
				pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z));
			else
				pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z));
		}

		pObj->Transform()->SetRelativeRotation(Transform()->GetRelativeRotation());
		pObj->Transform()->SetRelativeScale(Vec3(256.f, 256.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::GRABSHOTGAS:
	{
		float fx = vCursorPos.x - vPlayerPos.x;
		float fy = vCursorPos.y - vPlayerPos.y;

		// 현재각도
		float fCurAngle = atan2f(fy, fx);


		float fDe = XMConvertToDegrees(fCurAngle);
		fDe += 135.f;

		float fRadi = XMConvertToRadians(fDe);

		

		if (vCursorPos.x < vPlayerPos.x)
		{
			fDe += 90.f;
			fRadi = XMConvertToRadians(fDe);

			pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x + cos(fRadi) * 40.f,
				vPlayerPos.y + sin(fRadi) * 40.f,
				Transform()->GetRelativePos().z));

			fDe -= 205.f;


			pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
				Transform()->GetRelativeRotation().y,
				XMConvertToRadians(fDe)));
		}
		else
		{
			pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x + cos(fRadi) * 40.f,
				vPlayerPos.y + sin(fRadi) * 40.f,
				Transform()->GetRelativePos().z));

			fDe += 10.f;

			pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
				Transform()->GetRelativeRotation().y,
				XMConvertToRadians(fDe)));
		}


		pObj->Transform()->SetRelativeScale(Vec3(528.f, 528.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::GRABSHOTFIRE:
	{
		float fx = vCursorPos.x - vPlayerPos.x;
		float fy = vCursorPos.y - vPlayerPos.y;

		// 현재각도
		float fCurAngle = atan2f(fy, fx);


		float fDe = XMConvertToDegrees(fCurAngle);
		fDe += 180.f;

		float fRadi = XMConvertToRadians(fDe);

		// 상수값아닌 출발 - 도착위치의 거리넣어줘야함
		pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x + cos(fRadi) * 30.f,
			vPlayerPos.y + sin(fRadi) * 30.f,
			Transform()->GetRelativePos().z));

		if (vCursorPos.x < vPlayerPos.x)
		{
			fDe -= 180.f;
			pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
				Transform()->GetRelativeRotation().y,
				XMConvertToRadians(fDe)));
		}
		else
		{
			pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativeRotation().x,
				Transform()->GetRelativeRotation().y,
				XMConvertToRadians(fDe)));
		}


		pObj->Transform()->SetRelativeScale(Vec3(528.f, 528.f, 1.f));
	}
		break;
	case PlayerEffect_TYPE::DAMAGETILE:
		break;
	case PlayerEffect_TYPE::ENEMYATTACK:
	{
		pObj->Transform()->SetRelativePos(Vec3(vPlayerPos.x, vPlayerPos.y, vPlayerPos.z));

		pObj->Transform()->SetRelativeScale(Vec3(640.f, 640.f, 1.f));
	}
		break;
	default:
		return;
		break;
	}
	pObj->GetScript<CPlayerEffectScript>()->SetEffectType(_Type);

	GamePlayStatic::SpawnGameObject(pObj, 5);
	
}

void CPlayerScript::Dead()
{
	if (m_iHP > 0)
		return;

	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

	Gravity()->SetGravity(0.f);
	RigidBody()->SetVelocity(Vec2{});
	m_CurState = PLAYER_STATE::DEATH;

	if (m_fAccTime > m_fDeathTime && !m_bFade)
	{
		pMainCamera->GetScript<CCameraScript>()->FadeIn(2.9f, Vec3{});
		m_bFade = true;
	}
	else if (m_fAccTime > m_fDeathTime + 3.f)
	{
		Transform()->SetRelativePos(Vec3(-4484.f, -4667.f, 500.f));
		pMainCamera->GetScript<CCameraScript>()->FadeOut(1.f);
		m_CurState = PLAYER_STATE::IDLE;
		m_iHP = 4;
		m_fAccTime = 0.f;
		pMainCamera->Camera()->SetScale(1.f);

		return;
	}
	else
	{
		m_fAccTime += DT;
	}
}

void CPlayerScript::Damage(Vec3 _DamageObjPos)
{
	vector<CGameObject*> pChild = GetOwner()->GetChild();
	if (pChild[0]->GetScript<CArmScript>()->IsHolding() || m_bGod)
		return;
	
	CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	pMainCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 0.2f, 25.f, CAMERA_SHAKE_TYPE::FOURDIR_LT);

	Vec3 vDir = _DamageObjPos - Transform()->GetWorldPos();
	vDir.Normalize();
	RigidBody()->SetVelocity(Vec2(-vDir.x * 200.f, -vDir.y * 200.f));
	m_CurState = PLAYER_STATE::DAMAGE;
	GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Damaged.wav",1,0.1f);
	m_iHP--;

	m_bGod = true;
}