#pragma once
#include "singleton.h"

class CLevel;

typedef CLevel* (*LEVEL_LOAD)(const wstring&);

class CLevelMgr :
    public CSingleton<CLevelMgr>
{
    SINGLE(CLevelMgr);
private:
    CLevel*         m_CurLevel;
    LEVEL_TYPE      m_CurLevelType;

public:
    static LEVEL_LOAD levelLoad;

public:
    CLevel* LoadLevel(const wstring& _strFilePath);

public:
    void init();        
    void tick();  

public:
    void ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextStartState);
    void ChangeLevelState(LEVEL_STATE _State);
    void SetLevelType(LEVEL_TYPE _state) { m_CurLevelType = _state; }
    LEVEL_TYPE GetCurLevelType() { return m_CurLevelType; }

private:
    void ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState);


public:
    CLevel* GetCurrentLevel() { return m_CurLevel; }


    friend class CTaskMgr;
};

