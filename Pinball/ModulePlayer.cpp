#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleSceneIntro.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFonts.h"
#include <cstring>

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	textureball = textureLKicker = TextureRkicker = TexturePusher = NULL;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	textureball = App->textures->Load("pinball/balls.png");
	textureLKicker = App->textures->Load("pinball/kickerL.png");
	TextureRkicker = App->textures->Load("pinball/kickerR.png");
	TexturePusher = App->textures->Load("pinball/pusher.png");
	points = 0;
	lives = 3;
	leftkicker();
	rightkicker();
	pusherfunc();
	ballposition(PLAYER_POS_X, PLAYER_POS_Y);
	hitsound = App->audio->LoadFx("pinball/points.wav");
	fontscore = App->fonts->Load("pinball/fontnumbers.png", "0123456789", 1);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	App->textures->Unload(TexturePusher);
	App->textures->Unload(TextureRkicker);
	App->textures->Unload(textureLKicker);
	App->textures->Unload(textureball);
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
	{
		kickerrightjoint->EnableMotor(true);
		App->audio->PlayFx(hitsound);
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_UP)
	{
		kickerrightjoint->EnableMotor(false);
		App->audio->PlayFx(hitsound);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
	{
		kickerleftjoint->EnableMotor(true);
		App->audio->PlayFx(hitsound);
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_UP)
	{
		kickerleftjoint->EnableMotor(false);
		App->audio->PlayFx(hitsound);
	}


	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		pusherjoint->EnableMotor(true);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_UP)
	{

		pusherjoint->EnableMotor(false);
	}

	//Flippers Draw------

	int x, y;
	kickerright->GetPosition(x, y);
	App->renderer->Blit(TextureRkicker, x, y, NULL, 1.0f, kickerright->GetRotation());

	kickerleft->GetPosition(x, y);
	App->renderer->Blit(textureLKicker, x, y, NULL, 1.0f, kickerleft->GetRotation());


	//Ball Draw--------------------
	ball->GetPosition(position.x, position.y);
	App->renderer->Blit(textureball, position.x, position.y, NULL, 1.0f, 1.0f, ball->GetRotation());

	//pusher Draw--------------------
	pusher->GetPosition(position.x, position.y);
	App->renderer->Blit(TexturePusher, position.x -10, position.y - 18, NULL, 1.0f, 1.0f, ball->GetRotation());

	//sprintf
	
	sprintf_s(scoreText, 10, "%d", score);
	App->fonts->BlitText(200, 10, fontscore, scoreText);

	return UPDATE_CONTINUE;
}

void ModulePlayer::ballposition(uint x, uint y)
{
	ball = App->physics->CreateCircle(x, y - 12, 7, b2_dynamicBody);
	ball->listener = this;
}

void ModulePlayer::OnCollision(PhysBody * body_A, PhysBody * body_B)
{

}

void ModulePlayer::rightkicker() {

	kickerright = App->physics->CreateRectangle(180, 483, 50, 10, b2_dynamicBody, 1.2f);
	kickerrightpivot = App->physics->CreateCircle(208, 535, 7, b2_staticBody);

	b2RevoluteJointDef revoluteJointDef;

	revoluteJointDef.bodyA = kickerright->body;
	revoluteJointDef.bodyB = kickerrightpivot->body;

	kickerright->body->SetGravityScale(10.0f);

	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(15), PIXEL_TO_METERS(0));
	revoluteJointDef.localAnchorB.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));

	revoluteJointDef.collideConnected = false;
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 25 * DEGTORAD;
	revoluteJointDef.lowerAngle = -20 * DEGTORAD;
	revoluteJointDef.motorSpeed = -2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;
	kickerrightjoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);
}

void ModulePlayer::pusherfunc() {

	pusher = App->physics->CreateRectangle(PLAYER_POS_X, PLAYER_POS_Y + 20, 20, 30, b2_dynamicBody, 0);
	pusherpivot = App->physics->CreateRectangle(PLAYER_POS_X, PLAYER_POS_Y + 50, 12, 20, b2_staticBody, 0);
	b2PrismaticJointDef prismaticJointDef;
	prismaticJointDef.bodyA = pusher->body;
	prismaticJointDef.bodyB = pusherpivot->body;
	prismaticJointDef.localAnchorA.Set(0, 0);
	prismaticJointDef.localAnchorB.Set(0, 0);
	prismaticJointDef.collideConnected = false;
	prismaticJointDef.localAxisA.Set(0, 1);
	prismaticJointDef.enableLimit = true;
	prismaticJointDef.lowerTranslation = 0;
	prismaticJointDef.upperTranslation = PIXEL_TO_METERS(50);
	prismaticJointDef.enableMotor = false;
	prismaticJointDef.maxMotorForce = 80;
	prismaticJointDef.motorSpeed = 5000;
	pusherjoint = (b2PrismaticJoint*)App->physics->world->CreateJoint(&prismaticJointDef);
}

void ModulePlayer::leftkicker() {

	kickerleft = App->physics->CreateRectangle(142, 483, 50, 10, b2_dynamicBody, 1.2f);//210 741
	kickerleftpivot = App->physics->CreateCircle(104, 535, 7, b2_staticBody);
	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.bodyA = kickerleft->body;
	revoluteJointDef.bodyB = kickerleftpivot->body;
	kickerleft->body->SetGravityScale(10.0f);
	revoluteJointDef.localAnchorA.Set(PIXEL_TO_METERS(-18), 0);
	revoluteJointDef.localAnchorB.Set(0, 0);
	revoluteJointDef.collideConnected = false;
	revoluteJointDef.enableLimit = true;
	revoluteJointDef.upperAngle = 25 * DEGTORAD;
	revoluteJointDef.lowerAngle = -20 * DEGTORAD;
	revoluteJointDef.motorSpeed = 2000.0f * DEGTORAD;
	revoluteJointDef.maxMotorTorque = 1500.0f;
	revoluteJointDef.enableMotor = false;
	kickerleftjoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&revoluteJointDef);

}


