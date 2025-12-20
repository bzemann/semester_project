#include <cstddef>
#include <pp_ader/fv_core/mesh1d.hpp>
#include <utility>
#include <vector>

namespace PpADER::FvCore {

Mesh1d Mesh1d::make(double x_begin, double x_end, std::size_t num_phys_points,
                    std::size_t num_ghost_cells_left,
                    std::size_t num_ghost_cells_right) {
  const std::size_t tot_points =
      num_phys_points + num_ghost_cells_left + num_ghost_cells_right;
  const double dx = (x_end - x_begin) / static_cast<double>(num_phys_points);

  std::vector<double> grid(tot_points, 0.0);

  for (std::size_t i = 0; i < tot_points; i++) {
    const std::ptrdiff_t i_phys =
        static_cast<std::ptrdiff_t>(i) -
        static_cast<std::ptrdiff_t>(num_ghost_cells_left);
    grid[i] = (x_begin + (static_cast<double>(i_phys) + 0.5) * dx);
  }

  return Mesh1d{dx,
                tot_points,
                num_phys_points,
                num_ghost_cells_left,
                num_ghost_cells_right,
                std::move(grid)};
}

}  // namespace PpADER::FvCore
