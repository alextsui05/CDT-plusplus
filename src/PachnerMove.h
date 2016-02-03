/// Causal Dynamical Triangulations in C++ using CGAL
///
/// Copyright (c) 2016 Adam Getchell
///
/// RAII class for managing exception-safe ergodic (foliation-preserving
/// Pachner) moves.
/// See http://www.stroustrup.com/except.pdf and
/// http://exceptionsafecode.com for details.

#ifndef SRC_PACHNERMOVE_H_
#define SRC_PACHNERMOVE_H_

#include <tuple>
#include <memory>
#include <vector>
#include <utility>
#include <algorithm>

#include "Metropolis.h"

class PachnerMove {
 public:
  template <typename T1, typename T2, typename T3, typename T4>
  PachnerMove(T1&& universe,
              T2&& move,
              T3&& movable_simplex_types,
              T4&& movable_edge_types) :
              universe_(std::move(universe)),
              move_(move),
              movable_simplex_types_(movable_simplex_types),
              movable_edge_types_(movable_edge_types) {
    // Make a copy
    auto tempDT = Delaunay(*universe_);
    auto tempDT_ptr = std::make_unique<Delaunay>(tempDT);

    try {
      this->make_move(move);  //  throws exceptions

      // Exception-safe commit
      std::swap(universe_, tempDT_ptr);
    }

    catch (...) {
      // Swallow the exceptions thrown by make_move() from
      // CGAL_triangulation_precondition and postcondition
      std::cerr << "We caught a move error." << std::endl;
    }
  }

  ~PachnerMove() {}

  void make_move(move_type);

  move_tuple attempted_moves_;
  std::tuple<std::vector<Cell_handle>,
             std::vector<Cell_handle>,
             std::vector<Cell_handle>> movable_simplex_types_;
  ///< Movable (3,1), (2,2) and (1,3) simplices.

// private:
  std::unique_ptr<Delaunay> universe_;
  move_type move_;

  std::pair<std::vector<Edge_tuple>, unsigned> movable_edge_types_;
  ///< Movable timelike and spacelike edges.
};

void PachnerMove::make_move(const move_type move) {
  #ifndef NDEBUG
  std::cout << __PRETTY_FUNCTION__ << " called." << std::endl;
  #endif
  switch (move) {
    case move_type::TWO_THREE:
      make_23_move(universe_, movable_simplex_types_, attempted_moves_);
      break;
    case move_type::THREE_TWO:
      make_32_move(universe_, movable_edge_types_, attempted_moves_);
      break;
    case move_type::TWO_SIX:
      make_26_move(universe_, movable_simplex_types_, attempted_moves_);
      break;
    case move_type::SIX_TWO:
      // make_62_move(universe_, movable_types_, attempted_moves_);
      break;
    case move_type::FOUR_FOUR:
      // make_44_move(universe_, movable_types_, attempted_moves_);
      break;
  }
}  // make_move()


#endif  // SRC_PACHNERMOVE_H_