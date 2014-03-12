#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>

struct float2
{
	float2(float x_ = 0, float y_ = 0)
		: x(x_), y(y_)
	{}
	
	float x;
	float y;
};

struct float3
{
	float3(float x_ = 0, float y_ = 0, float z_ = 0)
		: x(x_), y(y_), z(z_)
	{}
	
	float x;
	float y;
	float z;
};

struct float4 : public float3
{
	float4(float x_ = 0, float y_ = 0, float z_ = 0, float w_ = 0)
		: float3(x_, y_, z_), 
		w(w_)
	{}

	float4(float3 f3_, float w_)
		: float3(f3_.x, f3_.y, f3_.z),
		w(w_)
	{}

	float w;
};


std::ostream & operator<<(std::ostream &out, const float3 &f)         
 {
   return out << "(" << f.x << ", " << f.y << ", " << f.z << ")";
 }


typedef std::vector<float3> vector3;
typedef std::vector<float4> vector4;

#define SQR(x) ((x)*(x))

template<typename T>
class ParticleSystem
{
	typedef std::vector<T> vecType;
	vecType vel;
	vecType nextVel;
	vecType pos;
	vecType prevPos;
	vecType nextPos;
	float mass;
	float radius;
	unsigned particles;
	unsigned step;

public:
	ParticleSystem(unsigned particlesAmount = 2) 
		: mass(1.f),
		radius(0.03f),
		particles(particlesAmount),
		step(0u)
	{
		initlize();
	}

	void initlize() {

		vel.push_back(T(4.f, 0.f));
		pos.push_back(T(-1.f, 0.f));
		prevPos.push_back(pos[0]);

		vel.push_back(T(-4.f, 0.f));
		pos.push_back(T(1.f, 0.f));
		prevPos.push_back(pos[1]);
	}




	void prepareMoveEuler(unsigned i, T acceleration, float dt) {
		nextVel[i] = vel[i] + acceleration * dt;
		nextPos[i] = pos[i] + nextVel[i] * dt;
	}


	void prepareMoveVerlet(unsigned i, T acceleration, float dt) {
		if(step == 0)
			prepareMoveEuler(i, acceleration, dt);

		nextPos[i] = 2.f * pos[i] - prevPos[i] + acceleration * SQR(dt);
		nextVel[i] = (nextPos[i] - prevPos[i]) / (2.f * dt);
	}


	void prepareMove(unsigned i, T force, float dt) {
		T acceleration = force / mass;

		prepareMoveVerlet(i, acceleration, dt);
	}


	void move(unsigned i) {
		prevPos[i] = pos[i];
		pos[i] = nextPos[i];
		vel[i] = nextVel[i];
		step++;
	}


};
