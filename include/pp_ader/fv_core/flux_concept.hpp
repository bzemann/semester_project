#pragma once

#include <concepts>
#include <pp_ader/fv_core/law_concepts.hpp>

namespace PpADER::FvCore {
template <class F>
struct FluxTrait;

template <class F>
concept Flux = requires(const F& nf, const typename FluxTrait<F>::law_t& law,
                        const typename FluxTrait<F>::state_t& u_minus,
                        const typename FluxTrait<F>::state_t& u_plus) {
  typename FluxTrait<F>::law_t;
  typename FluxTrait<F>::state_t;
  typename FluxTrait<F>::scalar_t;

  requires ConservationLaw<typename FluxTrait<F>::law_t>;

  {
    FluxTrait<F>::flux(nf, law, u_minus, u_plus)
  } -> std::convertible_to<typename FluxTrait<F>::state_t>;
};

namespace FluxAPI {
template <Flux F>
using law_t = typename FluxTrait<F>::law_t;

template <Flux F>
using state_t = typename FluxTrait<F>::state_t;

template <Flux F>
using scalar_t = typename FluxTrait<F>::scalar_t;

template <Flux F>
inline state_t<F> flux(const F& nf, const law_t<F>& law,
                       const state_t<F>& u_minus, const state_t<F>& u_plus) {
  return FluxTrait<F>::flux(nf, law, u_minus, u_plus);
}
}  // namespace FluxAPI

}  // namespace PpADER::FvCore
