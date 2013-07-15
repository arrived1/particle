#include <iostream>
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

typedef std::vector<float3> vector;

class ParticleSystem
{
public:
	ParticleSystem(const unsigned xSize_ = 20,
				   const unsigned ySize_ = 60,
				   const unsigned zSize_ = 60)
		: xSize(xSize_),
		ySize(ySize_),
		zSize(zSize_),
		quantity(xSize * ySize * zSize)
	{}

	void initialize(float3 commonVel)
	{
		initializePos();
		initializePrevPos();
		initializeVel(commonVel);
		initializePrevVel();
	}
	
	unsigned systemSize() const
	{
		return quantity;
	}

	vector& getPos()
	{
		return pos;
	}

	vector& getPrevPos()
	{
		return prevPos;
	}

	vector& getVel()
	{
		return vel;
	}

	vector& getPrevVel()
	{
		return prevVel;
	}


private:
	void initializePos()
	{
		float xRange = xSize;
		float yRange = ySize;
		float zRange = zSize;

		std::cout << "Initializing particle pos" << std::endl;

		for(float i = -xRange; i < -xRange + xRange/2; i += 0.5f)
			for(float j = -yRange/2; j < yRange/2; j += 1.f) 
				for(float k = -zRange/2; k < zRange/2; k += 1.f)
				{
					pos.push_back(float3(i, j, k));
				}
	}

	void initializePrevPos()
	{
		prevPos = pos;
	}

	void initializeVel(float3 commonVel)
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

	vector pos;
	vector prevPos;
	vector vel;
	vector prevVel;
	//vector color;
};
