#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);
	
public:
	int laps = 1;



	Cube s;
	Cube c1;
	Cube c2;
	Cube c3;
	Cube c4;
	Cube c5;
	Cube c6;
	Cube c7;
	Cube c8;
	Cube c9;
	Cube c10;
	Cube c11;
	Cube c12;
	Cube c13;
	Cube c14;
	Cube c15;
	Cube c16;
	Cube c17;
	Cube c18;
	Cylinder cyl;


	PhysBody3D* sensor;
	PhysBody3D* cube1;
};
