/// Causal Dynamical Triangulations in C++ using CGAL
///
/// Copyright (c) 2014 Adam Getchell
///
/// Inserts a given number of points onto a 3-dimensional sphere
/// of given radius

#ifndef SPHERE_3_H
#define SPHERE_3_H

/// CGAL headers
#include <CGAL/Simple_cartesian.h>
#include <CGAL/point_generators_3.h>

typedef CGAL::Simple_cartesian<double> Scd;

inline void make_3_sphere(std::vector<Scd::Point_3> *v,
    int number_of_points,
    double radius,
    bool message) {

    v->reserve(number_of_points);

    CGAL::Random_points_on_sphere_3<Scd::Point_3> gen(radius);

    for(size_t i = 0; i < number_of_points; i++)
    {
      v->push_back(*gen++);
    }
    ///
    /// If message = true
    if (message) {
      std::cout << "Generating " << number_of_points << " random points on "
      << "the surface of a sphere of center 0 and radius " << radius << "."
      << std::endl;

      for (auto point : *v)
        {
          std::cout << " " << point << std::endl;
        }
    }
}


#endif // SPHERE_3_H