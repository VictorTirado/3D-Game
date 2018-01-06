#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "Color.h"
#include "ModulePlayer.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	enum RotType { NONE, ROT_X, ROT_Y, ROT_Z };
	struct CubeDef {
		float x, y, z, w, d, h;
		float mass;
		Color color;
		RotType rot;
		float angle;

	};
	CubeDef cubes[] = {
		{ 50, 0.5f, 10, 0, 0, 0, 0.0f, Blue, NONE, 0.f },
		{ 50, 0.5f, 10, 0, 0, 0, 0.0f, Blue, NONE, 0.f },

	};
	
	

	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));


	//Water
	c9 = App->physics->AddCube(50, 0.5f, 10, 0, 0, 0, 0.0f, Blue);
	//AddCube()
	c18 = App->physics->AddCube(14, 0.5f, 50, -15, 0, -20, 0.0f, Blue);
	//Bridge
	c1 = App->physics->AddCube(15, 3, 10, 0, 3, 0, 0.0f, Brown);
	c2 = App->physics->AddCube(2, 2, 2, -5, 4.5, 3, 0.0f, Brown);
	c3 = App->physics->AddCube(2, 2, 2, -5, 4.5, -3, 0.0f, Brown);
	c4 = App->physics->AddCube(2, 2, 2, 5, 4.5, -3, 0.0f, Brown);
	c5 = App->physics->AddCube(2, 2, 2, 5, 4.5, 3, 0.0f, Brown);
	//cyl = App->physics->AddCylinder(3, 1, 0, 3, 30, 0.0f,Red);
	//SAND
	c8 = App->physics->AddCube(15, 3, 10, 0, 3.001, -10, 0.0f, Sand);
	c15 = App->physics->AddCube(35, 3, 10, 10, 3, -20, 0.0f, Sand);
	c16 = App->physics->AddCubeRotX(15, 3, 20, 20, 4, -30, 0.0f, Sand, 30);
	c21 = App->physics->AddCubeRotY(30, 3, 30, 10, 8.75, -53, 0.0f, Sand, 0);
	c22 = App->physics->AddCubeRotX(15, 3, 20, 2.5, 8.75, -35, 0.0f, Sand, -20);
	c6 = App->physics->AddCube(15, 3, 30, 0, 3.001, 20, 0.0f, Sand);
	c7 = App->physics->AddCube(15, 3, 30, 0, 3, 50, 0.0f, Sand);
	c41 = App->physics->AddCube(15, 3, 30, 0, 3, 65, 0.0f, Sand);
	c10 = App->physics->AddCubeRotY(15, 3, 30, 12.5, 3.001, 80, 0.0f, Sand, 45);
	c11 = App->physics->AddCubeRotY(15, 3, 25, 30, 3, 97.5, 0.0f, Sand, 45);
	c12 = App->physics->AddCube(15, 3, 30, 36, 3.001, 115.5, 0.0f, Sand);
	c13 = App->physics->AddCube(60, 3, 15, 13.5, 3, 138, 0.0f, Sand);
	c17 = App->physics->AddCube(15, 3, 10, -15, 3.001, -20, 0.0f, Brown);
	c14 = App->physics->AddCubeRotY(15, 3, 25, -13.5, 2.999, 130.5, 0.0f, Sand, 45);
	c19 = App->physics->AddCubeRotY(15, 3,25, -30.5, 3, 113.5, 0.0f, Sand, 45);
	c20 = App->physics->AddCubeRotY(30, 3, 10, -37.5, 3.001, -20, 0.0f, Sand, 0);
	c23 = App->physics->AddCubeRotY(15, 3, 25, -47.5, 3, 96.5, 0.0f, Sand, 45);
	c24 = App->physics->AddCubeRotY(15, 3, 50, -71.5, 2.999, 111.5, 0.0f, Sand, 130);
	c25 = App->physics->AddCubeRotX(15, 3, 20, -85.5, 3, 127.5, 0.0f, Sand,-15);
	c26 = App->physics->AddCubeRotX(40, 3.0001, 50, -85.5, 3.001, 190.5, 0.0f, Sand, 0);
	c27 = App->physics->AddCubeRotX(50, 3, 20, -125.5, 3, 205.5, 0.0f, Sand, 0);
	c28 = App->physics->AddCubeRotY(50, 3, 20, -150.5, 2.999, 190.5, 0.0f, Sand, -45);
	c29 = App->physics->AddCubeRotY(15, 3, 60, -168.5, 3.002, 150.5, 0.0f, Sand, 0);
	c30 = App->physics->AddCubeRotY(15, 3, 60, -168.5, 3.001, 90.5, 0.0f, Sand, 0);
	c31 = App->physics->AddCubeRotY(1, 10, 60, -176.5, 9, 90.5, 0.0f, Black, 0);
	c32 = App->physics->AddCubeRotY(1, 10, 60, -160.5, 9, 90.5, 0.0f, Black, 0);
	c33 = App->physics->AddCubeRotY(17, 1, 60, -168.5, 14, 90.5, 0.0f, Black, 0);
	c34 = App->physics->AddCubeRotY(15, 3, 30, -168.5, 3, 45.5, 0.0f, Sand, 0);
	c35 = App->physics->AddCubeRotY(15, 3, 15, -153.5, 2.999, 38.5, 0.0f, Sand, 0);
	c36 = App->physics->AddCubeRotY(15, 3, 30, -153.5, 2.998, 20.5, 0.0f, Sand, 0);
	c37 = App->physics->AddCubeRotY(15, 3, 15, -138.5, 2.999, 13, 0.0f, Sand, 0);
	c39 = App->physics->AddCubeRotY(15, 3, 30, -138.5, 3.001, -9.5, 0.0f, Sand, 0);
	c38 = App->physics->AddCubeRotY(140, 3, 10, -67.5, 3, -20, 0.0f, Sand, 0);
	c40 = App->physics->AddCube(15, 2.5, 2, 0, 6.001, -14, 0.0f, Sand);
	//bridge = App->physics->AddConstraintHinge(*c20.body, *c17.body, c20.size, c17.size, { c20.size.x, c20.size.y, c20.size.z }, {0,c17.size.y,0}, true);
	////bridge->enableMotor(true);
	//bridge->enableAngularMotor(true, 5, 50);
	////bridge->setMaxMotorImpulse(50);
	//bridge->setLimit(0, 10);

	//SENSORS
	s.size = vec3(15, 3, 1);
	s.SetPos(0, 6, 10);
	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	s2.size = vec3(15, 3, 1);
	s2.SetPos(-85, 8, 130);
	sensor2 = App->physics->AddBody(s2, 0.0f);
	sensor2->SetAsSensor(true);
	sensor2->collision_listeners.add(this);

	s3.size = vec3(15, 3, 1);
	s3.SetPos(-168.5, 7, 90.5);
	sensor3 = App->physics->AddBody(s3, 0.0f);
	sensor3->SetAsSensor(true);
	sensor3->collision_listeners.add(this);

	gs.size = vec3(1000, 2, 1000);
	gs.SetPos(0, 0, 0);
	groundSensor = App->physics->AddBody(gs, 0.0f);
	groundSensor->SetAsSensor(true);
	groundSensor->collision_listeners.add(this);


	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 10, 0);
	p.axis = true;
	p.color = Green;
	p.Render();
	Cube plane(1000, 0, 1000);
	plane.Render();

	//sensor->GetTransform(&s.transform);
	//SENSORS
	//s.Render();
	s2.Render();
	s3.Render();
	//gs.Render();

	p2List_item<Cube>* cube = cubes.getFirst();

	while (cube != nullptr) {
		cube->data.Render();

		cube = cube->next;
	}
	p2List_item<Cube>* cube1 = cubesRotX.getFirst();

	while (cube1 != nullptr) {
		cube1->data.Render();

		cube1 = cube1->next;
	}
	p2List_item<Cube>* cube2 = cubesRotX.getFirst();

	while (cube != nullptr) {
		cube2->data.Render();

		cube2 = cube2->next;
	}
	if (laps == 1)
	{
		lap1_time = App->player->startup_time.Read() / 1000;
	}
	if (laps == 2)
	{
		lap2_time = (App->player->startup_time.Read() / 1000) - lap1_time;
	}
	if (laps == 3)
	{
		lap3_time = (App->player->startup_time.Read() / 1000) - lap2_time - lap1_time;
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body1 == sensor || body2 == sensor) {
		if (checkPoint1 == true && checkPoint2 == true && checkPoint3 == true) {
			checkPoint1 = true;
			checkPoint2 = false;
			checkPoint3 = false;
			
			
			laps = laps + 1;
		}
		else if (checkPoint1 == false && checkPoint2 == false && checkPoint3 == false) {
			checkPoint1 = true;
		}
	}
	if (body1 == sensor2 || body2 == sensor2) {
		if (checkPoint1 == true && checkPoint2 == false && checkPoint3 == false) {
			checkPoint2 = true;
		}
	}
	if (body1 == sensor3 || body2 == sensor3) {
		if (checkPoint1 == true && checkPoint2 == true && checkPoint3 == false) {
			checkPoint3 = true;
		}
	}
	if (body1 == groundSensor || body2 == groundSensor) {
		App->player->acceleration = 0;
		App->player->brake = BRAKE_POWER;
		if (checkPoint1 == true && checkPoint2 == false && checkPoint3 == false || checkPoint1 == false && checkPoint2 == false && checkPoint3 == false) {
			App->player->changePos({ 0,5,0 });
		}
		if (checkPoint1 == true && checkPoint2 == true && checkPoint3 == false) {
			App->player->changePos({ -25, 8, 115 });
		}
		if (checkPoint1 == true && checkPoint2 == true && checkPoint3 == true) {
			App->player->changePos({ -165.5, 4, 150.5 });
		}
	}
}

