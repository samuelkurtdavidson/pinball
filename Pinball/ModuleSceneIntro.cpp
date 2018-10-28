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
	tube1 = App->textures->Load("pinball/tube1.png");
	tube2 = App->textures->Load("pinball/tube2.png");
	rail1 = App->textures->Load("pinball/rail1.png");
	rail2 = App->textures->Load("pinball/rail2.png");
	rail3 = App->textures->Load("pinball/rail3.png");
	shootsunny = App->textures->Load("pinball/shoot_sunny.png");


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

	for (int i = 0; i < 50; ++i)
	{
		map1[i] += 6;
	}

	App->physics->CreateChain(0, 0, map1, 50, 0);

	int map2[60] = {
		44, 251,
		37, 224,
		34, 203,
		33, 190,
		33, 164,
		40, 123,
		52, 97,
		78, 67,
		101, 51,
		135, 38,
		147, 38,
		162, 54,
		162, 85,
		173, 104,
		173, 158,
		114, 204,
		108, 204,
		98, 184,
		99, 168,
		108, 156,
		108, 142,
		97, 137,
		88, 140,
		76, 157,
		72, 168,
		72, 185,
		77, 203,
		87, 220,
		87, 224,
		47, 254

	};

	for (int i = 0; i < 60; ++i)
	{
		map2[i] += 6;
	}

	App->physics->CreateChain(0, 0, map2, 60, 0);

	int map3[32] = {
		241, 125,
		243, 60,
		248, 53,
		252, 55,
		280, 83,
		295, 109,
		301, 130,
		302, 144,
		303, 164,
		300, 180,
		294, 194,
		290, 198,
		287, 197,
		275, 170,
		262, 150,
		242, 127

	};

	for (int i = 0; i < 32; ++i)
	{
		map3[i] += 6;
	}

	App->physics->CreateChain(0, 0, map3, 32, 0);

	int map4[30] = {
		187, 217,
		205, 140,
		235, 158,
		262, 188,
		281, 221,
		284, 225,
		257, 259,
		253, 259,
		216, 240,
		220, 230,
		220, 223,
		213, 213,
		208, 212,
		200, 212,
		192, 218

	};

	for (int i = 0; i < 30; ++i)
	{
		map4[i] += 6;
	}

	App->physics->CreateChain(0, 0, map4, 30, 0);

	int map5[22] = {
		306, 558,
		306, 296,
		303, 296,
		278, 301,
		264, 333,
		262, 344,
		262, 381,
		267, 394,
		296, 420,
		298, 421,
		298, 558

	};

	for (int i = 0; i < 22; ++i)
	{
		map5[i] += 6;
	}

	App->physics->CreateChain(0, 0, map5, 22, 0);

	int map6[10] = {
		275, 558,
		275, 532,
		272, 528,
		267, 530,
		209, 558
	};

	for (int i = 0; i < 10; ++i)
	{
		map6[i] += 6;
	}

	App->physics->CreateChain(0, 0, map6, 10, 0);

	int map7[10] = {
		31, 559,
		31, 531,
		32, 530,
		39, 530,
		98, 559
	};

	for (int i = 0; i < 10; ++i)
	{
		map7[i] += 6;
	}

	App->physics->CreateChain(0, 0, map7, 10, 0);

	int map8[16] = {
		69, 445,
		98, 495,
		98, 499,
		97, 500,
		92, 500,
		62, 483,
		62, 445,
		64, 442

	};

	App->physics->CreateChain(0, 0, map8, 16, 0);

	int map9[18] = {
		222, 494,
		252, 443,
		253, 442,
		256, 442,
		258, 444,
		258, 483,
		256, 486,
		229, 500,
		223, 500
	};

	App->physics->CreateChain(0, 0, map9, 18, 0);

	int map10[16] = {
		96, 530,
		38, 503,
		38, 449,
		34, 451,
		34, 504,
		37, 508,
		95, 536,
		98, 533

	};

	App->physics->CreateChain(0, 0, map10, 16, 0);

	int map11[16] = {
		220, 531,
		277, 503,
		277, 450,
		279, 448,
		282, 448,
		282, 506,
		222, 536,
		219, 534
	};

	App->physics->CreateChain(0, 0, map11, 16, 0);


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
	App->textures->Unload(tube1);
	App->textures->Unload(tube2);
	App->textures->Unload(rail1);
	App->textures->Unload(rail2);
	App->textures->Unload(rail3);
	App->textures->Unload(shootsunny);
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
		App->renderer->Blit(tube1, 220, 100, NULL, 1.0f);
		App->renderer->Blit(tube2, 220, 100, NULL, 1.0f);
		App->renderer->Blit(rail1, 30, 20, NULL, 1.0f);
		App->renderer->Blit(rail2, 30, 20, NULL, 1.0f);
		App->renderer->Blit(rail3, 253, 190, NULL, 1.0f);
		App->renderer->Blit(shootsunny, 0, 15, NULL, 1.0f);
	}

	// Prepare for raycast ------------------------------------------------------

	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// All draw functions ------------------------------------------------------
	p2List_item<PhysBody*>* c = circles.getFirst();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	App->audio->PlayFx(bonus_fx);
}
