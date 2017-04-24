#ifndef __MODULE_UI_H__
#define __MODULE_UI_H__

#include "Module.h"

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();

private:

	char score_text[10];
	int font_score = -1;

};

#endif // !__MODULE_UI_H__
