#pragma once

#include <concepts>
#include <cstddef>

#include <pp_ader/fv_core/field_concept.hpp>
#include <pp_ader/fv_core/mesh_concept.hpp>

namespace PpADER::FvCore {

template <class BC> struct BCTrait;

template <class BC, class M, class U>
concept BoundaryCondition =
    Mesh<M> && FieldLike<U> && requires(const BC &bc, const M &mesh, U &u) {
      { BCTrait<BC>::apply(bc, mesh, u) } -> std::same_as<void>;
    };

namespace BcAPI {

template <class BC, class M, class U>
  requires BoundaryCondition<BC, M, U>
inline void apply(const BC &bc, const M &mesh, U &u) {
  BCTrait<BC>::apply(bc, mesh, u);
}

} // namespace BcAPI
} // namespace PpADER::FvCore
