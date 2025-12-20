#pragma once

#include <Eigen/Core>
#include <iostream>

namespace PpADER::Utils {

template <typename Derived>
void print(const Eigen::MatrixBase<Derived>& A) {
  const Eigen::IOFormat fmt(Eigen::StreamPrecision, Eigen::DontAlignCols,
                            ", ",    // coeff separator inside a row
                            ",\n ",  // row separator (note the comma!)
                            "[",     // row prefix
                            "]",     // row suffix
                            "[",     // matrix prefix
                            "]"      // matrix suffix
  );

  std::cout << A.format(fmt) << "\n";
}

}  // namespace PpADER::Utils
