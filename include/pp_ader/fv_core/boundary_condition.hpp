#pragma once

#include "pp_ader/fv_core/field_concept.hpp"
#include "pp_ader/fv_core/mesh_concept.hpp"
#include <cassert>
#include <cstddef>
#include <pp_ader/fv_core/bc_concept.hpp>

namespace PpADER::FvCore {
struct PeriodicBC {};

template <> struct BCTrait<PeriodicBC> {
  template <Mesh M, FieldLike U>
  static void apply(const PeriodicBC &, const M &mesh, U &u) {
    // K is the number ghost cells left
    const std::size_t K = MeshAPI::ghost_left(mesh);
    // L is the number ghost cells right
    const std::size_t L = MeshAPI::ghost_right(mesh);
    // N is the number physical cells
    const std::size_t N = MeshAPI::num_phys_points(mesh);

    assert(FieldAPI::size(u) == MeshAPI::length(mesh));
    assert(K + L + N == MeshAPI::length(mesh));

    // fill right ghost cells
    for (std::size_t i = 0; i < L; i++) {
      FieldAPI::get(u, K + N + i) = FieldAPI::get(u, K + i);
    }

    // fill left ghost cells
    for (std::size_t i = 0; i < K; i++) {
      FieldAPI::get(u, i) = FieldAPI::get(u, N + i);
    }
  }
};

} // namespace PpADER::FvCore
