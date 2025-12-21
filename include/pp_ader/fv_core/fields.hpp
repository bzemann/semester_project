#pragma once

#include <Eigen/Core>
#include <cstddef>
#include <pp_ader/fv_core/field_concept.hpp>
#include <vector>

namespace PpADER::FvCore {
template <> struct FieldTrait<std::vector<double>> {
  using value_t = double;

  static std::size_t size(const std::vector<value_t> &v) { return v.size(); }

  static const value_t &get(const std::vector<value_t> &v, std::size_t i) {
    return v[i];
  }

  static value_t &get(std::vector<value_t> &v, std::size_t i) { return v[i]; }
};

template <> struct FieldTrait<std::vector<Eigen::VectorXd>> {
  using value_t = Eigen::VectorXd;

  static std::size_t size(const std::vector<value_t> &v) { return v.size(); }

  static const value_t &get(const std::vector<value_t> &v, std::size_t i) {
    return v[i];
  }

  static value_t &get(std::vector<value_t> &v, std::size_t i) { return v[i]; }
};
} // namespace PpADER::FvCore
