#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include "particleSystem.h"

class ParticleSystemTest : public testing::Test 
{
public:
	void SetUp()
	{
		x = 2;
		y = 6;
		z = 6;
		radius = 1.f;
		commonVel.reset(new float3(3.f, 0, 0));
		system.reset(new ParticleSystem(radius, x, y, z));
	}

	void checkDistanceBetweenParticles(vector4 vec);

	unsigned x, y, z;
	float radius;
	boost::shared_ptr<float3> commonVel;
	boost::shared_ptr<ParticleSystem> system;
};

void ParticleSystemTest::checkDistanceBetweenParticles(vector4 vec)
{
	for(unsigned i = 0; i < vec.size(); ++i)
	{
		ASSERT_TRUE(vec[0].z < 2*radius);
	}
}



TEST_F(ParticleSystemTest, test_setSystemSize)
{
    const unsigned size = 5;
    ParticleSystem system(radius, size, size, size);

    ASSERT_EQ(size * size * size, system.systemSize());
}

TEST_F(ParticleSystemTest, test_initializePos)
{
    system->initialize(*commonVel);

    ASSERT_EQ(2 * 6 * 6, system->getPos().size());
    
    ASSERT_EQ(-2, system->getPos()[0].x);
    ASSERT_EQ(-3, system->getPos()[0].y);
    ASSERT_EQ(-3, system->getPos()[0].z);

    ASSERT_EQ(-2, system->getPos()[1].x);
    ASSERT_EQ(-3, system->getPos()[1].y);
    ASSERT_EQ(-2, system->getPos()[1].z);
}

TEST_F(ParticleSystemTest, test_initializePrevPos)
{
	system->initialize(*commonVel);

    ASSERT_EQ(system->getPos().size(), system->getPrevPos().size());

    for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_EQ(system->getPos()[i].x, system->getPrevPos()[i].x);
		ASSERT_EQ(system->getPos()[i].y, system->getPrevPos()[i].y);
		ASSERT_EQ(system->getPos()[i].z, system->getPrevPos()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_changedValueOfPos)
{
	system->initialize(*commonVel);

    float3 newPos(10.f, 10.f, 10.f);
    system->getPos()[0] = newPos;

    ASSERT_NE(system->getPos()[0].x, system->getPrevPos()[0].x);
	ASSERT_NE(system->getPos()[0].y, system->getPrevPos()[0].y);
    ASSERT_NE(system->getPos()[0].z, system->getPrevPos()[0].z);
}

TEST_F(ParticleSystemTest, test_initializeVel)
{
	system->initialize(*commonVel);

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_EQ(commonVel->x, system->getVel()[i].x);
		ASSERT_EQ(commonVel->y, system->getVel()[i].y);
		ASSERT_EQ(commonVel->z, system->getVel()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_initializePrevVel)
{
	system->initialize(*commonVel);

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_EQ(system->getVel()[i].x, system->getPrevVel()[i].x);
		ASSERT_EQ(system->getVel()[i].y, system->getPrevVel()[i].y);
		ASSERT_EQ(system->getVel()[i].z, system->getPrevVel()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_changedValueOfVel)
{
 	system->initialize(*commonVel);	

    float3 newVel(10.f, 10.f, 10.f);
    system->getVel()[0] = newVel;

    ASSERT_NE(system->getVel()[0].x, system->getPrevVel()[0].x);
	ASSERT_NE(system->getVel()[0].y, system->getPrevVel()[0].y);
    ASSERT_NE(system->getVel()[0].z, system->getPrevVel()[0].z);
}

TEST_F(ParticleSystemTest, test_calculateForce)
{
	system->initialize(*commonVel);	

	const float dt = 0.5f;
	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_EQ(commonVel->x / dt, system->calculateForce(dt, i).x);
		ASSERT_EQ(commonVel->y / dt, system->calculateForce(dt, i).y);
		ASSERT_EQ(commonVel->z / dt, system->calculateForce(dt, i).z);
	}
}

TEST_F(ParticleSystemTest, test_verletMoveOnXDirection)
{
	const float dt = 0.5f;
	system->initialize(*commonVel);	

	vector3 posTmp = system->getPos();
	vector3 velTmp = system->getVel();
	system->verlet(dt);

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_NE(velTmp[i].x, system->getVel()[i].x);
		ASSERT_EQ(velTmp[i].y, system->getVel()[i].y);
		ASSERT_EQ(velTmp[i].z, system->getVel()[i].z);

		ASSERT_NE(posTmp[i].x, system->getPos()[i].x);
		ASSERT_EQ(posTmp[i].y, system->getPos()[i].y);
		ASSERT_EQ(posTmp[i].z, system->getPos()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_verletMoveOnOtherDirection)
{
	const float dt = 0.5f;
	float3 vel(3.f, 4.f, 6.f);
	system->initialize(vel);	

	vector3 posTmp = system->getPos();
	vector3 velTmp = system->getVel();
	system->verlet(dt);

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_NE(velTmp[i].x, system->getVel()[i].x);
		ASSERT_NE(velTmp[i].y, system->getVel()[i].y);
		ASSERT_NE(velTmp[i].z, system->getVel()[i].z);

		ASSERT_NE(posTmp[i].x, system->getPos()[i].x);
		ASSERT_NE(posTmp[i].y, system->getPos()[i].y);
		ASSERT_NE(posTmp[i].z, system->getPos()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_copyPosAndVel)
{
	const float dt = 0.5f;
	float3 vel(3.f, 4.f, 6.f);
	system->initialize(vel);	
	system->verlet(dt);

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_NE(system->getPos()[i].x, system->getPrevPos()[i].x);
		ASSERT_NE(system->getPos()[i].y, system->getPrevPos()[i].y);
		ASSERT_NE(system->getPos()[i].z, system->getPrevPos()[i].z);
	}

	system->copyPosAndVel();

	for(unsigned i = 0; i < system->systemSize(); ++i)
	{
		ASSERT_EQ(system->getPos()[i].x, system->getPrevPos()[i].x);
		ASSERT_EQ(system->getPos()[i].y, system->getPrevPos()[i].y);
		ASSERT_EQ(system->getPos()[i].z, system->getPrevPos()[i].z);
	}
}

TEST_F(ParticleSystemTest, test_checkParticleCol_amountOfCollidingParticles_singleCollision)
{
	float radius = 1.f;
	ParticleSystem system(radius, 1, 2, 2);
	system.initialize();

	system.getPos()[0] = float3(10.f, 0.f, 0.f);
	system.getPos()[1] = float3(10.5f, 0.f, 0.f);
	system.getPos()[2] = float3(1.5f, 0.f, 0.f);
	system.getPos()[3] = float3(4.5f, 0.f, 0.f);

	system.copyPosAndVel();

	vector4 collidate = system.checkCollision(0);
	ASSERT_EQ(1u, collidate.size());
	ASSERT_TRUE(collidate[0].z < 2*radius);
	
	collidate = system.checkCollision(1);
	ASSERT_EQ(1u, collidate.size());
	ASSERT_TRUE(collidate[0].z < 2*radius);

	collidate = system.checkCollision(2);
	ASSERT_EQ(0u, collidate.size());

	collidate = system.checkCollision(3);
	ASSERT_EQ(0u, collidate.size());
}

TEST_F(ParticleSystemTest, test_checkParticleCol_amountOfCollidingParticles_multipleCollision)
{
	float radius = 1.f;
	ParticleSystem system(radius, 1, 2, 3);
	system.initialize();

	system.getPos()[0] = float3(10.f, 0.f, 0.f);
	system.getPos()[1] = float3(10.f, 0.2f, 0.f);
	system.getPos()[2] = float3(4.5f, 0.f, 0.f);
	system.getPos()[3] = float3(10.5f, 0.f, 0.f);
	system.getPos()[4] = float3(-3.5f, 0.f, 0.f);
	system.getPos()[5] = float3(10.5f, 0.f, 0.3f);

	system.copyPosAndVel();

	vector4 collidate = system.checkCollision(0);
	ASSERT_EQ(3u, collidate.size());
	checkDistanceBetweenParticles(collidate);
	
	collidate = system.checkCollision(1);
	ASSERT_EQ(3u, collidate.size());
	checkDistanceBetweenParticles(collidate);

	collidate = system.checkCollision(2);
	ASSERT_EQ(0u, collidate.size());

	collidate = system.checkCollision(3);
	ASSERT_EQ(3u, collidate.size());
	checkDistanceBetweenParticles(collidate);

	collidate = system.checkCollision(4);
	ASSERT_EQ(0u, collidate.size());

	collidate = system.checkCollision(5);
	ASSERT_EQ(3u, collidate.size());
	checkDistanceBetweenParticles(collidate);
}



int main(int argc, char* argv[]) 
{                                                                                      
  testing::InitGoogleTest(&argc, argv);                                                                                 
  return RUN_ALL_TESTS();                                                                                               
}
