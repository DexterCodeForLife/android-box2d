/*
* Copyright (c) 2006-2009 Erin Catto http://www.gphysics.com
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#ifndef CONTACT_SOLVER_H
#define CONTACT_SOLVER_H

#include "../../Common/b2Math.h"
#include "../../Collision/b2Collision.h"
#include "../b2World.h"

class b2Contact;
class b2Body;
class b2Island;
class b2StackAllocator;

struct b2ContactConstraintPoint
{
	b2Vec2 localPoint;
	b2Vec2 rA;
	b2Vec2 rB;
	float32 normalImpulse;
	float32 tangentImpulse;
	float32 normalMass;
	float32 tangentMass;
	float32 equalizedMass;
	float32 velocityBias;
};

struct b2ContactConstraint
{
	b2ContactConstraintPoint points[b2_maxManifoldPoints];
	b2Vec2 localPlaneNormal;
	b2Vec2 localPoint;
	b2Vec2 normal;
	b2Mat22 normalMass;
	b2Mat22 K;
	b2Body* bodyA;
	b2Body* bodyB;
	b2Manifold::Type type;
	float32 radius;
	float32 friction;
	float32 restitution;
	int32 pointCount;
	b2Manifold* manifold;
};

class b2ContactSolver
{
public:
	b2ContactSolver(const b2TimeStep& step, b2Contact** contacts, int32 contactCount, b2StackAllocator* allocator);
	~b2ContactSolver();

	void InitVelocityConstraints(const b2TimeStep& step);
	void SolveVelocityConstraints();
	void FinalizeVelocityConstraints();

	bool SolvePositionConstraints(float32 baumgarte);

	b2TimeStep m_step;
	b2StackAllocator* m_allocator;
	b2ContactConstraint* m_constraints;
	int m_constraintCount;
};

#endif
