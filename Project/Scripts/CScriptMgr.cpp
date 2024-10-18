#include "pch.h"
#include "CScriptMgr.h"

#include "CAfterImageManagerScript.h"
#include "CAfterImageScript.h"
#include "CAimmingRayScript.h"
#include "CArmScript.h"
#include "CArmToGrabLineScript.h"
#include "CBackgroundScript.h"
#include "CBombCargoScript.h"
#include "CBombScript.h"
#include "CBossATScript.h"
#include "CBossP2AlertScript.h"
#include "CBossRoomSysMgrScript.h"
#include "CBossScript.h"
#include "CBossWaveScript.h"
#include "CBrokenCargoScript.h"
#include "CBulletScript.h"
#include "CButtonScript.h"
#include "CCameraScript.h"
#include "CCapeScript.h"
#include "CChainScript.h"
#include "CClimbBarScript.h"
#include "CCursorScript.h"
#include "CDeathColScript.h"
#include "CDefendScript.h"
#include "CDestUIScript.h"
#include "CDropRedCargoColScript.h"
#include "CDropRedCargoScript.h"
#include "CEnemyScript.h"
#include "CEventColScript.h"
#include "CFadeInOutScript.h"
#include "CFinalCraneHookScript.h"
#include "CGamePlayBGScript.h"
#include "CGameSystemMgrScript.h"
#include "CGrabLineScript.h"
#include "CGrabScript.h"
#include "CGrabTailScript.h"
#include "CHoldAimScript.h"
#include "CHPUIScript.h"
#include "CLayerMgrScript.h"
#include "CLevelChangeEventColScript.h"
#include "CMainFlashScript.h"
#include "CMainLightOnScript.h"
#include "CMainLogoUI.h"
#include "CMainParticleScript.h"
#include "CMainSmokeScript.h"
#include "CMainUIScript.h"
#include "CMapObjScript.h"
#include "CMenuUIScript.h"
#include "CMessengerScript.h"
#include "CMissileScript.h"
#include "CMonsterScript.h"
#include "CPlayerEffectScript.h"
#include "CPlayerScript.h"
#include "CQTEScript.h"
#include "CRedCargoScript.h"
#include "CSearchBarScript.h"
#include "CSimpleWallScript.h"
#include "CTileColScript.h"
#include "CTrooperScript.h"
#include "CTurretBodyScript.h"
#include "CTurretGunScript.h"
#include "CTurretLaserScript.h"

void CScriptMgr::GetScriptInfo(vector<wstring>& _vec)
{
	_vec.push_back(L"CAfterImageManagerScript");
	_vec.push_back(L"CAfterImageScript");
	_vec.push_back(L"CAimmingRayScript");
	_vec.push_back(L"CArmScript");
	_vec.push_back(L"CArmToGrabLineScript");
	_vec.push_back(L"CBackgroundScript");
	_vec.push_back(L"CBombCargoScript");
	_vec.push_back(L"CBombScript");
	_vec.push_back(L"CBossATScript");
	_vec.push_back(L"CBossP2AlertScript");
	_vec.push_back(L"CBossRoomSysMgrScript");
	_vec.push_back(L"CBossScript");
	_vec.push_back(L"CBossWaveScript");
	_vec.push_back(L"CBrokenCargoScript");
	_vec.push_back(L"CBulletScript");
	_vec.push_back(L"CButtonScript");
	_vec.push_back(L"CCameraScript");
	_vec.push_back(L"CCapeScript");
	_vec.push_back(L"CChainScript");
	_vec.push_back(L"CClimbBarScript");
	_vec.push_back(L"CCursorScript");
	_vec.push_back(L"CDeathColScript");
	_vec.push_back(L"CDefendScript");
	_vec.push_back(L"CDestUIScript");
	_vec.push_back(L"CDropRedCargoColScript");
	_vec.push_back(L"CDropRedCargoScript");
	_vec.push_back(L"CEnemyScript");
	_vec.push_back(L"CEventColScript");
	_vec.push_back(L"CFadeInOutScript");
	_vec.push_back(L"CFinalCraneHookScript");
	_vec.push_back(L"CGamePlayBGScript");
	_vec.push_back(L"CGameSystemMgrScript");
	_vec.push_back(L"CGrabLineScript");
	_vec.push_back(L"CGrabScript");
	_vec.push_back(L"CGrabTailScript");
	_vec.push_back(L"CHoldAimScript");
	_vec.push_back(L"CHPUIScript");
	_vec.push_back(L"CLayerMgrScript");
	_vec.push_back(L"CLevelChangeEventColScript");
	_vec.push_back(L"CMainFlashScript");
	_vec.push_back(L"CMainLightOnScript");
	_vec.push_back(L"CMainLogoUI");
	_vec.push_back(L"CMainParticleScript");
	_vec.push_back(L"CMainSmokeScript");
	_vec.push_back(L"CMainUIScript");
	_vec.push_back(L"CMapObjScript");
	_vec.push_back(L"CMenuUIScript");
	_vec.push_back(L"CMessengerScript");
	_vec.push_back(L"CMissileScript");
	_vec.push_back(L"CMonsterScript");
	_vec.push_back(L"CPlayerEffectScript");
	_vec.push_back(L"CPlayerScript");
	_vec.push_back(L"CQTEScript");
	_vec.push_back(L"CRedCargoScript");
	_vec.push_back(L"CSearchBarScript");
	_vec.push_back(L"CSimpleWallScript");
	_vec.push_back(L"CTileColScript");
	_vec.push_back(L"CTrooperScript");
	_vec.push_back(L"CTurretBodyScript");
	_vec.push_back(L"CTurretGunScript");
	_vec.push_back(L"CTurretLaserScript");
}

CScript * CScriptMgr::GetScript(const wstring& _strScriptName)
{
	if (L"CAfterImageManagerScript" == _strScriptName)
		return new CAfterImageManagerScript;
	if (L"CAfterImageScript" == _strScriptName)
		return new CAfterImageScript;
	if (L"CAimmingRayScript" == _strScriptName)
		return new CAimmingRayScript;
	if (L"CArmScript" == _strScriptName)
		return new CArmScript;
	if (L"CArmToGrabLineScript" == _strScriptName)
		return new CArmToGrabLineScript;
	if (L"CBackgroundScript" == _strScriptName)
		return new CBackgroundScript;
	if (L"CBombCargoScript" == _strScriptName)
		return new CBombCargoScript;
	if (L"CBombScript" == _strScriptName)
		return new CBombScript;
	if (L"CBossATScript" == _strScriptName)
		return new CBossATScript;
	if (L"CBossP2AlertScript" == _strScriptName)
		return new CBossP2AlertScript;
	if (L"CBossRoomSysMgrScript" == _strScriptName)
		return new CBossRoomSysMgrScript;
	if (L"CBossScript" == _strScriptName)
		return new CBossScript;
	if (L"CBossWaveScript" == _strScriptName)
		return new CBossWaveScript;
	if (L"CBrokenCargoScript" == _strScriptName)
		return new CBrokenCargoScript;
	if (L"CBulletScript" == _strScriptName)
		return new CBulletScript;
	if (L"CButtonScript" == _strScriptName)
		return new CButtonScript;
	if (L"CCameraScript" == _strScriptName)
		return new CCameraScript;
	if (L"CCapeScript" == _strScriptName)
		return new CCapeScript;
	if (L"CChainScript" == _strScriptName)
		return new CChainScript;
	if (L"CClimbBarScript" == _strScriptName)
		return new CClimbBarScript;
	if (L"CCursorScript" == _strScriptName)
		return new CCursorScript;
	if (L"CDeathColScript" == _strScriptName)
		return new CDeathColScript;
	if (L"CDefendScript" == _strScriptName)
		return new CDefendScript;
	if (L"CDestUIScript" == _strScriptName)
		return new CDestUIScript;
	if (L"CDropRedCargoColScript" == _strScriptName)
		return new CDropRedCargoColScript;
	if (L"CDropRedCargoScript" == _strScriptName)
		return new CDropRedCargoScript;
	if (L"CEnemyScript" == _strScriptName)
		return new CEnemyScript;
	if (L"CEventColScript" == _strScriptName)
		return new CEventColScript;
	if (L"CFadeInOutScript" == _strScriptName)
		return new CFadeInOutScript;
	if (L"CFinalCraneHookScript" == _strScriptName)
		return new CFinalCraneHookScript;
	if (L"CGamePlayBGScript" == _strScriptName)
		return new CGamePlayBGScript;
	if (L"CGameSystemMgrScript" == _strScriptName)
		return new CGameSystemMgrScript;
	if (L"CGrabLineScript" == _strScriptName)
		return new CGrabLineScript;
	if (L"CGrabScript" == _strScriptName)
		return new CGrabScript;
	if (L"CGrabTailScript" == _strScriptName)
		return new CGrabTailScript;
	if (L"CHoldAimScript" == _strScriptName)
		return new CHoldAimScript;
	if (L"CHPUIScript" == _strScriptName)
		return new CHPUIScript;
	if (L"CLayerMgrScript" == _strScriptName)
		return new CLayerMgrScript;
	if (L"CLevelChangeEventColScript" == _strScriptName)
		return new CLevelChangeEventColScript;
	if (L"CMainFlashScript" == _strScriptName)
		return new CMainFlashScript;
	if (L"CMainLightOnScript" == _strScriptName)
		return new CMainLightOnScript;
	if (L"CMainLogoUI" == _strScriptName)
		return new CMainLogoUI;
	if (L"CMainParticleScript" == _strScriptName)
		return new CMainParticleScript;
	if (L"CMainSmokeScript" == _strScriptName)
		return new CMainSmokeScript;
	if (L"CMainUIScript" == _strScriptName)
		return new CMainUIScript;
	if (L"CMapObjScript" == _strScriptName)
		return new CMapObjScript;
	if (L"CMenuUIScript" == _strScriptName)
		return new CMenuUIScript;
	if (L"CMessengerScript" == _strScriptName)
		return new CMessengerScript;
	if (L"CMissileScript" == _strScriptName)
		return new CMissileScript;
	if (L"CMonsterScript" == _strScriptName)
		return new CMonsterScript;
	if (L"CPlayerEffectScript" == _strScriptName)
		return new CPlayerEffectScript;
	if (L"CPlayerScript" == _strScriptName)
		return new CPlayerScript;
	if (L"CQTEScript" == _strScriptName)
		return new CQTEScript;
	if (L"CRedCargoScript" == _strScriptName)
		return new CRedCargoScript;
	if (L"CSearchBarScript" == _strScriptName)
		return new CSearchBarScript;
	if (L"CSimpleWallScript" == _strScriptName)
		return new CSimpleWallScript;
	if (L"CTileColScript" == _strScriptName)
		return new CTileColScript;
	if (L"CTrooperScript" == _strScriptName)
		return new CTrooperScript;
	if (L"CTurretBodyScript" == _strScriptName)
		return new CTurretBodyScript;
	if (L"CTurretGunScript" == _strScriptName)
		return new CTurretGunScript;
	if (L"CTurretLaserScript" == _strScriptName)
		return new CTurretLaserScript;
	return nullptr;
}

CScript * CScriptMgr::GetScript(UINT _iScriptType)
{
	switch (_iScriptType)
	{
	case (UINT)SCRIPT_TYPE::AFTERIMAGEMANAGERSCRIPT:
		return new CAfterImageManagerScript;
		break;
	case (UINT)SCRIPT_TYPE::AFTERIMAGESCRIPT:
		return new CAfterImageScript;
		break;
	case (UINT)SCRIPT_TYPE::AIMMINGRAYSCRIPT:
		return new CAimmingRayScript;
		break;
	case (UINT)SCRIPT_TYPE::ARMSCRIPT:
		return new CArmScript;
		break;
	case (UINT)SCRIPT_TYPE::ARMTOGRABLINESCRIPT:
		return new CArmToGrabLineScript;
		break;
	case (UINT)SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return new CBackgroundScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBCARGOSCRIPT:
		return new CBombCargoScript;
		break;
	case (UINT)SCRIPT_TYPE::BOMBSCRIPT:
		return new CBombScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSATSCRIPT:
		return new CBossATScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSP2ALERTSCRIPT:
		return new CBossP2AlertScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSROOMSYSMGRSCRIPT:
		return new CBossRoomSysMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSSCRIPT:
		return new CBossScript;
		break;
	case (UINT)SCRIPT_TYPE::BOSSWAVESCRIPT:
		return new CBossWaveScript;
		break;
	case (UINT)SCRIPT_TYPE::BROKENCARGOSCRIPT:
		return new CBrokenCargoScript;
		break;
	case (UINT)SCRIPT_TYPE::BULLETSCRIPT:
		return new CBulletScript;
		break;
	case (UINT)SCRIPT_TYPE::BUTTONSCRIPT:
		return new CButtonScript;
		break;
	case (UINT)SCRIPT_TYPE::CAMERASCRIPT:
		return new CCameraScript;
		break;
	case (UINT)SCRIPT_TYPE::CAPESCRIPT:
		return new CCapeScript;
		break;
	case (UINT)SCRIPT_TYPE::CHAINSCRIPT:
		return new CChainScript;
		break;
	case (UINT)SCRIPT_TYPE::CLIMBBARSCRIPT:
		return new CClimbBarScript;
		break;
	case (UINT)SCRIPT_TYPE::CURSORSCRIPT:
		return new CCursorScript;
		break;
	case (UINT)SCRIPT_TYPE::DEATHCOLSCRIPT:
		return new CDeathColScript;
		break;
	case (UINT)SCRIPT_TYPE::DEFENDSCRIPT:
		return new CDefendScript;
		break;
	case (UINT)SCRIPT_TYPE::DESTUISCRIPT:
		return new CDestUIScript;
		break;
	case (UINT)SCRIPT_TYPE::DROPREDCARGOCOLSCRIPT:
		return new CDropRedCargoColScript;
		break;
	case (UINT)SCRIPT_TYPE::DROPREDCARGOSCRIPT:
		return new CDropRedCargoScript;
		break;
	case (UINT)SCRIPT_TYPE::ENEMYSCRIPT:
		return new CEnemyScript;
		break;
	case (UINT)SCRIPT_TYPE::EVENTCOLSCRIPT:
		return new CEventColScript;
		break;
	case (UINT)SCRIPT_TYPE::FADEINOUTSCRIPT:
		return new CFadeInOutScript;
		break;
	case (UINT)SCRIPT_TYPE::FINALCRANEHOOKSCRIPT:
		return new CFinalCraneHookScript;
		break;
	case (UINT)SCRIPT_TYPE::GAMEPLAYBGSCRIPT:
		return new CGamePlayBGScript;
		break;
	case (UINT)SCRIPT_TYPE::GAMESYSTEMMGRSCRIPT:
		return new CGameSystemMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::GRABLINESCRIPT:
		return new CGrabLineScript;
		break;
	case (UINT)SCRIPT_TYPE::GRABSCRIPT:
		return new CGrabScript;
		break;
	case (UINT)SCRIPT_TYPE::GRABTAILSCRIPT:
		return new CGrabTailScript;
		break;
	case (UINT)SCRIPT_TYPE::HOLDAIMSCRIPT:
		return new CHoldAimScript;
		break;
	case (UINT)SCRIPT_TYPE::HPUISCRIPT:
		return new CHPUIScript;
		break;
	case (UINT)SCRIPT_TYPE::LAYERMGRSCRIPT:
		return new CLayerMgrScript;
		break;
	case (UINT)SCRIPT_TYPE::LEVELCHANGEEVENTCOLSCRIPT:
		return new CLevelChangeEventColScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINFLASHSCRIPT:
		return new CMainFlashScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINLIGHTONSCRIPT:
		return new CMainLightOnScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINLOGOUI:
		return new CMainLogoUI;
		break;
	case (UINT)SCRIPT_TYPE::MAINPARTICLESCRIPT:
		return new CMainParticleScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINSMOKESCRIPT:
		return new CMainSmokeScript;
		break;
	case (UINT)SCRIPT_TYPE::MAINUISCRIPT:
		return new CMainUIScript;
		break;
	case (UINT)SCRIPT_TYPE::MAPOBJSCRIPT:
		return new CMapObjScript;
		break;
	case (UINT)SCRIPT_TYPE::MENUUISCRIPT:
		return new CMenuUIScript;
		break;
	case (UINT)SCRIPT_TYPE::MESSENGERSCRIPT:
		return new CMessengerScript;
		break;
	case (UINT)SCRIPT_TYPE::MISSILESCRIPT:
		return new CMissileScript;
		break;
	case (UINT)SCRIPT_TYPE::MONSTERSCRIPT:
		return new CMonsterScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYEREFFECTSCRIPT:
		return new CPlayerEffectScript;
		break;
	case (UINT)SCRIPT_TYPE::PLAYERSCRIPT:
		return new CPlayerScript;
		break;
	case (UINT)SCRIPT_TYPE::QTESCRIPT:
		return new CQTEScript;
		break;
	case (UINT)SCRIPT_TYPE::REDCARGOSCRIPT:
		return new CRedCargoScript;
		break;
	case (UINT)SCRIPT_TYPE::SEARCHBARSCRIPT:
		return new CSearchBarScript;
		break;
	case (UINT)SCRIPT_TYPE::SIMPLEWALLSCRIPT:
		return new CSimpleWallScript;
		break;
	case (UINT)SCRIPT_TYPE::TILECOLSCRIPT:
		return new CTileColScript;
		break;
	case (UINT)SCRIPT_TYPE::TROOPERSCRIPT:
		return new CTrooperScript;
		break;
	case (UINT)SCRIPT_TYPE::TURRETBODYSCRIPT:
		return new CTurretBodyScript;
		break;
	case (UINT)SCRIPT_TYPE::TURRETGUNSCRIPT:
		return new CTurretGunScript;
		break;
	case (UINT)SCRIPT_TYPE::TURRETLASERSCRIPT:
		return new CTurretLaserScript;
		break;
	}
	return nullptr;
}

const wchar_t * CScriptMgr::GetScriptName(CScript * _pScript)
{
	switch ((SCRIPT_TYPE)_pScript->GetScriptType())
	{
	case SCRIPT_TYPE::AFTERIMAGEMANAGERSCRIPT:
		return L"CAfterImageManagerScript";
		break;

	case SCRIPT_TYPE::AFTERIMAGESCRIPT:
		return L"CAfterImageScript";
		break;

	case SCRIPT_TYPE::AIMMINGRAYSCRIPT:
		return L"CAimmingRayScript";
		break;

	case SCRIPT_TYPE::ARMSCRIPT:
		return L"CArmScript";
		break;

	case SCRIPT_TYPE::ARMTOGRABLINESCRIPT:
		return L"CArmToGrabLineScript";
		break;

	case SCRIPT_TYPE::BACKGROUNDSCRIPT:
		return L"CBackgroundScript";
		break;

	case SCRIPT_TYPE::BOMBCARGOSCRIPT:
		return L"CBombCargoScript";
		break;

	case SCRIPT_TYPE::BOMBSCRIPT:
		return L"CBombScript";
		break;

	case SCRIPT_TYPE::BOSSATSCRIPT:
		return L"CBossATScript";
		break;

	case SCRIPT_TYPE::BOSSP2ALERTSCRIPT:
		return L"CBossP2AlertScript";
		break;

	case SCRIPT_TYPE::BOSSROOMSYSMGRSCRIPT:
		return L"CBossRoomSysMgrScript";
		break;

	case SCRIPT_TYPE::BOSSSCRIPT:
		return L"CBossScript";
		break;

	case SCRIPT_TYPE::BOSSWAVESCRIPT:
		return L"CBossWaveScript";
		break;

	case SCRIPT_TYPE::BROKENCARGOSCRIPT:
		return L"CBrokenCargoScript";
		break;

	case SCRIPT_TYPE::BULLETSCRIPT:
		return L"CBulletScript";
		break;

	case SCRIPT_TYPE::BUTTONSCRIPT:
		return L"CButtonScript";
		break;

	case SCRIPT_TYPE::CAMERASCRIPT:
		return L"CCameraScript";
		break;

	case SCRIPT_TYPE::CAPESCRIPT:
		return L"CCapeScript";
		break;

	case SCRIPT_TYPE::CHAINSCRIPT:
		return L"CChainScript";
		break;

	case SCRIPT_TYPE::CLIMBBARSCRIPT:
		return L"CClimbBarScript";
		break;

	case SCRIPT_TYPE::CURSORSCRIPT:
		return L"CCursorScript";
		break;

	case SCRIPT_TYPE::DEATHCOLSCRIPT:
		return L"CDeathColScript";
		break;

	case SCRIPT_TYPE::DEFENDSCRIPT:
		return L"CDefendScript";
		break;

	case SCRIPT_TYPE::DESTUISCRIPT:
		return L"CDestUIScript";
		break;

	case SCRIPT_TYPE::DROPREDCARGOCOLSCRIPT:
		return L"CDropRedCargoColScript";
		break;

	case SCRIPT_TYPE::DROPREDCARGOSCRIPT:
		return L"CDropRedCargoScript";
		break;

	case SCRIPT_TYPE::ENEMYSCRIPT:
		return L"CEnemyScript";
		break;

	case SCRIPT_TYPE::EVENTCOLSCRIPT:
		return L"CEventColScript";
		break;

	case SCRIPT_TYPE::FADEINOUTSCRIPT:
		return L"CFadeInOutScript";
		break;

	case SCRIPT_TYPE::FINALCRANEHOOKSCRIPT:
		return L"CFinalCraneHookScript";
		break;

	case SCRIPT_TYPE::GAMEPLAYBGSCRIPT:
		return L"CGamePlayBGScript";
		break;

	case SCRIPT_TYPE::GAMESYSTEMMGRSCRIPT:
		return L"CGameSystemMgrScript";
		break;

	case SCRIPT_TYPE::GRABLINESCRIPT:
		return L"CGrabLineScript";
		break;

	case SCRIPT_TYPE::GRABSCRIPT:
		return L"CGrabScript";
		break;

	case SCRIPT_TYPE::GRABTAILSCRIPT:
		return L"CGrabTailScript";
		break;

	case SCRIPT_TYPE::HOLDAIMSCRIPT:
		return L"CHoldAimScript";
		break;

	case SCRIPT_TYPE::HPUISCRIPT:
		return L"CHPUIScript";
		break;

	case SCRIPT_TYPE::LAYERMGRSCRIPT:
		return L"CLayerMgrScript";
		break;

	case SCRIPT_TYPE::LEVELCHANGEEVENTCOLSCRIPT:
		return L"CLevelChangeEventColScript";
		break;

	case SCRIPT_TYPE::MAINFLASHSCRIPT:
		return L"CMainFlashScript";
		break;

	case SCRIPT_TYPE::MAINLIGHTONSCRIPT:
		return L"CMainLightOnScript";
		break;

	case SCRIPT_TYPE::MAINLOGOUI:
		return L"CMainLogoUI";
		break;

	case SCRIPT_TYPE::MAINPARTICLESCRIPT:
		return L"CMainParticleScript";
		break;

	case SCRIPT_TYPE::MAINSMOKESCRIPT:
		return L"CMainSmokeScript";
		break;

	case SCRIPT_TYPE::MAINUISCRIPT:
		return L"CMainUIScript";
		break;

	case SCRIPT_TYPE::MAPOBJSCRIPT:
		return L"CMapObjScript";
		break;

	case SCRIPT_TYPE::MENUUISCRIPT:
		return L"CMenuUIScript";
		break;

	case SCRIPT_TYPE::MESSENGERSCRIPT:
		return L"CMessengerScript";
		break;

	case SCRIPT_TYPE::MISSILESCRIPT:
		return L"CMissileScript";
		break;

	case SCRIPT_TYPE::MONSTERSCRIPT:
		return L"CMonsterScript";
		break;

	case SCRIPT_TYPE::PLAYEREFFECTSCRIPT:
		return L"CPlayerEffectScript";
		break;

	case SCRIPT_TYPE::PLAYERSCRIPT:
		return L"CPlayerScript";
		break;

	case SCRIPT_TYPE::QTESCRIPT:
		return L"CQTEScript";
		break;

	case SCRIPT_TYPE::REDCARGOSCRIPT:
		return L"CRedCargoScript";
		break;

	case SCRIPT_TYPE::SEARCHBARSCRIPT:
		return L"CSearchBarScript";
		break;

	case SCRIPT_TYPE::SIMPLEWALLSCRIPT:
		return L"CSimpleWallScript";
		break;

	case SCRIPT_TYPE::TILECOLSCRIPT:
		return L"CTileColScript";
		break;

	case SCRIPT_TYPE::TROOPERSCRIPT:
		return L"CTrooperScript";
		break;

	case SCRIPT_TYPE::TURRETBODYSCRIPT:
		return L"CTurretBodyScript";
		break;

	case SCRIPT_TYPE::TURRETGUNSCRIPT:
		return L"CTurretGunScript";
		break;

	case SCRIPT_TYPE::TURRETLASERSCRIPT:
		return L"CTurretLaserScript";
		break;

	}
	return nullptr;
}