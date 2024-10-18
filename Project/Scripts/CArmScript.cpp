#include "pch.h"
#include "CArmScript.h"
#include "CSearchBarScript.h"
#include "CGrabScript.h"
#include "CBossScript.h"
#include "CGrabTailScript.h"
#include "CChainScript.h"
#include "CCameraScript.h"

#include <Engine/CLevel.h>
#include <Engine/CLevelMgr.h>

CArmScript::CArmScript()
	: CScript(ARMSCRIPT)
	, m_SearchObj(nullptr)
	, m_ChainObj(nullptr)
	, m_CurEnemyObj(nullptr)
	, m_vSearchBarScale{ 1.f, 1.f, 1.f }
	, m_vSearch {}
	, m_fRadian (0.f)
	, m_fCosTheta (0.f)
	, m_bHolding(false)
{
}

CArmScript::~CArmScript()
{
}



void CArmScript::begin()
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Radian", &m_fRadian);
	AddScriptParam(SCRIPT_PARAM::FLOAT, "CosTheta", &m_fCosTheta);

	Ptr<CTexture> pAltasTex;

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Idle.png", L"texture\\Arm\\Spr_SNBArm_Idle.png");
	Animator2D()->Create(L"ARM_IDLE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Idle_rp.png", L"texture\\Arm\\Spr_SNBArm_Idle_rp.png");
	Animator2D()->Create(L"ARM_IDLE_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Damaged.png", L"texture\\Arm\\Spr_SNBArm_Damaged.png");
	Animator2D()->Create(L"ARM_DAMAGE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Damaged_rp.png", L"texture\\Arm\\Spr_SNBArm_Damaged_rp.png");
	Animator2D()->Create(L"ARM_DAMAGE_RP", pAltasTex, Vec2(400.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_ExcDash.png", L"texture\\Arm\\Spr_SNBArm_ExcDash.png");
	Animator2D()->Create(L"ARM_DASH_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 17, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_ExcDash_rp.png", L"texture\\Arm\\Spr_SNBArm_ExcDash_rp.png");
	Animator2D()->Create(L"ARM_DASH_RP", pAltasTex, Vec2(1360.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 17, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_DashEndGround.png", L"texture\\Arm\\Spr_SNBArm_DashEndGround.png");
	Animator2D()->Create(L"ARM_DASHENDGND_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_DashEndGround_rp.png", L"texture\\Arm\\Spr_SNBArm_DashEndGround_rp.png");
	Animator2D()->Create(L"ARM_DASHENDGND_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Falling.png", L"texture\\Arm\\Spr_SNBArm_Falling.png");
	Animator2D()->Create(L"ARM_FALLING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Falling_rp.png", L"texture\\Arm\\Spr_SNBArm_Falling_rp.png");
	Animator2D()->Create(L"ARM_FALLING_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_FallStart.png", L"texture\\Arm\\Spr_SNBArm_FallStart.png");
	Animator2D()->Create(L"ARM_FALLSTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_FallStart_rp.png", L"texture\\Arm\\Spr_SNBArm_FallStart_rp.png");
	Animator2D()->Create(L"ARM_FALLSTART_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Grabbed.png", L"texture\\Arm\\Spr_SNBArm_Grabbed.png");
	Animator2D()->Create(L"ARM_GRABBED_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Grabbed_rp.png", L"texture\\Arm\\Spr_SNBArm_Grabbed_rp.png");
	Animator2D()->Create(L"ARM_GRABBED_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Jumping.png", L"texture\\Arm\\Spr_SNBArm_Jumping.png");
	Animator2D()->Create(L"ARM_JUMPING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Jumping_rp.png", L"texture\\Arm\\Spr_SNBArm_Jumping_rp.png");
	Animator2D()->Create(L"ARM_JUMPING_RP", pAltasTex, Vec2(480.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Land2Run.png", L"texture\\Arm\\Spr_SNBArm_Land2Run.png");
	Animator2D()->Create(L"ARM_LAND2RUN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Land2Run_rp.png", L"texture\\Arm\\Spr_SNBArm_Land2Run_rp.png");
	Animator2D()->Create(L"ARM_LAND2RUN_RP", pAltasTex, Vec2(960.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Landing.png", L"texture\\Arm\\Spr_SNBArm_Landing.png");
	Animator2D()->Create(L"ARM_LANDING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Landing_rp.png", L"texture\\Arm\\Spr_SNBArm_Landing_rp.png");
	Animator2D()->Create(L"ARM_LANDING_RP", pAltasTex, Vec2(240.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 3, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Returning.png", L"texture\\Arm\\Spr_SNBArm_Returning.png");
	Animator2D()->Create(L"ARM_RETURN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Returning_rp.png", L"texture\\Arm\\Spr_SNBArm_Returning_rp.png");
	Animator2D()->Create(L"ARM_RETURN_RP", pAltasTex, Vec2(160.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Reversal.png", L"texture\\Arm\\Spr_SNBArm_Reversal.png");
	Animator2D()->Create(L"ARM_REVERSAL_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Reversal_rp.png", L"texture\\Arm\\Spr_SNBArm_Reversal_rp.png");
	Animator2D()->Create(L"ARM_REVERSAL_RP", pAltasTex, Vec2(720.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Roll2Fall.png", L"texture\\Arm\\Spr_SNBArm_Roll2Fall.png");
	Animator2D()->Create(L"ARM_ROLL2FALL_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Roll2Fall_rp.png", L"texture\\Arm\\Spr_SNBArm_Roll2Fall_rp.png");
	Animator2D()->Create(L"ARM_ROLL2FALL_RP", pAltasTex, Vec2(640.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 8, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Rolling.png", L"texture\\Arm\\Spr_SNBArm_Rolling.png");
	Animator2D()->Create(L"ARM_ROLLING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Rolling_rp.png", L"texture\\Arm\\Spr_SNBArm_Rolling_rp.png");
	Animator2D()->Create(L"ARM_ROLLING_RP", pAltasTex, Vec2(960.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 12, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Running.png", L"texture\\Arm\\Spr_SNBArm_Running.png");
	Animator2D()->Create(L"ARM_RUNNING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 20, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Running_rp.png", L"texture\\Arm\\Spr_SNBArm_Running_rp.png");
	Animator2D()->Create(L"ARM_RUNNING_RP", pAltasTex, Vec2(1600.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 20, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_RunStart.png", L"texture\\Arm\\Spr_SNBArm_RunStart.png");
	Animator2D()->Create(L"ARM_RUNSTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_RunStart_rp.png", L"texture\\Arm\\Spr_SNBArm_RunStart_rp.png");
	Animator2D()->Create(L"ARM_RUNSTART_RP", pAltasTex, Vec2(160.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 2, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_RunStop.png", L"texture\\Arm\\Spr_SNBArm_RunStop.png");
	Animator2D()->Create(L"ARM_RUNSTOP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_RunStop_rp.png", L"texture\\Arm\\Spr_SNBArm_RunStop_rp.png");
	Animator2D()->Create(L"ARM_RUNSTOP_RP", pAltasTex, Vec2(480.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Shoot.png", L"texture\\Arm\\Spr_SNBArm_Shoot.png");
	Animator2D()->Create(L"ARM_SHOOT_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_Shoot_rp.png", L"texture\\Arm\\Spr_SNBArm_Shoot_rp.png");
	Animator2D()->Create(L"ARM_SHOOT_RP", pAltasTex, Vec2(480.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 6, 10, true);
	
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_SwingJump.png", L"texture\\Arm\\Spr_SNBArm_SwingJump.png");
	Animator2D()->Create(L"ARM_SWINGJUMP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_SwingJump_rp.png", L"texture\\Arm\\Spr_SNBArm_SwingJump_rp.png");
	Animator2D()->Create(L"ARM_SWINGJUMP_RP", pAltasTex, Vec2(720.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 9, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_SwingJumpUp.png", L"texture\\Arm\\Spr_SNBArm_SwingJumpUp.png");
	Animator2D()->Create(L"ARM_SWINGJUMPUP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_SwingJumpUp_rp.png", L"texture\\Arm\\Spr_SNBArm_SwingJumpUp_rp.png");
	Animator2D()->Create(L"ARM_SWINGJUMPUP_RP", pAltasTex, Vec2(400.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 5, 10, true);

	// TileDamage -> ImageTool
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbUp.png", L"texture\\Arm\\Spr_SNBArm_WallClimbUp.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_IDLE_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 1, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbUp_rp.png", L"texture\\Arm\\Spr_SNBArm_WallClimbUp_rp.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_IDLE_RP", pAltasTex, Vec2(80.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 1, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbDown.png", L"texture\\Arm\\Spr_SNBArm_WallClimbDown.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_DOWN_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbDown_rp.png", L"texture\\Arm\\Spr_SNBArm_WallClimbDown_rp.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_DOWN_RP", pAltasTex, Vec2(560.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbUp.png", L"texture\\Arm\\Spr_SNBArm_WallClimbUp.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_UP_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallClimbUp_rp.png", L"texture\\Arm\\Spr_SNBArm_WallClimbUp_rp.png");
	Animator2D()->Create(L"ARM_WALLCLIMB_UP_RP", pAltasTex, Vec2(560.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 7, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallSlideStart.png", L"texture\\Arm\\Spr_SNBArm_WallSlideStart.png");
	Animator2D()->Create(L"ARM_WALLSLIDESTART_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallSlideStart_rp.png", L"texture\\Arm\\Spr_SNBArm_WallSlideStart_rp.png");
	Animator2D()->Create(L"ARM_WALLSLIDESTART_RP", pAltasTex, Vec2(880.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallSliding.png", L"texture\\Arm\\Spr_SNBArm_WallSliding.png");
	Animator2D()->Create(L"ARM_WALLSLIDING_LP", pAltasTex, Vec2(0.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, false);
	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\Arm\\Spr_SNBArm_WallSliding_rp.png", L"texture\\Arm\\Spr_SNBArm_WallSliding_rp.png");
	Animator2D()->Create(L"ARM_WALLSLIDING_RP", pAltasTex, Vec2(880.f, 0.f), Vec2(80.f, 80.f), Vec2(0.f, 0.f), Vec2(130.f, 130.f), 11, 10, true);

	pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\NONE.png", L"texture\\NONE.png");
	Animator2D()->Create(L"NONE", pAltasTex, Vec2(0.f, 0.f), Vec2(16.f, 16.f), Vec2(0.f, 0.f), Vec2(30.f, 30.f), 1, 10, false);

	GetRenderComponent()->GetDynamicMaterial();

	Animator2D()->Play(L"ARM_IDLE_LP");

	m_SearchObj = new CGameObject;
	m_SearchObj->SetName(L"SearchBar");

	m_SearchObj->AddComponent(new CTransform);
	m_SearchObj->AddComponent(new CCollider2D);
	m_SearchObj->AddComponent(new CSearchBarScript);

	m_SearchObj->Transform()->SetRelativePos(Vec3(0.f, 0.f, 0.f));
	m_SearchObj->Transform()->SetRelativeScale(m_vSearchBarScale);

	m_SearchObj->Collider2D()->SetOffsetPos(Vec2(0.55f, 0.f));
	m_SearchObj->Collider2D()->SetOffsetScale(Vec2(1.f, 1.f));

	GetOwner()->AddChild(m_SearchObj);

	m_ChainObj = new CGameObject;
	m_ChainObj->SetName(L"Chain");

	m_ChainObj->AddComponent(new CTransform);
	m_ChainObj->AddComponent(new CMeshRender);
	m_ChainObj->AddComponent(new CAnimator2D);
	m_ChainObj->AddComponent(new CChainScript);

	m_ChainObj->Transform()->SetRelativePos(Vec3{});
	m_ChainObj->Transform()->SetAbsolute(true);

	m_ChainObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	m_ChainObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"LaserMtrl"));

	GamePlayStatic::SpawnGameObject(m_ChainObj, 5);

	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	pCurLevel->AddObject(m_SearchObj, 20);
}

void CArmScript::tick()
{
	CGameObject* pCursor = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Cursor");
	
	CGameObject* pGrab = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Grab");
	CGameObject* pPlayer = GetOwner()->GetParent();

	m_vSearch = pCursor->Transform()->GetRelativePos() - pPlayer->Transform()->GetRelativePos();
	m_vSearch.Normalize();
	m_SearchObj->GetScript<CSearchBarScript>()->SetDir(m_vSearch);


	
	

	if (pGrab && KEY_TAP(KEY::LBTN))
	{
		GrabAction(pGrab);
		GamePlayStatic::Play2DSound(L"sound\\Player\\SFX_SNB_Shoot.wav", 1, 0.1f);

		pPlayer->GetScript<CPlayerScript>()->CreateEffect(PlayerEffect_TYPE::GRABSHOTFIRE);
		pPlayer->GetScript<CPlayerScript>()->CreateEffect(PlayerEffect_TYPE::GRABSHOTGAS);
	}

	if (m_bHolding)
	{
		if (m_CurEnemyObj->GetName() == L"Boss Attack point")
		{
			if (m_CurEnemyObj->GetParent()->GetScript<CBossScript>()->GetCurBossState() == BOSS_STATE::PhaseFinal_3rdHooked)
			{
				m_CurEnemyObj->GetParent()->GetScript<CBossScript>()->SetBossState(BOSS_STATE::PhaseFinal_BeforePounding);
				m_CurEnemyObj->GetParent()->StateMachine()->GetFSM()->SetState(L"BeforePoundingState");
				Vec3 vPos = m_CurEnemyObj->GetParent()->Transform()->GetRelativePos();

				CGameObject* pMainCamera = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

				pMainCamera->GetScript<CCameraScript>()->ZoomInWithTime(0.1f, 3.f);
				pMainCamera->Transform()->SetRelativePos(Vec3(vPos.x + 20.f, -150.f, vPos.z));

				pMainCamera->GetScript<CCameraScript>()->SetShakeOnOff(true, 1000.f, 0.2f, CAMERA_SHAKE_TYPE::TOP_TO_BOTTOM);

				GamePlayStatic::DestroyGameObject(GetOwner()->GetParent());
			}
			else
			{
				m_CurEnemyObj->GetParent()->GetScript<CBossScript>()->Holding();
			}
		}
		else
		{
			// 일반몹
			if (m_CurEnemyObj->GetScript<CEnemyScript>() != nullptr)
				m_CurEnemyObj->GetScript<CEnemyScript>()->Holding();
		}
	}
	else if (!m_bHolding&& m_bEnemyAttack)
	{
		if (m_CurEnemyObj != nullptr)
		{
			if (m_CurEnemyObj->GetName() == L"Boss Attack point")
			{
				m_CurEnemyObj->GetParent()->GetScript<CBossScript>()->Damage();
			}
			else
			{
				// 일반몹
				if (m_CurEnemyObj->GetScript<CEnemyScript>() != nullptr)
					m_CurEnemyObj->GetScript<CEnemyScript>()->Dead();
			}
			m_CurEnemyObj = nullptr;
		}
		m_bEnemyAttack = false;
	}

	RotateReset(pGrab);
	

	// 그랩중, 홀딩중 일땐 탐색 X
	m_SearchObj->GetScript<CSearchBarScript>()->SetSearchAct(pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::NOT && !m_bHolding);
}

void CArmScript::RotateReset(CGameObject* _pGrab)
{
	static bool bFirstGrab = false;
	static float fCorrection = 0.f;

	Vec3 vRotParent = GetOwner()->GetParent()->Transform()->GetRelativeRotation();

	Vec3 vRot = Transform()->GetRelativeRotation();
	float fCurAngle = 0.f;
	float fDe = 0.f;

	//if (GetOwner()->GetParent()->GetScript<CPlayerScript>()->GetCurPlayerState() == PLAYER_STATE::SWING)
	if (_pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABING)
	{
		Vec3 vPos = _pGrab->Transform()->GetWorldPos();

		float fx = vPos.x - Transform()->GetWorldPos().x;
		float fy = vPos.y - Transform()->GetWorldPos().y;

		// 현재각도
		fCurAngle = atan2f(fy, fx);

		fDe = XMConvertToDegrees(fCurAngle);

		float fParentRot = vRotParent.z;
		fParentRot *= -1;


		if (!bFirstGrab)
		{
			Vec3 v = Transform()->GetLocalDir(DIR_TYPE::RIGHT);
			Vec3 v1 = _pGrab->Transform()->GetLocalDir(DIR_TYPE::RIGHT);
			if ((fDe >= 90.f && fDe < 180.f) || (fDe <= -90 && fDe > -180.f))
			{
				fCorrection = -180.f;
			}
			else
			{
				fCorrection = 0.f;
			}
			bFirstGrab = true;
		}

		fDe += fCorrection;
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, fParentRot + XMConvertToRadians(fDe)));
	}
	else if (_pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::FLYING || _pGrab->GetScript<CGrabScript>()->GetGrabState() == GRAB_STATE::GRABRETURN)
	{
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, -vRotParent.z + m_fNotShootDE));
		bFirstGrab = false;
	}
	else
	{
		Transform()->SetRelativeRotation(Vec3(vRot.x, vRot.y, 0.f));
		bFirstGrab = false;
	}
}

void CArmScript::ShootGrab(CGameObject* _pGrab)
{
	Vec3 vPos = m_SearchObj->GetScript<CSearchBarScript>()->GetSearchObjPos();
	CGameObject* pObj = m_SearchObj->GetScript<CSearchBarScript>()->GetSearchObj();

	Vec3 vTargetObjpos = pObj->Transform()->GetWorldPos();
	Vec3 vTargetObjScale = Vec3(pObj->Collider2D()->GetOffsetScale().x, pObj->Collider2D()->GetOffsetScale().y, 1.f);
	Vec3 vDist = vPos - Transform()->GetWorldPos();


	float fx = vPos.x - Transform()->GetWorldPos().x;
	float fy = vPos.y - Transform()->GetWorldPos().y;

	float fCurAngle = atan2f(fy, fx);

	float fDE = XMConvertToDegrees(fCurAngle);
	m_fNotShootDE = fCurAngle;

	PlayerStateSet(fDE);

	fDE -= 90;

	CreateGrabTail(Transform()->GetWorldPos(), vPos);

	_pGrab->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y,
		XMConvertToRadians(fDE)));

	_pGrab->GetScript<CGrabScript>()->SetGrabDirection(m_SearchObj->GetScript<CSearchBarScript>()->GetGrabDir());
	_pGrab->GetScript<CGrabScript>()->SetStartPos(Transform()->GetWorldPos());
	_pGrab->Transform()->SetRelativePos(Transform()->GetWorldPos());
	_pGrab->GetScript<CGrabScript>()->SetArriPos(vPos);
	_pGrab->GetScript<CGrabScript>()->SetNoneGrab(false);
	
	_pGrab->GetScript<CGrabScript>()->SetGrabState(GRAB_STATE::FLYING);
}

void CArmScript::ShootGrabAndReturn(CGameObject* _pGrab)
{
	CGameObject* pCursor = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Cursor");

	Vec3 vCursorPos = pCursor->Transform()->GetRelativePos();
	Vec3 vPos = Transform()->GetWorldPos();

	float fx = vCursorPos.x - vPos.x;
	float fy = vCursorPos.y - vPos.y;


	Vec3 vCurDir = vCursorPos - vPos;
	vCurDir.Normalize();
	_pGrab->GetScript<CGrabScript>()->SetStartPos(Transform()->GetWorldPos());
	_pGrab->Transform()->SetRelativePos(Transform()->GetWorldPos());
	_pGrab->GetScript<CGrabScript>()->SetArriPos(vCursorPos);
	_pGrab->GetScript<CGrabScript>()->SetNoneGrab(true);


	// 현재각도
	float fCurAngle = atan2f(fy, fx);

	float fDE = XMConvertToDegrees(fCurAngle);
	m_fNotShootDE = fCurAngle;

	PlayerStateSet(fDE);

	
	fDE -= 90;

	_pGrab->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y,
		XMConvertToRadians(fDE)));

	CreateGrabTail(Transform()->GetWorldPos(), vCursorPos);

	_pGrab->GetScript<CGrabScript>()->SetGrabState(GRAB_STATE::FLYING);
}


void CArmScript::GrabAction(CGameObject* _pGrab)
{
	SEARCH_PRIORITY CurPri = m_SearchObj->GetScript<CSearchBarScript>()->GetCurPriority();
	





	switch (CurPri)
	{
	case SEARCH_PRIORITY::ENEMY:
	{
		m_CurEnemyObj = m_SearchObj->GetScript<CSearchBarScript>()->GetSearchObj();
		m_vDestPos = m_SearchObj->GetScript<CSearchBarScript>()->GetSearchObj()->Transform()->GetWorldPos();
		// 시간 느려지며 잔상남기며 순간이동
		// 이후 
		m_vBeforeHoldingPos = GetOwner()->GetParent()->Transform()->GetRelativePos();
		CreateGrabTail(Transform()->GetWorldPos(), m_vDestPos);

		float fx = m_vDestPos.x - Transform()->GetWorldPos().x;
		float fy = m_vDestPos.y - Transform()->GetWorldPos().y;

		float fCurAngle = atan2f(fy, fx);

		float fDE = XMConvertToDegrees(fCurAngle);
		m_fNotShootDE = fCurAngle;

		PlayerStateSet(fDE);

		GetOwner()->GetParent()->Transform()->SetRelativePos(m_vDestPos);

		m_bHolding = true;
	}
	break;
	case SEARCH_PRIORITY::SWINGHOOK:
	{
		// 시간 느려지며 잔상남기며 순간이동
		// 이후 swinghook을 이용한 로프액션
	}
	break;
	case SEARCH_PRIORITY::CARGO:
	{
		// 그랩 발사후 해당 오브젝트 좌표에 그랩 고정
		// -> 로프 액션
		ShootGrab(_pGrab);
	}
	break;
	case SEARCH_PRIORITY::ENABLED:
	{
		// 그랩 발사후 해당 오브젝트 좌표에 그랩 고정
		// -> 로프 액션
		ShootGrab(_pGrab);
	}
	break;
	case SEARCH_PRIORITY::NOTHING:
	{
		// 그랩 발사후 거리잰후 최대거리되면 그랩 회수
		ShootGrabAndReturn(_pGrab);
	}
	break;
	default:
		break;
	}
}

void CArmScript::PlayerStateSet(float _fDegree)
{
	if (_fDegree > -45.f && _fDegree <= 45.f)
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_FRONT);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_FRONT;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_FRONT);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_FRONT;
		}
	}
	else if (_fDegree > 45.f && _fDegree <= 90.f)
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_UP);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_UP;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_UP);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_UP;
		}
	}
	else if (_fDegree > 90.f && _fDegree <= 135.f)
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_UP);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_UP;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_UP);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_UP;
		}
	}
	else if ((_fDegree > 135.f && _fDegree <= 180.f) || (_fDegree < -135.f && _fDegree >= -180.f))
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_FRONT);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_FRONT;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_FRONT);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_FRONT;
		}
	}
	else if (_fDegree < -90.f && _fDegree >= -135.f)
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_DOWN);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_DOWN;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_DOWN);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(false);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_DOWN;
		}
	}
	else if (_fDegree < -45.f && _fDegree >= -90.f)
	{
		if (GetOwner()->GetParent()->Gravity()->IsOnGround())
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_DOWN);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_DOWN;
		}
		else
		{
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetPlayerState(PLAYER_STATE::SHOT_AIR_DOWN);
			GetOwner()->GetParent()->GetScript<CPlayerScript>()->SetCurLP(true);
			m_CurState = AFTERIMAGE_TYPE::SHOT_AIR_DOWN;
		}
	}
}





void CArmScript::ChangeARMState(PLAYER_STATE _curPlayerState, PLAYER_STATE _prevPlayerState, bool _bLp)
{
	if (_curPlayerState == _prevPlayerState)
		return;

	switch (_curPlayerState)
	{
	case PLAYER_STATE::IDLE:
		if (_prevPlayerState == PLAYER_STATE::RUN)
		{
			if (_bLp)
				Animator2D()->PlayToPlay(L"ARM_RUNSTOP_LP", L"ARM_IDLE_LP");
			else if (!_bLp)
				Animator2D()->PlayToPlay(L"ARM_RUNSTOP_RP", L"ARM_IDLE_RP");
		}
		else if (_prevPlayerState == PLAYER_STATE::FALLING)
		{
			if (_bLp)
				Animator2D()->PlayToPlay(L"ARM_LANDING_LP", L"ARM_IDLE_LP");
			else if (!_bLp)
				Animator2D()->PlayToPlay(L"ARM_LANDING_RP", L"ARM_IDLE_RP");
		}
		else if (_bLp)
			Animator2D()->Play(L"ARM_IDLE_LP");
		else if (!_bLp)
			Animator2D()->Play(L"ARM_IDLE_RP");
		break;
	case PLAYER_STATE::JUMPING:
		if (_bLp)
			Animator2D()->Play(L"ARM_JUMPING_LP");
		else
			Animator2D()->Play(L"ARM_JUMPING_RP");
		break;
	case PLAYER_STATE::DAMAGE:
		if (_bLp)
			Animator2D()->Play(L"ARM_DAMAGE_LP");
		else
			Animator2D()->Play(L"ARM_DAMAGE_RP");
		break;
	case PLAYER_STATE::DASH:
		break;
	case PLAYER_STATE::SHOT_DOWN:
	case PLAYER_STATE::SHOT_FRONT:
	case PLAYER_STATE::SHOT_UP:
	case PLAYER_STATE::SHOT_AIR_DOWN:
	case PLAYER_STATE::SHOT_AIR_FRONT:
	case PLAYER_STATE::SHOT_AIR_UP:
		if (_bLp)
			Animator2D()->Play(L"ARM_SHOOT_LP", false);
		else if (!_bLp)
			Animator2D()->Play(L"ARM_SHOOT_RP", false);
		break;
	case PLAYER_STATE::DASHENDGROUND:
		break;
	case PLAYER_STATE::FALLING:
		if (_prevPlayerState != PLAYER_STATE::FALLING)
		{
			if (_bLp)
				Animator2D()->PlayToPlay(L"ARM_FALLSTART_LP", L"ARM_FALLING_LP");
			else 
				Animator2D()->PlayToPlay(L"ARM_FALLSTART_RP", L"ARM_FALLING_RP");
		}
		else if (_bLp)
			Animator2D()->Play(L"ARM_FALLING_LP");
		else if (!_bLp)
			Animator2D()->Play(L"ARM_FALLING_RP");
		break;
	case PLAYER_STATE::ROLLING:
		break;
	case PLAYER_STATE::RUN:
		if (_prevPlayerState == PLAYER_STATE::IDLE)
		{
			if (_bLp)
				Animator2D()->PlayToPlay(L"ARM_RUNSTART_LP", L"ARM_RUNNING_LP");
			else
				Animator2D()->PlayToPlay(L"ARM_RUNSTART_RP", L"ARM_RUNNING_RP");
		}
		else if (_prevPlayerState == PLAYER_STATE::FALLING)
		{
			
			if(_bLp)
				Animator2D()->PlayToPlay(L"ARM_LAND2RUN_LP", L"ARM_RUNNING_LP");
			else
				Animator2D()->PlayToPlay(L"ARM_LAND2RUN_RP", L"ARM_RUNNING_RP");
		}
		else if (_bLp)
			Animator2D()->Play(L"ARM_RUNNING_LP");
		else if (!_bLp)
			Animator2D()->Play(L"ARM_RUNNING_RP");
		break;
	case PLAYER_STATE::SWING:
		if (_bLp)
			Animator2D()->Play(L"ARM_GRABBED_LP");
		else if (!_bLp)
			Animator2D()->Play(L"ARM_GRABBED_RP");
		break;
	case PLAYER_STATE::SWINGJUMP:
		if (_bLp)
			Animator2D()->PlayToPlay(L"ARM_SWINGJUMP_LP", L"ARM_FALLING_LP");
		else
			Animator2D()->PlayToPlay(L"ARM_SWINGJUMP_RP", L"ARM_FALLING_RP");
		break;
	case PLAYER_STATE::SWINGJUMP_ROLLING:
		if (_bLp)
			Animator2D()->PlayToPlay(L"ARM_SWINGJUMPUP_LP", L"ARM_ROLLING_LP");
		else
			Animator2D()->PlayToPlay(L"ARM_SWINGJUMPUP_RP", L"ARM_ROLLING_RP");
		break;
	case PLAYER_STATE::ROPE_SLIDE:
		break;
	case PLAYER_STATE::CLIMB_UP:
		if (_bLp)
		{
			Animator2D()->Play(L"ARM_WALLCLIMB_UP_LP");
		}
		else
		{
			Animator2D()->Play(L"ARM_WALLCLIMB_UP_RP");
		}
		break;
	case PLAYER_STATE::CLIMB:
		if (_bLp)
		{
			Animator2D()->Play(L"ARM_WALLCLIMB_IDLE_LP");
		}
		else 
		{
			Animator2D()->Play(L"ARM_WALLCLIMB_IDLE_RP");
		}
		break;
	case PLAYER_STATE::SLIDE:
		if (_bLp)
			Animator2D()->PlayToPlay(L"ARM_WALLSLIDESTART_LP", L"ARM_WALLSLIDING_LP");
		else 
			Animator2D()->PlayToPlay(L"ARM_WALLSLIDESTART_RP", L"ARM_WALLSLIDING_RP");
		break;
	case PLAYER_STATE::DEATH:
		Animator2D()->Play(L"NONE");
	default:
		break;
	}
}


void CArmScript::SaveToFile(FILE* _File)
{
}

void CArmScript::LoadFromFile(FILE* _File)
{
}

void CArmScript::CreateGrabTail(Vec3 _vStartPos, Vec3 _vDestPos)
{
	CGameObject* pObj = new CGameObject;
	pObj->SetName(L"GrabTail");

	pObj->AddComponent(new CTransform);
	pObj->AddComponent(new CMeshRender);
	pObj->AddComponent(new CAnimator2D);
	pObj->AddComponent(new CGrabTailScript);

	_vDestPos.z = _vStartPos.z;

	Vec3 vDir = _vDestPos - _vStartPos;



	float fx = _vDestPos.x - _vStartPos.x;
	float fy = _vDestPos.y - _vStartPos.y;

	float fCurAngle = atan2f(fy, fx);
	float fDE = XMConvertToDegrees(fCurAngle);
	//fDE -= 90;

	pObj->Transform()->SetRelativePos(Vec3(_vDestPos.x - cosf(fCurAngle) * (vDir.Length() - 50.f), _vDestPos.y - sinf(fCurAngle) * (vDir.Length() - 50.f), _vDestPos.z));
	pObj->Transform()->SetRelativeScale(Vec3(vDir.Length() * 1.5f, 350.f, 1.f));

	pObj->Transform()->SetRelativeRotation(Vec3(Transform()->GetRelativePos().x, Transform()->GetRelativePos().y,
		XMConvertToRadians(fDE)));

	pObj->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	pObj->MeshRender()->SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"Std2DMtrl"));

	GamePlayStatic::SpawnGameObject(pObj, 1);
}
