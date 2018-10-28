#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	map_tex = App->textures->Load("pinball/background.png");
	colliders_tex = App->textures->Load("pinball/background_collision.png");
	colliderLeft = App->textures->Load("pinball/colliderleft.png");
	colliderRight = App->textures->Load("pinball/colliderright.png");

	if (!background_created)
		background_created = true;

	int map1[50] = {
		11, 559,
		11, 424,
		18, 415,
		47, 387,
		47, 346,
		41, 320,
		29, 286,
		22, 254,
		18, 227,
		16, 206,
		16, 152,
		25, 112,
		39, 83,
		78, 40,
		102, 26,
		143, 13,
		201, 13,
		234, 22,
		264, 38,
		292, 66,
		308, 96,
		316, 120,
		320, 142,
		321, 160,
		321, 558


	};
	App->physics->CreateChain(0, 0, map1, 50, 0);

	//int map2[0] = {
	//	
	//};
	//App->physics->CreateChain(0, 0, map2, 0, 0);

	//int map3[0] = {
	//	
	//};
	//App->physics->CreateChain(0, 0, map3, 0, 0);

	//int map4[0] = {
	//	
	//};

	//App->physics->CreateChain(0, 0, map4, 0, 0);

	//int map5[0] = {
	//	
	//};

	//App->physics->CreateChain(0, 0, map5, 0, 0);
	//int map6[0] = {
	//	
	//};
	//App->physics->CreateChain(0, 0, map6, 0, 0);

	//int map7[0] = {
	//	
	//};
	//App->physics->CreateChain(0, 0, map7, 0, 0);


	//over joint
	int map8[8] = {
		73, 420,
		72, 454,
		97, 469,
		77, 430
	};
	App->physics->CreateChain(0, 0, map8, 8, 1.5f);

	int map9[8] = {
		222, 467,
		247, 418,
		248, 458,
		232, 463
	};
	App->physics->CreateChain(0, 0, map9, 8, 1.5f);

	//over volt
	int map10[8] = {
		132, 99,
		141, 93,
		140, 120,
		135, 128
	};
	App->physics->CreateChain(0, 0, map10, 8, 0);

	int map11[8] = {
		177, 88,
		184, 88,
		185, 112,
		177, 112
	};
	App->physics->CreateChain(0, 0, map11, 8, 0);
	//diglet
	App->physics->CreateBouncer(60, 365, 15, 1.4f);
	App->physics->CreateBouncer(268, 365, 15, 1.4f);
	//voltorb
	App->physics->CreateBouncer(135, 159, 15, 1.4f);
	App->physics->CreateBouncer(183, 139, 15, 1.4f);
	App->physics->CreateBouncer(170, 199, 15, 1.4f);

	App->physics->CreateBouncer(27, 520, 15, 3.8f);
	App->physics->CreateBouncer(290, 518, 15, 3.8f);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	App->textures->Unload(map_tex);
	App->textures->Unload(colliders_tex);
	App->textures->Unload(colliderLeft);
	App->textures->Unload(colliderRight);
	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	if (map_tex != NULL)
	{
		App->renderer->Blit(map_tex, 0, 0, NULL, 1.0f);
		App->renderer->Blit(colliders_tex, 6, 6, NULL, 1.0f);
		App->renderer->Blit(colliderLeft, 60, 440, NULL, 1.0f);
		App->renderer->Blit(colliderRight, 220, 440, NULL, 1.0f);
	}




	/*if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
	circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 10, b2_dynamicBody));
	circles.getLast()->data->listener = this;
	}*/



	/*if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
	// Pivot 0, 0
	int rick_head[64] = {
	14, 36,
	42, 40,
	40, 0,
	75, 30,
	88, 4,
	94, 39,
	111, 36,
	104, 58,
	107, 62,
	117, 67,
	109, 73,
	110, 85,
	106, 91,
	109, 99,
	103, 104,
	100, 115,
	106, 121,
	103, 125,
	98, 126,
	95, 137,
	83, 147,
	67, 147,
	53, 140,
	46, 132,
	34, 136,
	38, 126,
	23, 123,
	30, 114,
	10, 102,
	29, 90,
	0, 75,
	30, 62
	};

	ricks.add(App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), rick_head, 64,0));
	}*/

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	/*while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = ricks.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(rick, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}*/

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	App->audio->PlayFx(bonus_fx);
}
