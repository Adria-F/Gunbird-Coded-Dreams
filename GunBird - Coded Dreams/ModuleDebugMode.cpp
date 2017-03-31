#include "Application.h"
#include "ModuleDebugMode.h"
#include "ModuleInput.h"
#include <iostream>
using namespace std;

ModuleDebugMode::ModuleDebugMode()
{

}

ModuleDebugMode::~ModuleDebugMode()
{

}

bool ModuleDebugMode::Start()
{
	LOG("Opened Debug Mode");

	debugging = true;
	
	return debugging;
}

bool ModuleDebugMode::CleanUp()
{
	LOG("Closed Debug Mode");
	
	debugging = false;
	
	return true;
}

update_status ModuleDebugMode::Update()
{
	return UPDATE_CONTINUE;
}