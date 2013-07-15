#include <gtest/gtest.h>

class ParticleSystemTest : public testing::Test {};

TEST_F(ParticleSystemTest, test)
{
    ASSERT_TRUE(true);
}


int main(int argc, char* argv[]) {                                                                                      
  testing::InitGoogleTest(&argc, argv);                                                                                 
  return RUN_ALL_TESTS();                                                                                               
}
