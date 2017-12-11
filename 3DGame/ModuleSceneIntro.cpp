#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "ModulePhysics3D.h"
#include "Color.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	
	
	//Water
	c9 = App->physics->AddCube(50, 0.5f, 10, 0, 0, 0, 0.0f, Blue);
	c18 = App->physics->AddCube(14, 0.5f, 50, -15, 0, -20, 0.0f, Blue);
	//Bridge
	c1 = App->physics->AddCube(15, 3, 10, 0, 3, 0, 0.0f, Brown);
	c2 = App->physics->AddCube(2, 2, 2, -5, 4.5, 3, 0.0f, Brown);
	c3 = App->physics->AddCube(2, 2, 2, -5, 4.5, -3, 0.0f, Brown);
	c4 = App->physics->AddCube(2, 2, 2, 5, 4.5, -3, 0.0f, Brown);
	c5 = App->physics->AddCube(2, 2, 2, 5, 4.5, 3, 0.0f, Brown);
	//cyl = App->physics->AddCylinder(3, 1, 0, 3, 30, 0.0f,Red);
	//SAND
	c8 = App->physics->AddCube(15, 3, 10, 0, 3, -10, 0.0f, Sand);
	c15 = App->physics->AddCube(35, 3, 10, 10, 3, -20, 0.0f, Sand);
	c16 = App->physics->AddCubeRotX(15, 3, 20, 20, 4, -30, 0.0f, Sand,30);
	c6 = App->physics->AddCube(15, 3, 30, 0, 3, 20, 0.0f, Sand);
	c7 = App->physics->AddCube(15, 3, 30, 0, 3, 50, 0.0f, Sand);
	c10 = App->physics->AddCubeRotY(15, 3, 30, 12.5, 3, 80, 0.0f, Sand,45);
	c11 = App->physics->AddCubeRotY(15, 3, 25,30, 3, 97.5, 0.0f, Sand, 45);
	c12 = App->physics->AddCube(15, 3, 30, 36, 3, 115.5, 0.0f, Sand);
	c13 = App->physics->AddCube(60, 3, 15,13.5, 3, 138, 0.0f, Sand);
	c17 = App->physics->AddCube(15, 3, 10, -15, 3, -20, 0.0f, Brown);
	c14 = App->physics->AddCubeRotY(15, 3, 25, -8.5, 4, 138.5, 0.0f, Sand, 45);

	
	//SENSORS
	s.size = vec3(15, 3, 1);
	s.SetPos(0, 6, 10);
	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);


	
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
	Plane p(0, 1, 10,0);
	p.axis = true;
	p.color = Green;
	p.Render();
	Cube plane(1000, 0, 1000);
	plane.color = Green;
	plane.Render();

	//sensor->GetTransform(&s.transform);
	//SENSORS
	s.Render();
	//MAP
	c9.Render();
	c1.Render();
	c2.Render();
	c3.Render();
	c4.Render();
	c5.Render();
	c6.Render();
	c7.Render();
	c8.Render();
	c10.Render();
	c11.Render();
	c12.Render();
	c13.Render();
	c14.Render();
	c15.Render();
	c16.Render();
	c17.Render();
	c18.Render();
	
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("1/3");
	laps=laps+1;
}

