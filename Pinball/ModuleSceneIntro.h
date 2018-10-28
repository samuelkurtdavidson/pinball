#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool background_created = false;

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	void SetBall(int x, int y);

public:
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	SDL_Texture* map_tex;
	SDL_Texture* colliders_tex;
	SDL_Texture* colliderLeft;
	SDL_Texture* colliderRight;
	SDL_Texture* tube1;
	SDL_Texture* tube2;
	SDL_Texture* rail1;
	SDL_Texture* rail2;
	SDL_Texture* rail3;
	SDL_Texture* shootsunny;
	uint bonus_fx;
	iPoint pos;
};
