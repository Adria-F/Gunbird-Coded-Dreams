#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 13

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneCastle;
class ModuleSceneMine;
class ModulePlayer;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleWelcomeTitle;
class ModuleHighscores;
class ModuleSelection;
class ModuleDebugMode;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneCastle* scene_castle;
	ModuleSceneMine* scene_mine;
	ModulePlayer* player;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleWelcomeTitle* welcometitle;
	ModuleHighscores* highscores;
	ModuleSelection* selection;
	ModuleDebugMode* debug;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__