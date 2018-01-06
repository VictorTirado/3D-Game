#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 1500.0f
#define TURN_DEGREES 15.0f * DEGTORAD
#define BRAKE_POWER 1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	mat4x4 matrix;
	mat4x4 originalMatrix;
	vec3 position;
	float speed;
	Timer startup_time;
	float total_time;
	float maxTime = 240.0f;
	void changePos(vec3 pos);
	Cube wall1;
	Cube wall2;
	Cube wall3;
	Cube wall4;
	Cube wall5;
	bool newWalls = false;
};