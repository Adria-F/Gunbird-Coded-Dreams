#ifndef __MODULE_SELECTION_H__
#define __MODULE_SELECTION_H__

#include "Module.h"

class ModuleSelection : public Module
{
public:

	ModuleSelection();
	~ModuleSelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	bool fading;
};

#endif // !__MODULE_SELECTION_H__
