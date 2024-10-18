#pragma once
#include "singleton.h"

class CMessengerMgr :
	public CSingleton<CMessengerMgr>
{
	SINGLE(CMessengerMgr);

public:
	void init();
    void render();
};

