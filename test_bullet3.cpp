// The files in this repository are licensed under the zlib license.

#include "btBulletDynamicsCommon.h"

#include <memory>
#include <cstdio>

int main()
{
	btDefaultCollisionConfiguration config;
	btCollisionDispatcher dispatcher(&config);

	btDbvtBroadphase broadphase;
	btSequentialImpulseConstraintSolver solver;
	btDiscreteDynamicsWorld world(&dispatcher, &broadphase, &solver, &config);

	world.setGravity(btVector3(0.f, -10.f, 0.f));

	btBoxShape groundShape(btVector3(50.f, 50.f, 50.f));
	const btScalar sphereMass = 1.f;
	btSphereShape sphereShape(1.f);
	btVector3 sphereInertia(0.f, 0.f, 0.f);
	sphereShape.calculateLocalInertia(sphereMass, sphereInertia);

	btDefaultMotionState groundMotion(btTransform(btQuaternion(), btVector3(0.f, -50.f, 0.f)));
	btDefaultMotionState firstSphereMotion(btTransform(btQuaternion(), btVector3(0.f, 10.f, 0.f)));
	btDefaultMotionState secondSphereMotion(btTransform(btQuaternion(), btVector3(0.f, 20.f, 0.f)));

	btRigidBody groundBody(
		btRigidBody::btRigidBodyConstructionInfo(
			/*mass=*/0.f,
			/*motionState=*/&groundMotion,
			/*shape=*/&groundShape,
			/*inertia=*/btVector3(0.f, 0.f, 0.f)
		)
	);

	btRigidBody firstSphereBody(
		btRigidBody::btRigidBodyConstructionInfo(
			/*mass=*/sphereMass,
			/*motionState=*/&firstSphereMotion,
			/*shape=*/&sphereShape,
			/*inertia=*/sphereInertia
		)
	);

	btRigidBody secondSphereBody(
		btRigidBody::btRigidBodyConstructionInfo(
			/*mass=*/1.f,
			/*motionState=*/&secondSphereMotion,
			/*shape=*/&sphereShape,
			/*inertia=*/sphereInertia
		)
	);

	world.addRigidBody(&groundBody);
	world.addRigidBody(&firstSphereBody);
	world.addRigidBody(&secondSphereBody);

	for (int step = 0; step < 180; ++step)
	{
		world.stepSimulation(1.f / 60.f, 10);
	}

	btTransform trans;
	firstSphereMotion.getWorldTransform(trans);
	const btVector3 result = trans.getOrigin();

	const btVector3 expected(0.f, 1.f, 0.f);
	const btVector3 delta = (result - expected).absolute();

	const float epsilon = 0.001f; // weak epsilon; just looking for ballpark accuracy

	std::printf(
		"RESULT x:%+11.6f, y:%+11.6f, z:%+11.6f\n"
		"EXPECT x:%+11.6f, y:%+11.6f, z:%+11.6f\n"
		" DELTA x:%+11.6f, y:%+11.6f, z:%+11.6f\n"
		"EPSILON %g\n",
		result.getX(), result.getY(), result.getZ(),
		expected.getX(), expected.getY(), expected.getZ(),
		delta.getX(), delta.getY(), delta.getZ(),
		epsilon);

	if (delta.getX() >= epsilon)
		return 1;
	if (delta.getY() >= epsilon)
		return 2;
	if (delta.getZ() >= epsilon)
		return 3;
}