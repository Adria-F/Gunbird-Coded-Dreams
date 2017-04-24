#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	update_status Update();

private:

	int font_score;

};

#endif // !__MODULE_UI_H__
