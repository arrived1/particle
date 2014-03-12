#include <gtest/gtest.h>
#include <boost/shared_ptr.hpp>

#include "particleSystem.h"

class ParticleSystemTest : public testing::Test 
{
public:
	void SetUp()
	{
	}

	boost::shared_ptr<ParticleSystem> system;
};






int main(int argc, char* argv[]) 
{                                                                                      
  testing::InitGoogleTest(&argc, argv);                                                                                 
  return RUN_ALL_TESTS();                                                                                               
}
