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
		commonVel.reset(new float3(3.f, 0, 0));
		system.reset(new ParticleSystem(x, y, z));
	}

	unsigned x, y, z;
	boost::shared_ptr<float3> commonVel;
	boost::shared_ptr<ParticleSystem> system;
};

TEST_F(ParticleSystemTest, test_setSystemSize)
{
    const unsigned size = 5;
    ParticleSystem system(size, size, size);

    ASSERT_EQ(size * size * size, system.systemSize());
}

TEST_F(ParticleSystemTest, test_initializePos)
{
    // system->initializePos();
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
    // system->initializePos();
    // system->initializePrevPos();

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
    // system->initializePos();
    // system->initializePrevPos();

    float3 newPos(10.f, 10.f, 10.f);
    system->getPos()[0] = newPos;

    ASSERT_NE(system->getPos()[0].x, system->getPrevPos()[0].x);
	ASSERT_NE(system->getPos()[0].y, system->getPrevPos()[0].y);
    ASSERT_NE(system->getPos()[0].z, system->getPrevPos()[0].z);
}

TEST_F(ParticleSystemTest, test_initializeVel)
{
	system->initialize(*commonVel);
	// system->initializeVel(*commonVel);

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
	// system->initializeVel(*commonVel);
	// system->initializePrevVel();

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
	// system->initializeVel(*commonVel);
	// system->initializePrevVel();

    float3 newVel(10.f, 10.f, 10.f);
    system->getVel()[0] = newVel;

    ASSERT_NE(system->getVel()[0].x, system->getPrevVel()[0].x);
	ASSERT_NE(system->getVel()[0].y, system->getPrevVel()[0].y);
    ASSERT_NE(system->getVel()[0].z, system->getPrevVel()[0].z);
}




int main(int argc, char* argv[]) {                                                                                      
  testing::InitGoogleTest(&argc, argv);                                                                                 
  return RUN_ALL_TESTS();                                                                                               
}
