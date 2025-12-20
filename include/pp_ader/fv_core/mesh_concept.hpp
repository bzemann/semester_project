#pragma once

#include <concepts>
#include <cstddef>

namespace PpADER::FvCore {

// Mesh Trait
template <class M>
struct MeshTrait;

template <class M>
concept Mesh = requires(const M& m, std::size_t i) {
  typename MeshTrait<M>::scalar_t;

  {
    MeshTrait<M>::dx(m)
  } -> std::convertible_to<typename MeshTrait<M>::scalar_t>;
  {
    MeshTrait<M>::cell_center(m, i)
  } -> std::convertible_to<typename MeshTrait<M>::scalar_t>;
  { MeshTrait<M>::length(m) } -> std::convertible_to<std::size_t>;
  { MeshTrait<M>::num_phys_points(m) } -> std::convertible_to<std::size_t>;
  { MeshTrait<M>::ghost_left(m) } -> std::convertible_to<std::size_t>;
  { MeshTrait<M>::ghost_right(m) } -> std::convertible_to<std::size_t>;
};

namespace MeshAPI {
template <Mesh M>
using scalar_t = typename MeshTrait<M>::scalar_t;

template <Mesh M>
inline scalar_t<M> dx(const M& m) {
  return MeshTrait<M>::dx(m);
}

template <Mesh M>
inline scalar_t<M> cell_center(const M& m, std::size_t i) {
  return MeshTrait<M>::cell_center(m, i);
}

template <Mesh M>
inline std::size_t length(const M& m) {
  return MeshTrait<M>::length(m);
}

template <Mesh M>
inline std::size_t num_phys_points(const M& m) {
  return MeshTrait<M>::num_phys_points(m);
}

template <Mesh M>
inline std::size_t ghost_left(const M& m) {
  return MeshTrait<M>::ghost_left(m);
}

template <Mesh M>
inline std::size_t ghost_right(const M& m) {
  return MeshTrait<M>::ghost_right(m);
}
}  // namespace MeshAPI
}  // namespace PpADER::FvCore
