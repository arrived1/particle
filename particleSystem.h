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
};
