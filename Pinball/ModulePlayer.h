#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2List.h"
#include "p2Point.h"
#include "Box2D/Box2D/Box2D.h"

class PhysBody;
struct SDL_Texture;

#define PLAYER_POS_X 321
#define PLAYER_POS_Y 530

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();

	uint points;
	uint lives;

	SDL_Texture* textureball;
	SDL_Texture* textureLKicker;
	SDL_Texture* TextureRkicker;
	SDL_Texture* TexturePusher;

	iPoint position;
	
	PhysBody* ball;
	int* score;
private:

	PhysBody * pusher;
	PhysBody* pusherpivot;
	PhysBody* kickerleft;
	PhysBody* kickerleftpivot;
	PhysBody* kickerright;
	PhysBody* kickerrightpivot;
	void OnCollision(PhysBody * bodyA, PhysBody * bodyB);
	void rightkicker();
	void leftkicker();
	void pusherfunc();
	void ballposition(uint x, uint y);
	b2PrismaticJoint* pusherjoint;
	b2RevoluteJoint* kickerleftjoint;
	b2RevoluteJoint* kickerrightjoint;
};