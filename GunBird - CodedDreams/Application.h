#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 16

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneMine;
class Player;
class ModuleMarion;
class ModuleAsh;
class ModuleFadeToBlack;
class Module;
class ModuleAudio;
class ModuleWelcomeTitle;
class ModuleHighscores;
class ModuleSelection;
class ModuleDebugMode;
class ModuleParticles;
class ModuleCollision;
class ModulePowerUp;
class ModuleEnemies;
class ModuleFonts;
class ModuleUI;

class Application
{
public:

	Module* modules[NUM_MODULES];
	ModuleWindow* window;
	ModuleRender* render;
	ModuleInput* input;
	ModuleTextures* textures;
	ModuleSceneMine* scene_mine;
	Player* player1;
	Player* player2;
	ModuleMarion* marion;
	ModuleAsh* ash;
	ModuleFadeToBlack* fade;
	ModuleAudio* audio;
	ModuleWelcomeTitle* welcometitle;
	ModuleHighscores* highscores;
	ModuleSelection* selection;
	ModuleDebugMode* debug;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModulePowerUp* powerup;
	ModuleEnemies* enemies;
	ModuleFonts* fonts;
	ModuleUI* ui;
	

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