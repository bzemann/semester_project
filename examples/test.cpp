#include <Eigen/Core>
#include <cstddef>
#include <iostream>
#include <pp_ader/fv_core/concepts.hpp>
#include <pp_ader/fv_core/mesh1d.hpp>
#include <pp_ader/time_integrator/fvm_ssp_rk.hpp>
#include <pp_ader/types.hpp>
#include <pp_ader/utils.hpp>

using namespace PpADER::FvCore;
using namespace PpADER::TimeIntegrator;

int main() {
  Mesh1d mesh = Mesh1d::make(0.0, 1.0, 4, 2, 2);

  std::cout << "dx: " << MeshAPI::dx(mesh) << "\n";
  std::cout << "length: " << MeshAPI::length(mesh) << "\n";
  std::cout << "number physical points: " << MeshAPI::num_phys_points(mesh)
            << "\n";
  std::cout << "Ghost cell left: " << MeshAPI::ghost_left(mesh)
            << ", Ghost cell right: " << MeshAPI::ghost_right(mesh) << "\n";
  std::cout << "cell centers:\n";
  std::size_t length = MeshAPI::length(mesh);

  for (std::size_t i = 0; i < length; i++) {
    std::cout << "i: " << i << "x: " << MeshAPI::cell_center(mesh, i) << "\n";
  }

  Eigen::VectorXd a = Eigen::VectorXd::Random(3);
  Eigen::VectorXd b = Eigen::VectorXd::Random(3);

  Eigen::VectorXd c = add(a, b);

  PpADER::Utils::print(c);

  return 0;
}
