#pragma once

#include <pp_ader/fv_core/concepts.hpp>
#include <vector>

// #include "../types.hpp"

namespace PpADER::FvCore {

struct Mesh1d {
  double dx{};
  std::size_t num_points{};
  std::size_t number_phys_points{};
  std::size_t ghost_l{};
  std::size_t ghost_r{};
  std::vector<double> grid;

  static Mesh1d make(double x_begin, double x_end, std::size_t num_phys_points,
                     std::size_t num_ghost_cells_left,
                     std::size_t num_ghost_cells_right);
};

template <>
struct MeshTrait<Mesh1d> {
  using scalar_t = double;

  static scalar_t dx(const Mesh1d& m) { return m.dx; }

  static scalar_t cell_center(const Mesh1d& m, std::size_t i) {
    return m.grid[i];
  }

  static std::size_t length(const Mesh1d& m) { return m.num_points; }

  static std::size_t num_phys_points(const Mesh1d& m) {
    return m.number_phys_points;
  }

  static std::size_t ghost_left(const Mesh1d& m) { return m.ghost_l; }

  static std::size_t ghost_right(const Mesh1d& m) { return m.ghost_r; }
};

}  // namespace PpADER::FvCore
