#pragma once

#include <concepts>
#include <cstddef>

namespace PpADER::FvCore {

template <class Field> struct FieldTrait;

template <class Field>
concept FieldLike = requires(Field &f, const Field &cf, std::size_t i) {
  typename FieldTrait<Field>::value_t;

  { FieldTrait<Field>::size(cf) } -> std::convertible_to<std::size_t>;
  {
    FieldTrait<Field>::get(cf, i)
  } -> std::convertible_to<const typename FieldTrait<Field>::value_t &>;
  {
    FieldTrait<Field>::get(f, i)
  } -> std::convertible_to<typename FieldTrait<Field>::value_t &>;
};

namespace FieldAPI {

template <FieldLike F> using value_t = typename FieldTrait<F>::value_t;

template <FieldLike F> inline std::size_t size(const F &f) {
  return FieldTrait<F>::size(f);
}

template <FieldLike F> inline const value_t<F> &get(const F &f, std::size_t i) {
  return FieldTrait<F>::get(f, i);
}

template <FieldLike F> inline value_t<F> &get(F &f, std::size_t i) {
  return FieldTrait<F>::get(f, i);
}

} // namespace FieldAPI
} // namespace PpADER::FvCore
