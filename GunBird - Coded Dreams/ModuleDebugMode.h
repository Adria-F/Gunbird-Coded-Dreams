#ifndef __MODULEDEBUGMODE_H__
#define __MODULEDEBUGMODE_H__

#include "Module.h"
#include "Globals.h"

class ModuleDebugMode : public Module
{
public:
	ModuleDebugMode();
	~ModuleDebugMode();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool debugging = false;
};

#endif // __MODULEDEBUGMODE_H__