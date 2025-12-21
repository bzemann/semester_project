#pragma once

#include "pp_ader/fv_core/field_concept.hpp"
#include <cstddef>
#include <pp_ader/fv_core/bc_concept.hpp>

namespace PpADER::FvCore {
struct PeriodicBC {};

template <> struct BCTrait<PeriodicBC> {
  template <Mesh M, FieldLike U>
  static void apply(const PeriodicBC &, const M &mesh, U &u) {}
};

} // namespace PpADER::FvCore
