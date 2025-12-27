#pragma once

#include <concepts>

namespace PpADER::FvCore {

template <class Lim> struct LimiterTrait;

template <class Lim>
concept Limiter =
    requires(const Lim &lim, const typename LimiterTrait<Lim>::scalar_t &a,
             const typename LimiterTrait<Lim>::scalar_t &b) {
      typename LimiterTrait<Lim>::scalar_t;

      {
        LimiterTrait<Lim>::limit(lim, a, b)
      } -> std::convertible_to<typename LimiterTrait<Lim>::scalar_t>;
    };
namespace LimiterAPI {

template <Limiter Lim> using scalar_t = typename LimiterTrait<Lim>::scalar_t;

template <Limiter Lim>
inline scalar_t<Lim> limit(const Lim &lim, const scalar_t<Lim> &a,
                           const scalar_t<Lim> &b) {
  return LimiterTrait<Lim>::limit(lim, a, b);
}
} // namespace LimiterAPI
} // namespace PpADER::FvCore
