#pragma once

#include <concepts>
#include <type_traits>

namespace PpADER::FvCore {
template <class L>
struct LawTrait;

template <class L>
concept ConservationLaw =
    requires(const L& law, const typename LawTrait<L>::state_t& u,
             const typename LawTrait<L>::state_t& u_minus,
             const typename LawTrait<L>::state_t& u_plus) {
      typename LawTrait<L>::state_t;
      typename LawTrait<L>::scalar_t;

      requires std::is_arithmetic_v<typename LawTrait<L>::scalar_t>;

      {
        LawTrait<L>::phys_flux(law, u)
      } -> std::convertible_to<typename LawTrait<L>::state_t>;

      {
        LawTrait<L>::max_wave_speed(law, u_minus, u_plus)
      } -> std::convertible_to<typename LawTrait<L>::scalar_t>;
    };

namespace LawAPI {
template <ConservationLaw L>
using state_t = typename LawTrait<L>::state_t;

template <ConservationLaw L>
using scalar_t = typename LawTrait<L>::scalar_t;

template <ConservationLaw L>
inline state_t<L> phys_flux(const L& law, const state_t<L>& u) {
  return LawTrait<L>::phys_flux(law, u);
}

template <ConservationLaw L>
inline scalar_t<L> max_wave_speed(const L& law, const state_t<L>& u_minus,
                                  const state_t<L>& u_plus) {
  return LawTrait<L>::max_wave_speed(law, u_minus, u_plus);
}

}  // namespace LawAPI
}  // namespace PpADER::FvCore
