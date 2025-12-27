#pragma once

#include <concepts>
#include <cstddef>
#include <pp_ader/fv_core/field_concept.hpp>
#include <pp_ader/fv_core/mesh_concept.hpp>

namespace PpADER::FvCore {

template <class R> struct ReconTrait;

template <class R, class M, class U, class UM, class UP>
concept Recon =
    Mesh<M> && FieldLike<U> && FieldLike<UP> && FieldLike<UM> &&
    requires(const R &r, const M &m, const U &u, UM &u_minus, UP &u_plus) {
      typename ReconTrait<R>::state_t;
      typename ReconTrait<R>::scalar_t;

      requires std::same_as<FieldAPI::value_t<U>,
                            typename ReconTrait<R>::state_t>;
      requires std::same_as<FieldAPI::value_t<UM>,
                            typename ReconTrait<R>::state_t>;
      requires std::same_as<FieldAPI::value_t<UP>,
                            typename ReconTrait<R>::state_t>;
      {
        ReconTrait<R>::reconstruction(r, m, u, u_minus, u_plus)
      } -> std::same_as<void>;
    };
namespace ReconAPI {

template <class R> using state_t = typename ReconTrait<R>::state_t;

template <class R> using scalar_t = typename ReconTrait<R>::scalar_t;

template <class R, class M, class U, class UM, class UP>
  requires Recon<R, M, U, UM, UP>
inline void reconstruction(const R &r, const M &m, const U &u, UM &u_minus,
                           UP &u_plus) {
  return ReconTrait<R>::reconstruction(r, m, u, u_minus, u_plus);
}

} // namespace ReconAPI
} // namespace PpADER::FvCore
