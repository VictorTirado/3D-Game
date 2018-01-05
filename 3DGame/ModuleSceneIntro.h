#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#include "Bullet/include/btBulletDynamicsCommon.h"

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

	btHingeConstraint* bridge;

	Cube s;
	Cube s2;
	Cube s3;
	Cube gs;

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
	Cube c19;
	Cube c20;
	Cube c21;
	Cube c22;
	Cube c23;
	Cube c24;
	Cube c25;
	Cube c26;
	Cube c27;
	Cube c28;
	Cube c29;
	Cube c30;
	Cube c31;
	Cube c32;
	Cube c33;
	Cube c34;
	Cube c35;
	Cube c36;
	Cube c37;
	Cube c38;
	Cube c39;
	
	Cylinder cyl;


	PhysBody3D* sensor;
	PhysBody3D* sensor2;
	PhysBody3D* sensor3;
	PhysBody3D* groundSensor;
	PhysBody3D* cube1;

	bool checkPoint1 = false;
	bool checkPoint2 = false;
	bool checkPoint3 = false;

	
};
