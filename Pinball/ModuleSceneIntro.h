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

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:
	/*p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List<PhysBody*> ricks;

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;*/
	uint bonus_fx;
	PhysBody* maps;
	p2List<PhysBody*> bouncers;
	p2List<PhysBody*> sensors;

	PhysBody* leftflipper;
	PhysBody* rightflipper;

	bool dead = false;
	bool sensed;
	int font_score = -1;
	char score_text[10];

private:

	void PinballGround();
	void setScores();
	void AddBouncers();
	void UpdateSensors();
	void PlayerLives();
	void SceneChange();
};
