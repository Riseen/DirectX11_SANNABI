#include "pch.h"
#include "CEnemyScript.h"

CEnemyScript::CEnemyScript()
	: CScript(ENEMYSCRIPT)
{
}

CEnemyScript::CEnemyScript(UINT _ScriptType)
	: CScript(_ScriptType)
{
}

CEnemyScript::~CEnemyScript()
{
}

void CEnemyScript::SetCurEnemyState(ENEMY_STATE _State)
{
}

void CEnemyScript::Holding()
{
}

void CEnemyScript::Dead()
{

}

void CEnemyScript::Detected()
{
}

void CEnemyScript::begin()
{
}

void CEnemyScript::tick()
{
}


void CEnemyScript::SaveToFile(FILE* _File)
{
}

void CEnemyScript::LoadFromFile(FILE* _File)
{
}




