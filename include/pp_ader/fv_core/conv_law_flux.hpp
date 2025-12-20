#pragma once

#include <algorithm>
#include <cmath>
#include <concepts>
#include <span>
#include <vector>
#include <pp_ader/fv_core/flux_concept.hpp>
#include <pp_ader/fv_core/law_concepts.hpp>
#include <pp_ader/fv_core/mesh_concept.hpp>

namespace PpADER::FvCore {
struct LinAdvScalar {
  double c;
};

template <>
struct LawTrait<LinAdvScalar> {
  using state_t = double;
  using scalar_t = double;

  static state_t phys_flux(const LinAdvScalar& law, const state_t& u){
    return law.c * u;
  }

  static scalar_t max_wave_speed(const LinAdvScalar& law, const state_t& u_minus, const state_t& u_plus) {
    return std::abs(law.c);
  }
};

struct RusanovLin {};

template <>
struct FluxTrait<RusanovLin> {
  using law_t = LinAdvScalar;
  using state_t = LawTrait<law_t>::state_t;
  using scalar_t = LawTrait<law_t>::scalar_t;

  static state_t flux(const RusanovLin&, const law_t& law, const state_t& u_minus, const state_t& u_plus) {
    const auto f_minus = LawAPI::phys_flux(law, u_minus);
    const auto f_plus= LawAPI::phys_flux(law, u_plus);
    const auto alpha = LawAPI::max_wave_speed(law, u_minus, u_plus);

    return scalar_t(0.5) * (f_minus + f_plus) - scalar_t(0.5) * alpha * (u_plus - u_minus);
  }
};

struct BurgerScalar {};

template <>
struct LawTrait<BurgerScalar> {
  using state_t = double;
  using scalar_t = double;

  static state_t phys_flux(const BurgerScalar&, const state_t& u) {
    return 0.5 * u * u;
  }

  static scalar_t max_wave_speed(const BurgerScalar&, const state_t& u_minus, const state_t& u_plus) {
    return std::max(std::abs(u_minus), std::abs(u_plus));
  }
};

struct RusanovBur {};

template <>
struct FluxTrait<RusanovBur> {
  using law_t = BurgerScalar;
  using state_t = LawTrait<BurgerScalar>::state_t;
  using scalar_t = LawTrait<BurgerScalar>::scalar_t;

  static state_t flux(const RusanovBur&, const law_t& law, const state_t& u_minus, const state_t& u_plus) {
    const auto f_minus = LawAPI::phys_flux(law, u_minus);
    const auto f_plus = LawAPI::phys_flux(law, u_plus);
    const auto alpha = LawAPI::max_wave_speed(law, u_minus, u_plus);

    return scalar_t(0.5) * (f_minus + f_plus) - scalar_t(0.5) * alpha * (u_plus - u_minus);
  }
};

template <ConservationLaw L , Flux F>
requires std::same_as<L, FluxAPI::law_t<F>>
void compute_interface_fluxes(const L& law, const F& flux, std::span<const FluxAPI::state_t<F>> u_minus, std::span<const FluxAPI::state_t<F>> u_plus, std::span<FluxAPI::state_t<F>> Fhat) {
  const auto size = u_minus.size();
  for (std::size_t i = 0; i < size; i++){
    Fhat[i] = FluxAPI::flux(flux, law, u_minus[i], u_plus[i]);
  }
}

template <ConservationLaw L, Flux F>
requires std::same_as<L, FluxAPI::law_t<F>>
auto fluxes_vector(const L& law, const F& flux, std::span<const FluxAPI::state_t<F>> u_minus, std::span<const FluxAPI::state_t<F>> u_plus) {
  auto size = u_minus.size();
  std::vector<FluxAPI::state_t<F>> out(size); 
  compute_interface_fluxes(law, flux, u_minus, u_plus, out);
  return out;
}

}  // namespace PpADER::FvCore
