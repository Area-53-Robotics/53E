#include "api.h"
#include "gtest/gtest.h"
#include "subsystems/pid.hpp"
#include "subsystems/point.hpp"
using namespace testing;

TEST(PointTests, distance) {
  Point point1(0, 0, 0);
  Point point2(10, 0, 0);
  EXPECT_EQ(point1.get_linear_dist(point2), 10);
}

int main(int argc, char *argv[]) {
  InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
