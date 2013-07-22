#include <iostream>
#include <ostream>
#include <vector>
#include <algorithm>

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

class ParticleSystem
{
public:
	ParticleSystem(const float radius_ = 1.f, 
				   const unsigned xSize_ = 20,
				   const unsigned ySize_ = 60,
				   const unsigned zSize_ = 60)
		: xSize(xSize_),
		ySize(ySize_),
		zSize(zSize_),
		quantity(xSize * ySize * zSize),
		mass(1.f),
		radius(radius_)
	{}

	void initialize(const float3 commonVel = float3(3.f, 0.f, 0.f))
	{
		initializePos();
		initializePrevPos();
		initializeVel(commonVel);
		initializePrevVel();
	}
	
	float3 calculateForce(const float dt, const unsigned idx)
	{
		float vx = mass * vel[idx].x / dt;
		float vy = mass * vel[idx].y / dt;
		float vz = mass * vel[idx].z / dt;

		return float3(vx, vy, vz);
	}

	void verlet(const float dt)
	{
		for(unsigned i = 0; i < quantity; ++i)
		{
			float3 force = calculateForce(dt, i);
			vel[i].x += force.x * dt;
			vel[i].y += force.y * dt;
			vel[i].z += force.z * dt;

			pos[i].x += vel[i].x * dt;
			pos[i].y += vel[i].y * dt;
			pos[i].z += vel[i].z * dt;
		}
	}

	vector4 checkCollision(const unsigned idx)
	{
		vector4 collidingParticles;
		float dist;
		float rays = 2.f * radius;

		for(unsigned i = 0; i < quantity; ++i)
		{
			if(i == idx)
				continue;

			dist = calculateDistance(idx, i);

			std::cout << dist << std::endl;

			if(dist <= rays)
				collidingParticles.push_back(float4(prevPos[i], dist));

		}
		return collidingParticles;
	}

	// void reactToCollision(unsigned idx, const vector4& collidingParticles)
	// {
	// 	float dist = collidingParticles[0].z;
	// 	float multiplier = (2.f * radius - dist) / 2.f;
	// 	float3 vecToChange = calculateDistToMove(idx, multiplier);

	// 	std::cout << "currentPos: " << pos[idx] << std::endl;
	// 	pos[idx].x = pos[idx].x - vecToChange.x;
	// 	pos[idx].y = pos[idx].y - vecToChange.y;
	// 	pos[idx].z = pos[idx].z - vecToChange.z;
	// 	std::cout << "newPos: " << pos[idx] << std::endl << std::endl;
	// }







	void copyPosAndVel()
	{
		prevPos = pos;
		prevVel = vel;
	}

	unsigned systemSize() const
	{
		return quantity;
	}

	vector3& getPos()
	{
		return pos;
	}

	vector3& getPrevPos()
	{
		return prevPos;
	}

	vector3& getVel()
	{
		return vel;
	}

	vector3& getPrevVel()
	{
		return prevVel;
	}

private:
	float calculateDistance(const unsigned currentParticle, const unsigned idx)
	{
		float x = prevPos[currentParticle].x - prevPos[idx].x;
		float y = prevPos[currentParticle].y - prevPos[idx].y;
		float z = prevPos[currentParticle].z - prevPos[idx].z;

		return pow(x*x + y*y + z*z, 0.5);
	}

	float3 calculateDistToMove(const unsigned idx, const float multiplier)
	{
		float oppsiteDirec = -1.f;
		float scalledMultiplier = (multiplier + 0.0005f) * oppsiteDirec;
		float3 versor = findVersor(prevVel[idx]);
		float3 dist = float3(versor.x * scalledMultiplier, 
					  		 versor.y * scalledMultiplier, 
					  		 versor.z * scalledMultiplier);
		std::cout << "calculateDistToMove: " << dist << std::endl;
		return dist;
	}

	float3 findVersor(const float3 vec)
	{
		float3 versor = float3(0.f, 0.f, 0.f);

		if(vec.x > 0.f)
			versor.x = 1.f;
		if(vec.x < 0.f)
			versor.x = -1.f;

		if(vec.y > 0.f)
			versor.y = 1.f;
		if(vec.y < 0.f)
			versor.y = -1.f;

		if(vec.z > 0.f)
			versor.z = 1.f;
		if(vec.z < 0.f)
			versor.z = -1.f;

		return versor;
	}

	void initializePos()
	{
		float xRange = xSize;
		float yRange = ySize;
		float zRange = zSize;

		for(float i = -xRange; i < -xRange + xRange/2.f; i += 0.5f)
			for(float j = -yRange/2; j < yRange/2.f; j += 1.f) 
				for(float k = -zRange/2; k < zRange/2.f; k += 1.f)
				{
					pos.push_back(float3(i, j, k));
				}
	}

	void initializePrevPos()
	{
		prevPos = pos;
	}

	void initializeVel(const float3 commonVel)
	{
		for(unsigned i = 0; i < quantity; ++i)
			vel.push_back(commonVel);
	}

	void initializePrevVel()
	{
		prevVel = vel;
	}


	const unsigned xSize;
	const unsigned ySize;
	const unsigned zSize;
	const unsigned quantity;

	const float mass;
	const float radius;

	vector3 pos;
	vector3 prevPos;
	vector3 vel;
	vector3 prevVel;
	//vector color;
};
