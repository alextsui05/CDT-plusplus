#include "gmock/gmock.h"
//#include "Sphere_d.h"
#include "S3Triangulation.h"

using namespace ::testing;

TEST(Triangulated2Sphere, DISABLED_CreatesTriangulated2Sphere) {

  Delaunay T;

  ASSERT_TRUE(T.is_valid())
    << "Triangulation is invalid.";
}