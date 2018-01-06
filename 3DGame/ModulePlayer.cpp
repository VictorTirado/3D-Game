#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis_size.Set(2, 1.5,3);
	car.chassis_offset.Set(0, 1.5, 0);
	car.mass = 1000.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 0.8f;
	float wheel_radius = 0.5f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 0.5f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis_size.x*0.5f;
	float half_length = car.chassis_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0,3,0);
	vehicle->GetTransform(&originalMatrix);
	App->camera->Follow(vehicle, 10, 10, 1.f);

	App->audio->LoadFx("Audio/engine.wav");
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{

	turn = acceleration = brake = 0.0f;
	float seconds_since_startup = startup_time.Read() / 1000;
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		{
			acceleration = MAX_ACCELERATION;
			App->audio->PlayFx(1,1);
		}

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (turn < TURN_DEGREES) {
				turn += TURN_DEGREES;
			}
		}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (turn > -TURN_DEGREES) {
				turn -= TURN_DEGREES;
			}
		}

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		{
			acceleration = -MAX_ACCELERATION;
		}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
		{
			brake = BRAKE_POWER;
		}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();
	char title[180];
	sprintf_s(title, "%.1fKm/h     Laps:%i/3     Time:%.f/%.fs     First lap time:%.fs     Second lap time:%.fs     Third lap time:%.fs", vehicle->GetKmh(), App->scene_intro->laps, seconds_since_startup, maxTime, App->scene_intro->lap1_time, App->scene_intro->lap2_time, App->scene_intro->lap3_time);
	App->window->SetTitle(title);
	vehicle->GetTransform(&matrix);
	position = matrix.translation();
	speed = vehicle->GetKmh();

	if (seconds_since_startup > maxTime && App->scene_intro->laps<=3 && newWalls == false) {
		wall1 = App->physics->AddCube(1500, 100, 1, 0, 0, -130, 0.0f, Red);
		wall2 = App->physics->AddCube(1500, 100, 1, 0, 0, 390, 0.0f, Red);
		wall3 = App->physics->AddCube(1, 100, 1500, 90, 0, -140, 0.0f, Red);
		wall4 = App->physics->AddCube(1, 100, 1500, -390, 0, -140, 0.0f, Red);
		wall5 = App->physics->AddCube(1500, 100, 1500, -390, 90, -140, 0.0f, Red);
		newWalls = true;
	}

	if (App->scene_intro->laps>3 && seconds_since_startup < maxTime && newWalls == false) {
		wall1 = App->physics->AddCube(1500, 100, 1, 0, 0, -130, 0.0f, Green);
		wall2 = App->physics->AddCube(1500, 100, 1, 0, 0, 390, 0.0f, Green);
		wall3 = App->physics->AddCube(1, 100, 1500, 90, 0, -140, 0.0f, Green);
		wall4 = App->physics->AddCube(1, 100, 1500, -390, 0, -140, 0.0f, Green);
		wall5 = App->physics->AddCube(1500, 100, 1500, -390, 90, -140, 0.0f, Green);
		newWalls = true;
	}
	if (newWalls == true) {
		wall1.Render();
		wall2.Render();
		wall3.Render();
		wall4.Render();
		wall5.Render();
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer::changePos(vec3 pos) {
	vehicle->SetPos(pos.x, pos.y, pos.z);
	mat4x4 newTransform = originalMatrix;
	newTransform.translation() = pos;
	newTransform.M[12] = pos.x;
	newTransform.M[13] = pos.y;
	newTransform.M[14] = pos.z;
	if (App->scene_intro->checkPoint2 == true && App->scene_intro->checkPoint3 == false) {
		newTransform.rotate(-135 , { 0,1,0 });
	}
	if (App->scene_intro->checkPoint3 == true) {
		newTransform.rotate(180, { 0,1,0 });
	}
	vehicle->SetTransform(&newTransform);
}



